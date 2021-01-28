#ifndef CCONNECTSSH_H
#define CCONNECTSSH_H

#include "Connect.h"
#include "ConnecterSSH.h"
#include "libssh/callbacks.h"
#include "libssh/libssh.h"

class CConnectSSH : public CConnect
{
    Q_OBJECT
public:
    explicit CConnectSSH(CConnecterSSH* pConnecter, QObject *parent = nullptr);
    
    // CConnect interface
protected:
    virtual int SetParamter(void *pPara) override;
    
public slots:
    virtual int Initialize() override;
    virtual int Clean() override;
    virtual int Connect() override;
    virtual int Disconnect() override;
    virtual int Process() override;
    virtual void slotClipBoardChange() override;
    
private:
    CConnecterSSH* m_pConnecter;
    CParameterSSH* m_pPara;
    
    ssh_session m_pSession;
    ssh_channel m_pChannel;
    ssh_event m_pEvent;
    ssh_connector connector_in, connector_out, connector_err;
    
    struct ssh_callbacks_struct *m_pCb;
    
    static int cbAuthCallback(const char *prompt,
                             char *buf,
                             size_t len,
                             int echo,
                             int verify,
                             void *userdata);
    int GetPassword(const char *prompt,
                    char *buf,
                    size_t len,
                    int echo,
                    int verify);
};

#endif // CCONNECTSSH_H
