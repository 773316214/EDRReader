/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 0.0.5
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.24
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CenterWindow/centerwindow.h"
#include "Serial/masterthread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void InitUI();
    void InitBar();
    void ConnectSignal();

private:
    CenterWindow *center_window_{nullptr};
    serial_port::MasterSerialThread *serial_{nullptr};

    QMenuBar *menubar_{nullptr};  // a menu bar
    QToolBar *toolbar_{nullptr};  // a tool bar
    QStatusBar *statusbar_{nullptr};  // a status bar
};
#endif // MAINWINDOW_H
