#ifndef PROPERTYDOCKWIDGET_H
#define PROPERTYDOCKWIDGET_H

#include <QDockWidget>

class QTreeView;

class PropertyDockWidget : public QDockWidget
{
public:
    explicit PropertyDockWidget(QWidget* parent = nullptr);
    ~PropertyDockWidget();

public:

protected:

private:

public:

protected:

private:
    QTreeView* m_pTreeView;

protected slots:

signals:

};

#endif // PROPERTYDOCKWIDGET_H
