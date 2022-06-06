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

#ifndef FCUSTOMPLOT_H
#define FCUSTOMPLOT_H

#include "QCustomPlot/qcustomplot.h"

class FCustomPlot : public QCustomPlot
{
    Q_OBJECT
public:
    explicit FCustomPlot(QWidget *parent = nullptr);

signals:

public slots:

};

#endif // FCUSTOMPLOT_H
