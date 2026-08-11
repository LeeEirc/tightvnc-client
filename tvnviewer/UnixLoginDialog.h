// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#ifndef _UNIX_LOGIN_DIALOG_H_
#define _UNIX_LOGIN_DIALOG_H_

#include "gui/BaseDialog.h"
#include "gui/TextBox.h"
#include "UnixLoginResource.h"

class UnixLoginDialog : public BaseDialog
{
public:
  UnixLoginDialog();
  virtual ~UnixLoginDialog();

  const StringStorage *getUsername() const;
  const StringStorage *getPassword() const;
  void setHostName(const StringStorage *hostname);
  void setUsername(const StringStorage *username);

protected:
  virtual BOOL onCommand(UINT controlID, UINT notificationID);
  virtual BOOL onInitDialog();

  TextBox m_username;
  TextBox m_password;
  TextBox m_hostname;
  StringStorage m_strUsername;
  StringStorage m_strPassword;
  StringStorage m_strHost;
};

#endif
