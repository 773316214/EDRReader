/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 0.0.0
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.02
**
****************************************************************************/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QApplication::setWindowIcon(QIcon(":/image/Image/EDRReader.ico"));
    w.show();
    return a.exec();
}
