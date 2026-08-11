// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#include "UnixLoginAuthenticationHandler.h"

#include "rfb/AuthDefs.h"
#include "rfb/VendorDefs.h"
#include "util/Utf8StringStorage.h"

namespace {

const size_t MAX_UNIX_LOGIN_CREDENTIAL_LENGTH = 1 << 20;

void wipeString(StringStorage *value)
{
  if (value->getSize() != 0) {
    SecureZeroMemory(const_cast<TCHAR *>(value->getString()), value->getSize());
  }
  value->setString(_T(""));
}

void wipeUtf8(Utf8StringStorage *value)
{
  if (value->getSize() != 0) {
    SecureZeroMemory(const_cast<char *>(value->getString()), value->getSize());
  }
}

} // namespace

UnixLoginAuthenticationHandler::UnixLoginAuthenticationHandler()
: AuthHandler(AuthDefs::UNIX_LOGIN)
{
}

UnixLoginAuthenticationHandler::~UnixLoginAuthenticationHandler()
{
}

void UnixLoginAuthenticationHandler::authenticate(DataInputStream *input,
                                                   DataOutputStream *output)
{
  (void)input;

  StringStorage username;
  StringStorage password;
  getCredentials(&username, &password);

  try {
    Utf8StringStorage usernameUtf8(&username);
    Utf8StringStorage passwordUtf8(&password);
    const size_t usernameLength = usernameUtf8.getLength();
    const size_t passwordLength = passwordUtf8.getLength();
    if (usernameLength > MAX_UNIX_LOGIN_CREDENTIAL_LENGTH ||
        passwordLength > MAX_UNIX_LOGIN_CREDENTIAL_LENGTH) {
      wipeUtf8(&passwordUtf8);
      throw AuthException(_T("Unix login credentials exceed the 1 MiB limit"));
    }

    try {
      // UnixLogin/Plain places both lengths before either byte sequence.
      output->writeUInt32(static_cast<UINT32>(usernameLength));
      output->writeUInt32(static_cast<UINT32>(passwordLength));
      if (usernameLength != 0) {
        output->writeFully(usernameUtf8.getString(), usernameLength);
      }
      if (passwordLength != 0) {
        output->writeFully(passwordUtf8.getString(), passwordLength);
      }
      output->flush();
    } catch (...) {
      wipeUtf8(&passwordUtf8);
      throw;
    }

    wipeUtf8(&passwordUtf8);
  } catch (...) {
    wipeString(&password);
    throw;
  }

  wipeString(&password);
}

void UnixLoginAuthenticationHandler::addAuthCapability(
    CapabilitiesManager *capabilitiesManager)
{
  capabilitiesManager->addAuthCapability(this,
                                          AuthDefs::UNIX_LOGIN,
                                          VendorDefs::TIGHTVNC,
                                          AuthDefs::SIG_UNIX_LOGIN,
                                          _T("Tight Unix login"));
}
