#ifndef CPARAMETERVIEWER_H
#define CPARAMETERVIEWER_H

#pragma once

#include "Parameter.h"

/*!
 * \~english
 * \brief The CParameterClient class
 *        The parameters is valid in the Client.
 *        The application cannot access it directly,
 *        it can only be set via CClient::GetSettingsWidgets.
 * \note
 *  - The interface only is implemented and used by Client or plugin.
 *  - If the parameters(\ref CParameterConnecter or its derived class) requires a CParameterClient.
 *    Please instantiate the parameters and call CConnecter::SetParameter in the constructor of the CConnecter derived class to set the parameters.
 *    If you are sure to the parameter does not need CParameterClient.
 *    please overload the CConnecter::SetParameterClient in the CConnecter derived class.
 *    don't set it.
 *
 * \~chinese
 * \brief 客户端参数接口。它包含客户端的参数。此类仅在客户端和插件内有效。
 *        应用程序不能直接访问，只能通过 CClient::GetSettingsWidgets 进行设置。
 * \note
 *  - 此接口仅由插件派生实现和使用。
 *  - 如果参数( CParameterConnecter 或其派生类）需要 CParameterClient 。
 *    请在 CConnecter 派生类的构造函数中实例化参数，并调用 CConnecter::SetParameter 设置参数指针。
 *    如果参数不需要 CParameterClient ，
 *    那请在 CConnecter 派生类重载 CConnecter::SetParameterClient 不设置它。
 *
 * \~
 * \see CClient::CreateConnecter CConnecter::CConnecter
 *      CConnecter::SetParameterClient CConnecter::SetParameter
 *      CParameterConnecter
 */
class CLIENT_EXPORT CParameterClient : public CParameter
{
    Q_OBJECT

public:
    explicit CParameterClient(QObject *parent = nullptr);
    virtual ~CParameterClient();

    /*!
     * \see CClient::LoadSettings
     */
    virtual int Load(QSettings &set) override;
    /*!
     * \see CClient::SaveSettings
     */
    virtual int Save(QSettings &set) override;

public:
    bool GetHookKeyboard() const;
    void SetHookKeyboard(bool newHookKeyboard);
Q_SIGNALS:
    void sigHookKeyboardChanged();
private:
    bool m_bHookKeyboard;
    Q_PROPERTY(bool HookKeyboard READ GetHookKeyboard WRITE SetHookKeyboard
               NOTIFY sigHookKeyboardChanged)
    

//////////////// Password ////////////////
public:
    const QString &GetEncryptKey() const;
    void SetEncryptKey(const QString &newPassword);
Q_SIGNALS:
    void sigEncryptKeyChanged();
private:
    QString m_szEncryptKey; //Don't save to file
    Q_PROPERTY(QString EncryptKey READ GetEncryptKey WRITE SetEncryptKey NOTIFY sigEncryptKeyChanged)

public:
    const bool &GetSavePassword() const;
    void SetSavePassword(bool NewAutoSavePassword);
Q_SIGNALS:
    void sigSavePasswordChanged(bool AutoSavePassword);

private:
    bool m_bSavePassword;
    Q_PROPERTY(bool SavePassword READ GetSavePassword WRITE SetSavePassword NOTIFY sigSavePasswordChanged)
 
public:
    enum class PromptType
    {
        No,
        First,
        Always,
    };
    Q_ENUM(PromptType)
    PromptType GetPromptType() const;
    void SetPromptType(PromptType NewPromptType);
Q_SIGNALS:
    void sigPromptTypeChanged(PromptType PromptType);    
private:
    PromptType m_PromptType;
    Q_PROPERTY(PromptType PromptType READ GetPromptType WRITE SetPromptType NOTIFY sigPromptTypeChanged)
    
public:
    int GetPromptCount() const;
    void SetPromptCount(int NewPromptCount);
Q_SIGNALS:
    void sigPromptCountChanged(int PromptCount);
private:
    int m_nPromptCount;
    Q_PROPERTY(int PromptCount READ GetPromptCount WRITE SetPromptCount NOTIFY sigPromptCountChanged)

public:
    bool GetViewPassowrd() const;
    void SetViewPassowrd(bool NewViewPassowrd);
Q_SIGNALS:
    void sigViewPassowrdChanged(bool ViewPassowrd);
private:
    bool m_bViewPassowrd;
    Q_PROPERTY(bool ViewPassowrd READ GetViewPassowrd WRITE SetViewPassowrd NOTIFY sigViewPassowrdChanged)
//////////////// Password end ////////////////
};

#endif // CPARAMETERVIEWER_H
