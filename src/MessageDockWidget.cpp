#include "MessageDockWidget.h"

#include <QTextEdit>
#include <QScrollBar>

#include "MsgHandleerWapper.h"

MessageDockWidget::MessageDockWidget(QWidget* parent)
    : QDockWidget(parent)
{
    this->setWindowTitle(tr("Message"));
//    this->setFeatures(this->features()
//                      & ~QDockWidget::DockWidgetMovable
//                      & ~QDockWidget::DockWidgetFloatable);
    m_pMessageTextEdit = new QTextEdit(this);
    m_pMessageTextEdit->setReadOnly(true);
    setWidget(m_pMessageTextEdit);

    connect(MsgHandlerWapper::instance(),
            &MsgHandlerWapper::message,
            this,
            &MessageDockWidget::qtMessage);
}

MessageDockWidget::~MessageDockWidget()
{
}

void MessageDockWidget::qtMessage(QtMsgType type, const QString& msg)
{
    switch (type) {
    case QtMsgType::QtDebugMsg:
        m_pMessageTextEdit->setTextColor(Qt::blue);
        break;

    case QtMsgType::QtInfoMsg:
        m_pMessageTextEdit->setTextColor(Qt::blue);
        break;

    case QtMsgType::QtWarningMsg:
        m_pMessageTextEdit->setTextColor(Qt::darkYellow);
        break;

    case QtMsgType::QtCriticalMsg:
        m_pMessageTextEdit->setTextColor(Qt::red);
        break;

//    case QtMsgType::QtFatalMsg:
//        m_pMessageTextEdit->setTextColor(Qt::red);
//        break;

    default:
        break;

    }
    m_pMessageTextEdit->append(msg);
    auto workCursor = m_pMessageTextEdit->textCursor();
    QScrollBar *scrollbar = m_pMessageTextEdit->verticalScrollBar();
    workCursor.movePosition(QTextCursor::End);
    if (scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

void MessageDockWidget::outMessage(const QString& msg, const QColor& color_ ,const QFont& font_)
{
    Q_UNUSED(font_)
    m_pMessageTextEdit->setTextColor(color_);
    m_pMessageTextEdit->append(msg);
    auto workCursor = m_pMessageTextEdit->textCursor();
    QScrollBar *scrollbar = m_pMessageTextEdit->verticalScrollBar();
    workCursor.movePosition(QTextCursor::End);
    if (scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}
