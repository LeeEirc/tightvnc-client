// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#ifndef _VIEWER_UNIX_LOGIN_AUTH_HANDLER_H_
#define _VIEWER_UNIX_LOGIN_AUTH_HANDLER_H_

#include "viewer-core/UnixLoginAuthenticationHandler.h"
#include "ConnectionData.h"

class ViewerUnixLoginAuthHandler : public UnixLoginAuthenticationHandler
{
public:
  ViewerUnixLoginAuthHandler(ConnectionData *connectionData);
  virtual ~ViewerUnixLoginAuthHandler();

private:
  virtual void getCredentials(StringStorage *username,
                              StringStorage *password);

  ConnectionData *m_connectionData;
};

#endif
