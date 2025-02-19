// Author: Kang Lin <kl222@126.com>

#include <QLoggingCategory>
#include <QCryptographicHash>
#include <QInputDialog>

#include "ParameterConnecter.h"
#include "RabbitCommonEncrypt.h"
#include "RabbitCommonTools.h"
#include "DlgInputPassword.h"

Q_DECLARE_LOGGING_CATEGORY(Client);

CParameterConnecter::CParameterConnecter(QObject *parent)
    : CParameter(parent),
    m_pParameterViewe(nullptr),
    m_bShowServerName(true),
    m_nPort(0),
    m_bSavePassword(false),
    m_bOnlyView(false),
    m_bLocalCursor(true),
    m_bClipboard(true),
    m_eProxyType(emProxy::No),
    m_nProxyPort(1080)
{
    SetUser(RabbitCommon::CTools::GetCurrentUser());
}

CParameterClient* CParameterConnecter::GetParameterViewer()
{
    return m_pParameterViewe;
}

bool CParameterConnecter::GetCheckCompleted()
{
    if(GetSavePassword()) return true;
    return false;
}

const QString CParameterConnecter::GetName() const
{
    return m_szName;
}

void CParameterConnecter::SetName(const QString& name)
{
    if(m_szName == name)
        return;
    m_szName = name;
    emit sigNameChanged(m_szName);
}

const QString CParameterConnecter::GetServerName() const
{
    return m_szServerName;
}

void CParameterConnecter::SetServerName(const QString& name)
{
    m_szServerName = name;
}

bool CParameterConnecter::GetShowServerName() const
{
    return m_bShowServerName;
}

void CParameterConnecter::SetShowServerName(bool NewShowServerName)
{
    if (m_bShowServerName == NewShowServerName)
        return;
    m_bShowServerName = NewShowServerName;
    emit sigShowServerNameChanged();
}

void CParameterConnecter::SetHost(const QString& host)
{
    if (m_szHost == host)
        return;
    m_szHost = host;
}

const QString CParameterConnecter::GetHost() const
{
    return m_szHost;
}

const quint16 CParameterConnecter::GetPort() const
{
    return m_nPort;
}

void CParameterConnecter::SetPort(quint16 port)
{
    if(m_nPort == port)
        return;
    m_nPort = port;
}

const QString CParameterConnecter::GetUser() const
{
    return m_szUser;
}

void CParameterConnecter::SetUser(const QString &user)
{
    if (m_szUser == user)
        return;
    m_szUser = user;
}

const QString CParameterConnecter::GetPassword() const
{
    return m_szPassword;
}

void CParameterConnecter::SetPassword(const QString &password)
{
    m_szPassword = password;
}

const bool CParameterConnecter::GetSavePassword() const
{
    return m_bSavePassword;
}

void CParameterConnecter::SetSavePassword(bool save)
{
    if (m_bSavePassword == save)
        return;
    m_bSavePassword = save;
}

const bool CParameterConnecter::GetOnlyView() const
{
    return m_bOnlyView;
}

void CParameterConnecter::SetOnlyView(bool only)
{
    if(m_bOnlyView == only)
        return;
    m_bOnlyView = only;
}

const bool CParameterConnecter::GetLocalCursor() const
{
    return m_bLocalCursor;
}

void CParameterConnecter::SetLocalCursor(bool cursor)
{
    if(m_bLocalCursor == cursor)
        return;
    m_bLocalCursor = cursor;
}

const bool CParameterConnecter::GetClipboard() const
{
    return m_bClipboard;
}

void CParameterConnecter::SetClipboard(bool c)
{
    m_bClipboard = c;
}

const CParameterConnecter::emProxy CParameterConnecter::GetProxyType() const
{
    return m_eProxyType;
}

void CParameterConnecter::SetProxyType(emProxy type)
{
    if (m_eProxyType == type)
        return;
    m_eProxyType = type;
}

const QString CParameterConnecter::GetProxyHost() const
{
    return m_szProxyHost;
}

void CParameterConnecter::SetProxyHost(const QString &host)
{
    m_szProxyHost = host;
}

const quint16 CParameterConnecter::GetProxyPort() const
{
    return m_nProxyPort;
}

void CParameterConnecter::SetProxyPort(quint16 port)
{
    m_nProxyPort = port;
}

const QString CParameterConnecter::GetProxyUser() const
{
    return m_szProxyUser;
}

void CParameterConnecter::SetProxyUser(const QString &user)
{
    m_szProxyUser = user;
}

const QString CParameterConnecter::GetProxyPassword() const
{
    return m_szProxyPassword;
}

void CParameterConnecter::SetProxyPassword(const QString &password)
{
    m_szProxyPassword = password;
}

