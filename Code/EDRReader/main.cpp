/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 1.0.2
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.08.09
**
****************************************************************************/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QApplication::setWindowIcon(QIcon(":/image/Image/EDRReader.ico"));
    w.setWindowTitle("EDRReader Version:1.0.2");
    w.show();
    return a.exec();
}
