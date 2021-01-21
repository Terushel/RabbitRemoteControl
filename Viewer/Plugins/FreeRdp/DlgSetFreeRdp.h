//! @author: Kang Lin(kl222@126.com)

#ifndef DLGSETFREERDP_H
#define DLGSETFREERDP_H

#include <QDialog>
#include "freerdp/freerdp.h"
#include "ConnecterFreeRdp.h"

namespace Ui {
class CDlgSetFreeRdp;
}

class CDlgSetFreeRdp : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgSetFreeRdp(CConnecterFreeRdp::CParamterFreeRdp* pSettings, QWidget *parent = nullptr);
    ~CDlgSetFreeRdp();
    
private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();
    void on_rbFullScreen_clicked(bool checked);
    
private:
    int InsertDesktopSize(int width, int height);
    
private:
    Ui::CDlgSetFreeRdp *ui;
    CConnecterFreeRdp::CParamterFreeRdp* m_pSettings;
    
    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // DLGSETFREERDP_H
