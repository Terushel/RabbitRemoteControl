// Author: Kang Lin <kl222@126.com>

#include "ParameterDlgSettings.h"
#include "ui_ParameterDlgSettings.h"
#include "mainwindow.h"
#include "ManagePassword.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonLog.h"
#include "Ice.h"

CParameterDlgSettings::CParameterDlgSettings(CParameterApp *pPara, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CParameterDlgSettings),
    m_pParameters(pPara)
{
    ui->setupUi(this);

    QWidget* pWidget = CICE::Instance()->GetWidget(this);
    if(pWidget)
    {
        ui->tabWidget->addTab(pWidget, pWidget->windowTitle());
        bool check = false;
        check = connect(this, SIGNAL(accepted()),
                        pWidget, SLOT(slotAccept()));
        if(!check)
        {
            LOG_MODEL_ERROR("CParameterDlgSettings",
                            "Class %s must has slot slotAccept(), please add it",
                            pWidget->metaObject()->className());
        }
        Q_ASSERT(check);
    }

    ui->leShotScreenSavepath->setText(m_pParameters->GetScreenShotPath());
    ui->cbShotRemoteDesktop->setChecked(m_pParameters->GetScreenShot());
    switch (m_pParameters->GetScreenShotEndAction()) {
    case CParameterApp::NoAction:
        ui->rbShotScreenNoAction->setChecked(true);
        break;
    case CParameterApp::OpenFile:
        ui->rbShotScreenOpenFile->setChecked(true);
        break;
    case CParameterApp::OpenFolder:
        ui->rbShotScreenOpenFolder->setChecked(true);
        break;    
    }
    
    ui->cbReciverShortCut->setChecked(m_pParameters->GetReceiveShortCut());
    ui->cbSaveMainWindowStatus->setChecked(m_pParameters->GetSaveMainWindowStatus());
    ui->cbResumLasterClose->setChecked(m_pParameters->GetOpenLasterClose());
    
    switch (m_pParameters->GetTabPosition()) {
    case QTabWidget::North:
        ui->rbNorth->setChecked(true);
        break;
    case QTabWidget::South:
        ui->rbSouth->setChecked(true);
        break;
    case QTabWidget::West:
        ui->rbWest->setChecked(true);
        break;
    case QTabWidget::East:
        ui->rbEast->setChecked(true);
        break;
    }
    
    ui->sbRecentMenuMaxCount->setValue(m_pParameters->GetRecentMenuMaxCount());
    
    ui->leEncryptKey->setText(CManagePassword::Instance()->GetEncryptKey());
    ui->cbSavePassword->setChecked(CManagePassword::Instance()->GetSavePassword());
    ui->cbEnableViewPassword->setChecked(CManagePassword::Instance()->GetViewPassowrd());
    ui->pbEncryptKey->setEnabled(ui->cbEnableViewPassword->isChecked());
    switch (CManagePassword::Instance()->GetPromptType()) {
    case CManagePassword::PromptType::Always:
        ui->rbPromptAlways->setChecked(true);
        break;
    case CManagePassword::PromptType::First:
        ui->rbPromptFirst->setChecked(true);
        break;
    case CManagePassword::PromptType::No:
        ui->rbPromptNo->setChecked(true);
        break;
    }
    
    ui->rbSystemTrayIconFavorite->hide();
    switch (m_pParameters->GetSystemTrayIconMenuType()) {
    case CParameterApp::SystemTrayIconMenuType::No:
        ui->rbSystemTrayIconNo->setChecked(true);
        break;
    case CParameterApp::SystemTrayIconMenuType::RecentOpen:
        ui->rbSystemTrayIconRecentOpen->setChecked(true);
        break;
    case CParameterApp::SystemTrayIconMenuType::Remote:
        ui->rbSystemTrayIconRemote->setChecked(true);
        break;
    case CParameterApp::SystemTrayIconMenuType::Favorite:
        ui->rbSystemTrayIconFavorite->setChecked(true);
        break;
    }
    ui->cbShowSystemTrayIcon->setChecked(m_pParameters->GetEnableSystemTrayIcon());
    
    ui->cbFavoriteDoubleEdit->setChecked(m_pParameters->GetFavoriteEdit());
}

CParameterDlgSettings::~CParameterDlgSettings()
{
    delete ui;
}

