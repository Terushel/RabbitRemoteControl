// Author: Kang Lin <kl222@126.com>

#include "ConnecterFreeRDP.h"
#include "ConnectFreeRDP.h"
#include <QInputDialog>
#include "DlgSetFreeRDP.h"

CConnecterFreeRDP::CConnecterFreeRDP(CPluginClient *parent)
    : CConnecterDesktopThread(parent)
{
    //WLog_SetLogLevel(WLog_GetRoot(), WLOG_TRACE);
    SetParameter(&m_ParameterFreeRdp);
    // 在 freerdp_client_context_free 中释放
    m_ParameterFreeRdp.m_pSettings = freerdp_settings_new(0);
    GetParameter()->SetPort(3389);
}

CConnecterFreeRDP::~CConnecterFreeRDP()
{
    qDebug(FreeRDP) << "CConnecterFreeRdp::~CConnecterFreeRdp()";
}

qint16 CConnecterFreeRDP::Version()
{
    return 0;
}

QDialog *CConnecterFreeRDP::GetDialogSettings(QWidget *parent)
{
    return new CDlgSetFreeRDP(&m_ParameterFreeRdp, parent);
}

CConnect *CConnecterFreeRDP::InstanceConnect()
{
    CConnectFreeRDP* p = new CConnectFreeRDP(this);
    return p;
}
