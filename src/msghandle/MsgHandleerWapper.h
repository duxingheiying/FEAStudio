#ifndef MSGHANDLEERWAPPER_H
#define MSGHANDLEERWAPPER_H

#include <QObject>

class MsgHandlerWapper : public QObject
{
    Q_OBJECT
public:
//    explicit MsgHandleerWapper(QObject *parent = nullptr);

    static MsgHandlerWapper* instance();  // instance class

public:

protected:

private:

public:

protected:

private:
    MsgHandlerWapper();
    static MsgHandlerWapper* m_instance;

signals:
    void message(QtMsgType type, const QString& msg);

public slots:

};

#endif // MSGHANDLEERWAPPER_H
