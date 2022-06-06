/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.1
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.06
**
****************************************************************************/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    InitUI();
    setCentralWidget(center_window_);
    resize(1000, 600);
}

MainWindow::~MainWindow()
{
}


void MainWindow::InitUI()
{
    center_window_ = new CenterWindow;
}
