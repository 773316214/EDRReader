/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.2
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.06
**
****************************************************************************/
#include "mainwindow.h"
#include "Log/flog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    el::Loggers::removeFlag(el::LoggingFlag::NewLineForContainer);
    el::Helpers::installLogDispatchCallback<LogHandler>("LogHandler");
    el::Helpers::installLogDispatchCallback<HtmlHandler>("HtmlHandler");
    LOG(INFO) << "Starting log";
    LogHandler* logHandler = el::Helpers::logDispatchCallback<LogHandler>("LogHandler");
    logHandler->setEnabled(false);

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
