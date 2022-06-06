﻿/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.1
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.06
**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CenterWindow/centerwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void InitUI();

private:
    CenterWindow *center_window_{nullptr};
};
#endif // MAINWINDOW_H
