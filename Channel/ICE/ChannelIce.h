//! @author Kang Lin(kl222@126.com)

#ifndef CDATACHANNELICE_H
#define CDATACHANNELICE_H

#pragma once

#include "rtc/rtc.hpp"
#include "IceSignal.h"
#include "Channel.h"
#include <memory>
#include <QMutex>
#include <QSharedPointer>

/*!
 * \~chinese
 * \brief ICE 通道类。此类实现一个 ICE 的通道。
 *
 * \~english
 * \brief The ICE channel interface class. This class implements a ICE channel.
 * 
 * \~
 * \ingroup LIBAPI_ICE LIBAPI_CHANNEL
 * \see CIceSignal
 */
class CHANNEL_EXPORT CChannelIce : public CChannel
{
    Q_OBJECT

public:
    explicit CChannelIce(CIceSignal* pSignal,
                          QObject *parent = nullptr);
    virtual ~CChannelIce();

    //! @note These properties must be set before calling Open
    int SetConfigure(const rtc::Configuration& config);
    
    //! Open channel. Used for active callers
    //! @param bData: true: open data channel
    //!              false: don't open data channel
    //! @note Must call SetConfigure set the service properties before calling it
    //!        Called by client
    virtual bool open(const QString& user,
                      const QString& peer,
                      bool bChannelId);
    //! Open channel. For passive receivers
    //! @note Must call SetConfigure set the service properties before calling it
    //! @note Called by service
    virtual bool open(const QString& fromUser,
                      const QString& toUser,
                      const QString& channelId,
                      const QString& type,
                      const QString& sdp);
    virtual void close();

    QString GetUser();
    QString GetPeerUser();
    QString GetChannelId();

private Q_SLOTS:
    virtual void slotSignalConnected();
    virtual void slotSignalDisconnected();
    virtual void slotSignalReceiverCandiate(const QString& fromUser,
                                            const QString& toUser,
                                            const QString& channelId,
                                            const QString& mid,
                                            const QString& sdp);
    virtual void slotSignalError(int error, const QString& szError);
    virtual void slotSignalReceiverDescription(const QString& fromUser,
                                               const QString& toUser,
                                               const QString& channelId,
                                               const QString& type,
                                               const QString& sdp);

private:
    CChannelIce(QObject *parent = nullptr);

    virtual int SetSignal(CIceSignal* signal);
    virtual int SetDataChannel(std::shared_ptr<rtc::DataChannel>);   
    virtual int CreateDataChannel(bool bDataChannel);
    QString GenerateID(const QString& lable = QString());
    
    CIceSignal* m_pSignal;
    QString m_szUser;
    QString m_szPeerUser;
    QString m_szChannelId;
    rtc::Configuration m_Config;
    std::shared_ptr<rtc::PeerConnection> m_peerConnection;
    std::shared_ptr<rtc::DataChannel> m_dataChannel;

    QByteArray m_data;
    QMutex m_MutexData;

protected:
    bool isSequential() const;
    qint64 writeData(const char *data, qint64 len);
    qint64 readData(char *data, qint64 maxlen);
};

#endif // CDATACHANNELICE_H
