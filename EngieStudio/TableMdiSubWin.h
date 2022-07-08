#ifndef TABLEMDISUBWIN_H
#define TABLEMDISUBWIN_H

#include <QMainWindow>
#include <QMap>

class QTableView;
class QStandardItemModel;

class TableMdiSubWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit TableMdiSubWin(QWidget *parent = nullptr);
    ~TableMdiSubWin();

public:

protected:

private:
    bool createNodeTable();  // create simluate point table
    bool createSimulateUnitTable();  // create simulate unit table
    bool createPointTable();  // create test point table
    bool createTestGeometryTable();  // create geometry table

public:

protected:

private:
    QTableView* m_pTableView;
    QMap<QString, QStandardItemModel*> m_vTableModelList;

signals:

public slots:
};

#endif // TABLEMDISUBWIN_H
