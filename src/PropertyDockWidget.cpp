#include "PropertyDockWidget.h"

#include <QTabWidget>
#include <QTreeView>

PropertyDockWidget::PropertyDockWidget(QWidget* parent)
    : QDockWidget(parent)
{
    this->setWindowTitle(tr("Property"));
    m_pTreeView = new QTreeView(this);
    this->setWidget(m_pTreeView);
}

PropertyDockWidget::~PropertyDockWidget()
{
}
