#include "Service.h"
#include <QTimer>
#include <QSettings>
#include "RabbitCommonLog.h"
#include "RabbitCommonDir.h"
#include "PluginService.h"

CService::CService(CPluginService *plugin) : QObject(),
    m_pPara(nullptr),
    m_pPlugin(plugin)
{
}

CService::~CService()
{
    LOG_MODEL_DEBUG("CService", "CService::~CService()");
}

bool CService::Enable()
{
    if(GetParameters())
        return GetParameters()->getEnable();
    return false;
}

int CService::Init()
{
    int nRet = 0;
    if(GetParameters())
    {
        QString szFile = RabbitCommon::CDir::Instance()->GetFileUserConfigure();
        QSettings set(szFile, QSettings::IniFormat);
        szFile = set.value("Configure/File" + m_pPlugin->Id(),
                           RabbitCommon::CDir::Instance()->GetDirUserConfig()
                           + QDir::separator()
                           + m_pPlugin->Id()
                           + ".rrs").toString();
        LOG_MODEL_INFO("Service", "Configure file: %s", szFile.toStdString().c_str());
        nRet = GetParameters()->OnLoad(szFile);
    }
    
    if(!Enable())
    {
        LOG_MODEL_INFO("ServiceThread", "The service [%s] is disable",
                       m_pPlugin->Name().toStdString().c_str());
        return -1;
    } else
        LOG_MODEL_INFO("ServiceThread", "The service [%s] is start",
                       m_pPlugin->Name().toStdString().c_str());
    
    nRet = OnInit();
    if(0 == nRet)
        QTimer::singleShot(0, this, SLOT(slotProcess()));

    return nRet;
}

int CService::OnInit()
{
    return 0;
}

int CService::Clean()
{
    int nRet = 0;
    
    OnClean();

    if(m_pPara)
    {
        m_pPara->deleteLater();
        m_pPara = nullptr;
    }
    return nRet;
}

int CService::OnClean()
{
    return 0;
}

void CService::slotProcess()
{
    int nRet = OnProcess();
    if(nRet < 0) return;
    if(0 == nRet)
        QTimer::singleShot(0, this, SLOT(slotProcess()));
}

int CService::OnProcess()
{
    return 0;
}

CParameterService* CService::GetParameters()
{
    return m_pPara;
}

int CService::SaveConfigure(const QString &szDir)
{
    int nRet = 0;
    if(GetParameters())
    {
        QString szFile;
        if(szDir.isEmpty())
        {
            szFile = RabbitCommon::CDir::Instance()->GetFileUserConfigure();
            QSettings set(szFile, QSettings::IniFormat);
            szFile = set.value("Configure/File" + m_pPlugin->Id(),
                               RabbitCommon::CDir::Instance()->GetDirUserConfig()
                               + QDir::separator()
                               + m_pPlugin->Id()
                               + ".rrs").toString();
        } else {
            szFile = szDir + QDir::separator() + m_pPlugin->Id() + ".rrs";
        }
        nRet = GetParameters()->OnSave(szFile);
    }
    return nRet;
}
