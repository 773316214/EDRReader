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
#include "centerwindow.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLinearGradient>

CenterWindow::CenterWindow(QWidget *parent) : QWidget(parent)
{
    InitUI();
}


void CenterWindow::InitUI()
{
   base_widget_ = new QWidget(this);
   QHBoxLayout* base_layout = new QHBoxLayout;  //
   QVBoxLayout *info_fault_info_layout = new QVBoxLayout;
   ///ECU information
   /// ——————QFormLayout(ECU_information_form)——————————————————
   ///|
   ///|     |序列号|        serial_line_
   ///|     |硬件版本号|   hardware_version_line_
   ///|     |软件版本号|     software_version_line_
   ///|     |生产日期|       manufacturing_date_line_
   ///|     |功能配置字|     function_configration_data_line_
   ///|_________________________________________________________
   QFormLayout *ecu_information_form = new QFormLayout;   // 放置ECU信息控件 表单
   QStringList ecu_information_string = {"序列号", "硬件版本号", "软件版本号", "生产日期", "功能配置字"};
   for (int i = 0; i < 5; i++) {
       ecu_information_btn_[i] = new QPushButton(ecu_information_string[i]);
//       ecu_information_btn_[i]->setMaximumWidth(100);
       ecu_information_line_[i] = new QLineEdit;
//       ecu_information_line_[i]->setMaximumWidth(120);
       ecu_information_form->addRow(ecu_information_btn_[i], ecu_information_line_[i]);
   }
   ecu_information_form->setMargin(0);
   info_fault_info_layout->addLayout(ecu_information_form);

   ///Fault information
   /// ——————QFormLayout(ECU_information_form)——————————————————
   ///|
   ///|     |           清除故障码           |
   ///|     |           读取故障码           |
   ///|     __________print_dtc_table________
   ///|     |   故障码   |        含义       |
   ///|     --------------------------------
   ///|     |           |                   |
   ///|     --------------------------------
   ///|     |           |                   |
   ///|     --------------------------------
   ///|     |           |                   |
   ///|     --------------------------------
   ///|     |           |                   |
   ///|     --------------------------------
   QVBoxLayout *fault_information_box = new QVBoxLayout;
   clear_dtc_btn = new QPushButton("清除故障码");
//   clear_dtc_btn->setMaximumWidth(200);
   read_dtc_btn = new QPushButton("读取故障码");
//   read_dtc_btn->setMaximumWidth(200);
   print_dtc_table_ = new QTableWidget;
//   print_dtc_table_->setMaximumWidth(200);
   fault_information_box->addWidget(clear_dtc_btn);
   fault_information_box->addWidget(read_dtc_btn);
   fault_information_box->addWidget(print_dtc_table_);
   info_fault_info_layout->addLayout(fault_information_box);

   ///Event data
   /// —————————————QGridLayout(event_data_box)—————————————
   ///| 事件数据
   ///|     |FA13||FA14||FA15||0216||0217||0218||0219|
   ///|     ------------print_event_data_table_-------------
   ///|     |               |                              |
   ///|     -----------------------------------------------|
   ///|     |               |                              |
   ///|     -----------------------------------------------|
   ///|     |               |                              |
   ///|     -----------------------------------------------|
   ///|     |               |                              |
   ///|     -----------------------------------------------|
   ///|     |               |                              |
   ///|     |----------------------------------------------|
   ///|
   QVBoxLayout *event_data_plot_layout = new QVBoxLayout;
   QGridLayout *event_data_box = new QGridLayout;
   QLabel *event_data_label = new QLabel("事件数据");
   event_data_box->addWidget(event_data_label,0, 0);
   QStringList event_data_string = {"FA13", "FA14", "FA15", "0216", "0217", "0218", "0219"};
   for (int i = 0; i < event_data_string.size(); i++) {
       event_data_btn_[i] = new QPushButton(event_data_string[i]);
       event_data_box->addWidget(event_data_btn_[i], 1, i);
   }
   print_event_data_table_ = new QTableWidget;
   event_data_box->addWidget(print_event_data_table_, 2, 0, 10, 10);
   event_data_plot_layout->addLayout(event_data_box);

   ///Axis-Event
   /// —————————————QGridLayout(axis_box)—————————————
   ///| 事件数据
   ///|     |FA13||FA14||FA15||0216||0217||0218||0219|
   ///|
   ///|     |                     *.           | -                             |
   ///|     |                *.  *.   *.       | * -                           |
   ///|     |                 *.         *.    |    *-                         |
   ///|     |               *.            *.   |     * -  -                    |
   ///|     |         * . * .                  |       *     - -               |
   ///|     |        * .                       |         *        -            |
   ///|     |      * .                         |            * *       -   -    |
   ///|     |     *.                           |                  *          - |
   ///|     |   *.                             |                     * *  *    |

   QGridLayout *axis_box = new QGridLayout;
   QLabel *plot_label = new QLabel("数据曲线");
   axis_box->addWidget(plot_label,0, 0);
   QStringList axis_string = {"FA13", "FA14", "FA15", "0216", "0217", "0218", "0219"};
   for (int i = 0; i < axis_string.size(); i++) {
       axis_btn_[i] = new QPushButton(event_data_string[i]);
       axis_box->addWidget(axis_btn_[i], 1, i);
   }
   acc_axis_ = new FCustomPlot;
   SetupAccAxis(acc_axis_);
   data_axis_ = new FCustomPlot;
   SetupAccAxis(data_axis_);
   axis_box->addWidget(acc_axis_, 2, 0, 10, 6);
   axis_box->addWidget(data_axis_, 2, 6, 10, 5);
   event_data_plot_layout->addLayout(axis_box);

   base_layout->addLayout(info_fault_info_layout);
   base_layout->addLayout(event_data_plot_layout);
   // 设置info_fault_info_layout : event_data_plot_layout 伸缩系数1 : 4
   base_layout->setStretchFactor(info_fault_info_layout, 1);
   base_layout->setStretchFactor(event_data_plot_layout, 4);
   setLayout(base_layout);
   show();
}

void CenterWindow::SetupAccAxis(QCustomPlot *customPlot)
{
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    // setup for graph 0: key axis left, value axis bottom
    // will contain left maxwell-like function
    customPlot->addGraph(customPlot->yAxis, customPlot->xAxis);
    customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
//    customPlot->graph(0)->setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // fill with texture of specified image
    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->graph(0)->setName("EDR Acc");

    // setup for graph 1: key axis bottom, value axis left (those are the default axes)
    // will contain bottom maxwell-like function
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));
//    customPlot->graph(1)->setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // same fill as we used for graph 0
    customPlot->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, Qt::red, Qt::white, 7));
    ///customPlot->graph(1)->setErrorType(QCPGraph::etValue);
    customPlot->graph(1)->setName("ACU Acc");

    // setup for graph 2: key axis top, value axis right
    // will contain high frequency sine with low frequency beating:
    customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis2);
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setName("High frequency sine");

}
