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
#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>

#include "qcustomplot/fcustomplot.h"


class CenterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWindow(QWidget *parent = nullptr);

public:
    void InitUI();
    void SetupAccAxis(QCustomPlot *customPlot);
private:
    QWidget* base_widget_{nullptr};  // 基础窗体
    ///ECU information
    QPushButton *ecu_information_btn_[5]{nullptr};
    QLineEdit *ecu_information_line_[5]{nullptr};

    ///ECU fault information
    QPushButton *clear_dtc_btn{nullptr};  // 清除DTC
    QPushButton *read_dtc_btn{nullptr};   // 读取DTC
    QTableWidget *print_dtc_table_{nullptr};    // 打印DTC

    ///Event data
    QPushButton *event_data_btn_[7]{nullptr};
    QTableWidget *print_event_data_table_{nullptr};    // 打印DTC

    ///Axis-Event
    QPushButton *axis_btn_[7]{nullptr};
    FCustomPlot *acc_axis_{nullptr};
    FCustomPlot *data_axis_{nullptr};


signals:

public slots:
};

#endif // CENTERWINDOW_H
