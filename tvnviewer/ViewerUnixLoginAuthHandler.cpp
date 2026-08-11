// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#include "ViewerUnixLoginAuthHandler.h"
#include "UnixLoginDialog.h"

ViewerUnixLoginAuthHandler::ViewerUnixLoginAuthHandler(
    ConnectionData *connectionData)
: m_connectionData(connectionData)
{
}

ViewerUnixLoginAuthHandler::~ViewerUnixLoginAuthHandler()
{
}

void ViewerUnixLoginAuthHandler::getCredentials(StringStorage *username,
                                                StringStorage *password)
{
  if (!m_connectionData->isSetUnixLoginCredentials()) {
    UnixLoginDialog authDialog;
    StringStorage hostname = m_connectionData->getHost();
    StringStorage prefilledUsername =
        m_connectionData->getUnixLoginUsername();
    authDialog.setHostName(&hostname);
    authDialog.setUsername(&prefilledUsername);
    if (authDialog.showModal()) {
      m_connectionData->setUnixLoginCredentials(authDialog.getUsername(),
                                                authDialog.getPassword());
    } else {
      throw AuthCanceledException();
    }
  }

  m_connectionData->getUnixLoginCredentials(username, password);
}
