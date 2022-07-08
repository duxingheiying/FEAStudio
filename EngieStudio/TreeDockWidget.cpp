#include "TreeDockWidget.h"

#include <QTabWidget>
#include <QTreeWidget>
#include <QHeaderView>
#include <QTreeView>


TreeDockWidget::TreeDockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    this->setWindowTitle(tr("TableTree"));
    m_pTabWidget = new QTabWidget(this);
    this->setWidget(m_pTabWidget);
    m_pDataTreeWdiget = new QTreeWidget(m_pTabWidget);
    m_pDataTreeWdiget->header()->hide();
    m_pTabWidget->addTab(m_pDataTreeWdiget, tr("DataTree"));
}

TreeDockWidget::~TreeDockWidget()
{
}
