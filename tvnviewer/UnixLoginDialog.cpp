// Copyright (C) 2026 JumpServer Authors.
//
// This file is part of TightVNC and is distributed under the terms of the
// GNU General Public License, version 2 or (at your option) any later version.

#include "UnixLoginDialog.h"

UnixLoginDialog::UnixLoginDialog()
: BaseDialog(IDD_DUNIXLOGIN)
{
}

UnixLoginDialog::~UnixLoginDialog()
{
  if (m_strPassword.getSize() != 0) {
    SecureZeroMemory(const_cast<TCHAR *>(m_strPassword.getString()),
                     m_strPassword.getSize());
  }
  m_strPassword.setString(_T(""));
}

BOOL UnixLoginDialog::onInitDialog()
{
  setControlById(m_hostname, IDC_UNIX_LOGIN_HOST);
  m_hostname.setText(m_strHost.getString());
  setControlById(m_username, IDC_UNIX_LOGIN_USERNAME);
  m_username.setText(m_strUsername.getString());
  setControlById(m_password, IDC_UNIX_LOGIN_PASSWORD);
  if (m_strUsername.isEmpty()) {
    m_username.setFocus();
  } else {
    m_password.setFocus();
  }
  return FALSE;
}

void UnixLoginDialog::setHostName(const StringStorage *hostname)
{
  m_strHost = *hostname;
}

void UnixLoginDialog::setUsername(const StringStorage *username)
{
  m_strUsername = *username;
}

BOOL UnixLoginDialog::onCommand(UINT controlID, UINT notificationID)
{
  if (controlID == IDOK) {
    m_username.getText(&m_strUsername);
    m_password.getText(&m_strPassword);
    m_password.setText(_T(""));
    kill(1);
    return TRUE;
  }
  if (controlID == IDCANCEL) {
    m_password.setText(_T(""));
    kill(0);
    return TRUE;
  }
  return FALSE;
}

const StringStorage *UnixLoginDialog::getUsername() const
{
  return &m_strUsername;
}

const StringStorage *UnixLoginDialog::getPassword() const
{
  return &m_strPassword;
}
