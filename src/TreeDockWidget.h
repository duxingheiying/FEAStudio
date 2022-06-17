#ifndef TREEDOCKWIDGET_H
#define TREEDOCKWIDGET_H

#include <QDockWidget>

class QTabWidget;
class QTreeWidget;

class TreeDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit TreeDockWidget(QWidget *parent = nullptr);
    ~TreeDockWidget();

public:


protected:


private:


public:


protected:



private:
    QTabWidget* m_pTabWidget;
    QTreeWidget* m_pDataTreeWdiget;

signals:

public slots:

};

#endif // TREEDOCKWIDGET_H
