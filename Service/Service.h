// Author: Kang Lin <kl222@126.com>

#ifndef CSERVICE_H_KL_2021_07_13
#define CSERVICE_H_KL_2021_07_13

#pragma once

#include "ParameterService.h"
#include <QSharedPointer>

class CPluginService;

/*!
 * \~chinese 服务接口。由具体的协议实现。支持非Qt事件循环。详见： Init() 、 slotProcess()
 *           如果不启用非Qt事件循环。则 OnInit() 返回 > 0
 *
 * \~english
 * \brief The service interface. by specific protocol implement.
 *        Support non-Qt event loop. see: Init(), slotProcess().
 *        If don't use non-Qt event loop. then OnInit() return > 0
 *
 * \~
 * \ingroup LIBAPI_SERVICE
 * \see CPluginService
 */
class SERVICE_EXPORT CService : public QObject
{
    Q_OBJECT

public:
    explicit CService(CPluginService *plugin);
    virtual ~CService();

    /*!
     * \~chinese 加载参数，支持非Qt事件循环
     * \~english Load parameters, support non-Qt event loop
     */
    virtual int Init();
    virtual int Clean();

    CParameterService* GetParameters();
#ifdef HAVE_GUI
    /*!
     * \~chinese 得到设置参数窗口
     * \return 设置参数窗口。此窗口的所有者为调用者。
     * \note 此窗口必须有定义槽 \b slotAccept 。
     *       例如: CFrmParameterFreeRDP::slotAccept
     *
     * \~english GetParameterWidget
     * \return Parameter widget. The QWidget owner is caller.
     * \note the widget must has slot \b slotAccept .
     *         Eg: CFrmParameterFreeRDP::slotAccept
     *
     * \~
     * \snippet Plugins/FreeRDP/Service/FrmParameterFreeRDP.h Accept parameters
     */   
    virtual QWidget* GetParameterWidget(QWidget* parent = nullptr) = 0;
#endif
    
    virtual int LoadConfigure(const QString& szDir = QString());
    virtual int SaveConfigure(const QString& szDir = QString());

protected Q_SLOTS:
    /*!
     * \~chinese 支持非Qt事件循环
     * \~english Support non-Qt event loop
     */
    virtual void slotProcess();

protected:
    /*!
     * \return
     * \li < 0: error
     * \li = 0: Use OnProcess (non-Qt event loop)
     * \li > 0: Don't use OnProcess (qt event loop)
     */
    virtual int OnInit() = 0;
    virtual int OnClean() = 0;
    /*!
     * \return
     * \li <  0: error or stop
     * \li >= 0: Call interval
     */
    virtual int OnProcess();

    CParameterService* m_pPara;
    CPluginService* m_pPlugin;
};

#endif // CSERVICE_H_KL_2021_07_13
