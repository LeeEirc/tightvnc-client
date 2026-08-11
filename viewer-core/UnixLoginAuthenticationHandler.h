// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#ifndef _UNIX_LOGIN_AUTHENTICATION_HANDLER_H_
#define _UNIX_LOGIN_AUTHENTICATION_HANDLER_H_

#include "viewer-core/AuthHandler.h"

// Implements Tight Security's UnixLogin authentication capability (129).
// Concrete viewers provide credentials through getCredentials().
class UnixLoginAuthenticationHandler : public AuthHandler
{
public:
  UnixLoginAuthenticationHandler();
  virtual ~UnixLoginAuthenticationHandler();

  virtual void authenticate(DataInputStream *input, DataOutputStream *output);
  virtual void addAuthCapability(CapabilitiesManager *capabilitiesManager);

protected:
  virtual void getCredentials(StringStorage *username,
                              StringStorage *password) = 0;
};

#endif
