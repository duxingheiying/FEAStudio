#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "File/STLFile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
