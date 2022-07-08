#include "MsgHandleerWapper.h"

#include <QMetaType>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>

#include <iostream>
using namespace std;

//MsgHandleerWapper::MsgHandleerWapper(QObject *parent) :
//    QObject(parent)
//{
//}

void static msgHandlerFunction(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    QMetaObject::invokeMethod(MsgHandlerWapper::instance(), "message",
                              Qt::AutoConnection,
                              Q_ARG(QtMsgType, type),
                              Q_ARG(QString, msg));

//    cout<<"you have call the function"<<endl;
}

MsgHandlerWapper* MsgHandlerWapper::m_instance = nullptr;

MsgHandlerWapper* MsgHandlerWapper::instance()
{
    static QMutex mutex;
    if ( !m_instance ) {
        QMutexLocker locker(&mutex);
        if ( !m_instance ) {
            m_instance = new MsgHandlerWapper;
        }
    }
    return m_instance;
}

MsgHandlerWapper::MsgHandlerWapper() :
    QObject(qApp)
{
    qRegisterMetaType<QtMsgType>("QtMsgType");
    qInstallMessageHandler(msgHandlerFunction);
}
