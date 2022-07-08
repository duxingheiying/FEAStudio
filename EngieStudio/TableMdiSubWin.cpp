#include "TableMdiSubWin.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

TableMdiSubWin::TableMdiSubWin(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Table"));
    setWindowIcon(QIcon(""));
    m_pTableView = new QTableView(this);
    m_pTableView->verticalHeader()->hide();
    m_pTableView->setSortingEnabled(true);
    m_pTableView->setShowGrid(true);
    m_pTableView->setGridStyle(Qt::SolidLine);
    m_pTableView->setAlternatingRowColors(true);
    m_pTableView->setStyleSheet("QTableView{"
                                "background-color: rgb(255, 255, 255);"
                                "alternate-background-color: rgb(150, 200, 230);}"
                                "QHeaderView::section, QTableCornerButton::section {"
                                "padding: 1px;"
                                "border: none;"
                                "border-bottom: 1px solid rgb(75, 120, 154);"
                                "border-right: 1px solid rgb(75, 120, 154);"
                                "border-bottom: 1px solid gray;"
                                "background-color:rgba(185, 185, 185, 1);"
                                "color:rgba(255,255,255,255);};" );
    setCentralWidget(m_pTableView);
    createNodeTable();
}

TableMdiSubWin::~TableMdiSubWin()
{
}

bool TableMdiSubWin::createNodeTable()  // create simluate point table
{
    QStringList _StrList;
    _StrList<<"Node"<<"ICS"<<"OCS"<<"X"<<"Y"<<"Z";
    QStandardItemModel* _itemmodel = new QStandardItemModel(2, _StrList.size());
    _itemmodel->setHorizontalHeaderLabels(_StrList);
    m_pTableView->setModel(_itemmodel);
    QStandardItem* _item;
    int i = 0;
    return true;
}

bool TableMdiSubWin::createSimulateUnitTable()  // create simulate unit table
{
    return true;
}

bool TableMdiSubWin::createPointTable()  // create test point table
{
    return true;
}

bool TableMdiSubWin::createTestGeometryTable()  // create geometry table
{
    return true;
}