void CParameterDlgSettings::on_pbOk_clicked()
{
    if(!m_pParameters) return;
    
    m_pParameters->SetScreenShot(ui->cbShotRemoteDesktop->isChecked());
    m_pParameters->SetScreenShotPath(ui->leShotScreenSavepath->text());
    if(ui->rbShotScreenNoAction->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::NoAction);
    if(ui->rbShotScreenOpenFile->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::OpenFile);
    if(ui->rbShotScreenOpenFolder->isChecked())
        m_pParameters->SetScreenShotEndAction(CParameterApp::OpenFolder);
    
    m_pParameters->SetReceiveShortCut(ui->cbReciverShortCut->isChecked());
    m_pParameters->SetSaveMainWindowStatus(ui->cbSaveMainWindowStatus->isChecked());
    m_pParameters->SetOpenLasterClose(ui->cbResumLasterClose->isChecked());
    
    if(ui->rbNorth->isChecked()) m_pParameters->SetTabPosition(QTabWidget::North);
    if(ui->rbSouth->isChecked()) m_pParameters->SetTabPosition(QTabWidget::South);
    if(ui->rbEast->isChecked()) m_pParameters->SetTabPosition(QTabWidget::East);
    if(ui->rbWest->isChecked()) m_pParameters->SetTabPosition(QTabWidget::West);
    
    m_pParameters->SetRecentMenuMaxCount(ui->sbRecentMenuMaxCount->value());
    
    CManagePassword::Instance()->SetEncryptKey(ui->leEncryptKey->text());
    CManagePassword::Instance()->SetSavePassword(ui->cbSavePassword->isChecked());
    CManagePassword::Instance()->SetViewPassowrd(ui->cbEnableViewPassword->isChecked());
    if(ui->rbPromptAlways->isChecked())
        CManagePassword::Instance()->SetPromptType(CManagePassword::PromptType::Always);
    if(ui->rbPromptFirst->isChecked())
        CManagePassword::Instance()->SetPromptType(CManagePassword::PromptType::First);
    if(ui->rbPromptNo->isChecked())
        CManagePassword::Instance()->SetPromptType(CManagePassword::PromptType::No);
    
    if(ui->rbSystemTrayIconNo->isChecked())
        m_pParameters->SetSystemTrayIconMenuType(CParameterApp::SystemTrayIconMenuType::No);
    if(ui->rbSystemTrayIconRecentOpen->isChecked())
        m_pParameters->SetSystemTrayIconMenuType(CParameterApp::SystemTrayIconMenuType::RecentOpen);
    if(ui->rbSystemTrayIconRemote->isChecked())
        m_pParameters->SetSystemTrayIconMenuType(CParameterApp::SystemTrayIconMenuType::Remote);
    if(ui->rbSystemTrayIconFavorite->isChecked())
        m_pParameters->SetSystemTrayIconMenuType(CParameterApp::SystemTrayIconMenuType::Favorite);
    
    m_pParameters->SetEnableSystemTrayIcon(ui->cbShowSystemTrayIcon->isChecked());
    m_pParameters->SetFavoriteEdit(ui->cbFavoriteDoubleEdit->isChecked());
    
    accept();
}

void CParameterDlgSettings::on_pbNo_clicked()
{
    reject();
}

void CParameterDlgSettings::on_cbEnableViewPassword_clicked(bool checked)
{
    ui->pbEncryptKey->setEnabled(checked);
}

void CParameterDlgSettings::on_pbEncryptKey_clicked()
{
    switch(ui->leEncryptKey->echoMode())
    {
    case QLineEdit::Password:
        ui->leEncryptKey->setEchoMode(QLineEdit::Normal);
        ui->pbEncryptKey->setIcon(QIcon(":/image/EyeOff"));
        break;
    case QLineEdit::Normal:
        ui->leEncryptKey->setEchoMode(QLineEdit::Password);
        ui->pbEncryptKey->setIcon(QIcon(":/image/EyeOn"));
        break;
    default:
        break;
    }
}

void CParameterDlgSettings::on_pbScreenShotBrower_clicked()
{
    QString szPath = RabbitCommon::CDir::Instance()->GetOpenDirectory(this,
                                                    tr("Open shot screen path"),
                                              ui->leShotScreenSavepath->text());
    if(szPath.isEmpty())
        return;
    ui->leShotScreenSavepath->setText(szPath);
}

void CParameterDlgSettings::on_cbShowSystemTrayIcon_toggled(bool checked)
{
    ui->gbSystemTrayIconContextMenu->setEnabled(checked);
}
