#ifndef MESSAGEDOCKWIDGET_H
#define MESSAGEDOCKWIDGET_H

#include <QDockWidget>
#include <QMetaType>
#include <QObject>
#include <QColor>
#include <QFont>

class QTextEdit;

class MessageDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit MessageDockWidget(QWidget* parent = nullptr);
    ~MessageDockWidget();

public:

protected:

private:

public:

protected:

private:
    QTextEdit* m_pMessageTextEdit;

public slots:
    void qtMessage(QtMsgType type,const QString &msg);
    void outMessage(const QString& msg,
                    const QColor& color_ = Qt::blue ,
                    const QFont& font_ = QFont("Times", -1, -1, false));

signals:

};

#endif // MESSAGEDOCKWIDGET_H