int CParameterConnecter::Load(QSettings &set)
{
    SetName(set.value("Name", GetName()).toString());
    SetName(set.value("ServerName", GetServerName()).toString());
    SetShowServerName(set.value("ShowServerName", GetShowServerName()).toBool());
    SetHost(set.value("Host", GetHost()).toString());
    SetPort(set.value("Port", GetPort()).toUInt());
    SetUser(set.value("User", GetUser()).toString());
    SetSavePassword(set.value("SavePassword", GetSavePassword()).toBool());
    if(GetSavePassword())
    {
        QString szPassword;
        if(!LoadPassword(tr("Password"), "Password", szPassword, set))
            SetPassword(szPassword);
    }
    SetOnlyView(set.value("OnlyView", GetOnlyView()).toBool());
    SetLocalCursor(set.value("LocalCursor", GetLocalCursor()).toBool());
    SetClipboard(set.value("Clipboard", GetClipboard()).toBool());
    
    SetProxyType(static_cast<emProxy>(set.value("Proxy/Type",
                                    static_cast<int>(GetProxyType())).toInt()));
    SetProxyHost(set.value("Proxy/Host", GetProxyHost()).toString());
    SetProxyPort(set.value("Proxy/Port", GetProxyPort()).toUInt());
    SetProxyUser(set.value("Proxy/User", GetProxyUser()).toString());
    
    if(GetSavePassword())
    {
        QString szPassword;
        if(!LoadPassword(tr("Proxy password"), "Proxy/Password", szPassword, set))
            SetProxyPassword(szPassword);
    }
    
    return 0;
}

int CParameterConnecter::Save(QSettings &set)
{
    set.setValue("Name", GetName());
    set.setValue("ServerName", GetServerName());
    set.setValue("ShowServerName", GetShowServerName());
    set.setValue("Host", GetHost());
    set.setValue("Port", GetPort());
    set.setValue("User", GetUser());
    SavePassword("Password", GetPassword(), set, true);
    set.setValue("OnlyView", GetOnlyView());
    set.setValue("LocalCursor", GetLocalCursor());
    set.setValue("Clipboard", GetClipboard());
    
    set.setValue("Proxy/Type", (int)m_eProxyType);
    set.setValue("Proxy/Host", GetProxyHost());
    set.setValue("Proxy/Port", GetProxyPort());
    set.setValue("Proxy/User", GetProxyUser());
    SavePassword("Proxy/Password", GetProxyPassword(), set);
    
    return 0;
}

QByteArray CParameterConnecter::PasswordSum(const std::string &password,
                                          const std::string &key)
{
    QCryptographicHash sum(QCryptographicHash::Md5);
    sum.addData(password.c_str(), password.length());
    std::string pw = "RabbitRemoteControl";
    sum.addData(pw.c_str(), pw.length());
    if(!key.empty())
        sum.addData(key.c_str(), key.length());
    return sum.result();
}

int CParameterConnecter::LoadPassword(const QString &szTitle,
                                    const QString &szKey,
                                    QString &password,
                                    QSettings &set)
{
    QByteArray sum = set.value(szKey + "_sum").toByteArray();
    QByteArray pwByte = set.value(szKey).toByteArray();
    RabbitCommon::CEncrypt e;
    
    std::string key;
    if(GetParameterViewer())
        key = GetParameterViewer()->GetEncryptKey().toStdString().c_str();
    if(key.empty())
    {
        if(!e.Dencode(pwByte, password)
                && PasswordSum(password.toStdString(), key) == sum)
            return 0;
    } else {
        e.SetPassword(key.c_str());
        if(!e.Dencode(pwByte, password)
                && PasswordSum(password.toStdString(), key) == sum)
            return 0;
    }

    qDebug(Client) << "Password don't dencode";
    CDlgInputPassword d(GetParameterViewer()->GetViewPassowrd(), szTitle);
    if(QDialog::Accepted != d.exec())
    {
        SetSavePassword(false);
        return -1;
    }

    CDlgInputPassword::InputType t;
    int nRet = d.GetValue(t, password);
    if(nRet) return nRet;
    if(CDlgInputPassword::InputType::Password == t)
        return 0;
    GetParameterViewer()->SetEncryptKey(password);
    return LoadPassword(szTitle, szKey, password, set);
}

int CParameterConnecter::SavePassword(const QString &szKey,
                                    const QString &password,
                                    QSettings &set, bool bSave)
{
    if(bSave)
        set.setValue("SavePassword", GetSavePassword());
    if(!GetSavePassword())
    {
        set.remove(szKey);
        set.remove(szKey + "_sum");
        return 0;
    }

    QByteArray encryptPassword;
    RabbitCommon::CEncrypt e;
    std::string key = GetParameterViewer()->GetEncryptKey().toStdString();
    if(key.empty())
    {
        switch (GetParameterViewer()->GetPromptType()) {
        case CParameterClient::PromptType::First:
            if(GetParameterViewer()->GetPromptCount() >= 1)
                break;
            GetParameterViewer()->SetPromptCount(
                        GetParameterViewer()->GetPromptCount() + 1);
        case CParameterClient::PromptType::Always:
        {
            QString szKey;
            CDlgInputPassword::InputType t = CDlgInputPassword::InputType::Encrypt;
            CDlgInputPassword dlg(GetParameterViewer()->GetViewPassowrd());
            if(QDialog::Accepted == dlg.exec())
                dlg.GetValue(t, szKey);
            if(CDlgInputPassword::InputType::Encrypt == t)
                GetParameterViewer()->SetEncryptKey(szKey);
            break;
        }
        case CParameterClient::PromptType::No:
            break;
        }
    } else
        e.SetPassword(key.c_str());
    e.Encode(GetPassword(), encryptPassword);
    set.setValue(szKey, encryptPassword);
    set.setValue(szKey + "_sum", PasswordSum(GetPassword().toStdString(), key));
    return 0;
}
