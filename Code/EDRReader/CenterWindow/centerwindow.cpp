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

#include "centerwindow.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLinearGradient>
#include <cstdlib>
#include <time.h>
#include "Log/flog.h"
#include "Universal/universal.h"
#include "Serial/masterthread.h"

typedef unsigned int DataType;

CenterWindow::CenterWindow(QWidget *parent) : QWidget(parent)
{
    InitUI();
    InitPlot(*acc_axis_, "EDR_ACC", "ACU_ACC");
    InitPlot(*data_axis_, "VehicleSpeed", "_");
    InitConnect();

}

const QMap<QVector<unsigned char>, QString> DTC = {
    {{0x91, 0x17, 0x17}, "ECU供电电压过高"}, {{0x91, 0x17, 0x16}, "ECU供电电压过低"}, {{0xC0, 0x73, 0x00}, "总线BusOff"},
    {{0xC1, 0x41, 0x00}, "BDM1节点丢失故障(BDM1(0x392))"}, {{0xD1, 0x41, 0x00}, "BDM8节点丢失故障(BDM8(0x536))"}, {{0xD1, 0x42, 0x00}, "BDM9节点丢失故障(BDM9(0x539))"},
    {{0xC1, 0x00, 0x00}, "EMS2节点丢失故障(EMS2(0x1B5))"}, {{0xC2, 0x48, 0x00}, "TBOX1节点丢失故障(EP_TBOX1(0x579))"}, {{0xC1, 0x02, 0x00}, "VCU2节点丢失故障(EP_VCU2(0x75))"},
    {{0xC1, 0x55, 0x00}, "MMI21节点丢失故障(MMI21(0x21E))"}, {{0xC1, 0x05, 0x00}, "ADAS2节点丢失故障(S_ADAS2(0x15))"}, {{0xC1, 0x29, 0x00}, "EB1节点丢失故障(S_eB1(0x1C6))"},
    {{0xC1, 0x21, 0x00}, "ESC1节点丢失故障(S_ESC1(0xE5))"}, {{0xD1, 0x21, 0x00}, "ESC5节点丢失故障(S_ESC5(0x26E))"}, {{0xD1, 0x22, 0x00}, "ESC7节点丢失故障(S_ESC7(0x291))"},
    {{0xD1, 0x23, 0x00}, "ESC8节点丢失故障(S_ESC8(0x27E))"}, {{0xC1, 0x26, 0x00}, "SAS1节点丢失故障(SAS1(0x0C4))"},
    {{0x11, 0x10, 0x1B}, "驾驶员安全气囊电阻过高"}, {{0x11, 0x10, 0x1A}, "驾驶员安全气囊电阻过低"}, {{0x11, 0x10, 0x11}, "驾驶员安全气囊对地短路"}, {{0x11, 0x10, 0x12}, "驾驶员安全气囊对电源短路"},
    {{0x11, 0x11, 0x1B}, "前排乘员安全气囊电阻过高"}, {{0x11, 0x11, 0x1A}, "前排乘员安全气囊电阻过低"}, {{0x11, 0x11, 0x11}, "前排乘员安全气囊对地短路"}, {{0x11, 0x11, 0x12}, "前排乘员安全气囊对电源短路"},
    {{0x11, 0x12, 0x1B}, "驾驶员安全带预紧器电阻过高"}, {{0x11, 0x12, 0x1A}, "驾驶员安全带预紧器电阻过低"}, {{0x11, 0x12, 0x11}, "驾驶员安全带预紧器对地短路"}, {{0x11, 0x12, 0x12}, "驾驶员安全带预紧器对电源短路"},
    {{0x11, 0x13, 0x1B}, "前排乘员安全带预紧器电阻过高"}, {{0x11, 0x13, 0x1A}, "前排乘员安全带预紧器电阻过低"}, {{0x11, 0x13, 0x11}, "前排乘员安全带预紧器对地短路"}, {{0x11, 0x13, 0x12}, "前排乘员安全带预紧器对电源短路"},
    {{0x11, 0x14, 0x1B}, "驾驶员侧气囊电阻过高"}, {{0x11, 0x14, 0x1A}, "驾驶员侧气囊电阻过低"}, {{0x11, 0x14, 0x11}, "驾驶员侧气囊对地短路"}, {{0x11, 0x14, 0x12}, "驾驶员侧气囊对电源短路"},
    {{0x11, 0x15, 0x1B}, "前排乘员侧气囊电阻过高"}, {{0x11, 0x15, 0x1A}, "前排乘员侧气囊电阻过低"}, {{0x11, 0x15, 0x11}, "前排乘员侧气囊对地短路"}, {{0x11, 0x15, 0x12}, "前排乘员侧气囊对电源短路"},
    {{0x11, 0x16, 0x1B}, "驾驶员左侧气帘电阻过高"}, {{0x11, 0x16, 0x1A}, "驾驶员左侧气帘电阻过低"}, {{0x11, 0x16, 0x11}, "驾驶员左侧气帘对地短路"}, {{0x11, 0x16, 0x12}, "驾驶员左侧气帘对电源短路"},
    {{0x11, 0x17, 0x1B}, "前排乘员右侧气帘电阻过高"}, {{0x11, 0x17, 0x1A}, "前排乘员右侧气帘电阻过低"}, {{0x11, 0x17, 0x11}, "前排乘员右侧气帘对地短路"}, {{0x11, 0x17, 0x12}, "前排乘员右侧气帘对电源短路"},
    {{0x11, 0x18, 0x1B}, "驾驶员膝部气囊电阻过高"}, {{0x11, 0x18, 0x1A}, "驾驶员膝部气囊电阻过低"}, {{0x11, 0x18, 0x11}, "驾驶员膝部气囊对地短路"}, {{0x11, 0x18, 0x12}, "驾驶员膝部气囊对电源短路"},
    {{0x11, 0x19, 0x1B}, "后排右侧安全带预紧器电阻过高"}, {{0x11, 0x19, 0x1A}, "后排右侧安全带预紧器电阻过低"}, {{0x11, 0x19, 0x11}, "后排右侧安全带预紧器对地短路"}, {{0x11, 0x19, 0x12}, "后排右侧安全带预紧器对电源短路"},
    {{0x11, 0x1A, 0x1B}, "后排左侧安全带预紧器电阻过高"}, {{0x11, 0x1A, 0x1A}, "后排左侧安全带预紧器电阻过低"}, {{0x11, 0x1A, 0x11}, "后排左侧安全带预紧器对地短路"}, {{0x11, 0x1A, 0x12}, "后排左侧安全带预紧器对电源短路"},
    {{0x11, 0x1B, 0x1B}, "前排乘员安全带卷收器电阻过高"}, {{0x11, 0x1B, 0x1A}, "前排乘员安全带卷收器电阻过低"}, {{0x11, 0x1B, 0x11}, "前排乘员安全带卷收器对地短路"}, {{0x11, 0x1B, 0x12}, "前排乘员安全带卷收器对电源短路"},
    {{0x11, 0x1C, 0x1B}, "驾驶员安全带卷收器电阻过高"}, {{0x11, 0x1C, 0x1A}, "驾驶员安全带卷收器电阻过低"}, {{0x11, 0x1C, 0x11}, "驾驶员安全带卷收器对地短路"}, {{0x11, 0x1C, 0x12}, "驾驶员安全带卷收器对电源短路"},
    {{0x11, 0x20, 0x12}, "驾驶员安全带锁扣对电源短路"}, {{0x11, 0x21, 0x12}, "前排乘员安全带锁扣对电源短路"}, {{0x11, 0x22, 0x12}, "后排左侧安全带锁扣对电源短路"},
    {{0x11, 0x23, 0x12}, "后排中间安全带锁扣对电源短路"}, {{0x11, 0x24, 0x12}, "后排右侧安全带锁扣对电源短路"}, {{0x11, 0x25, 0x12}, "前排乘员座椅检测开关对电源短路"},
    {{0x11, 0x26, 0x12}, "后排左侧座椅检测开关对电源短路"}, {{0x11, 0x27, 0x12}, "后排中间座椅检测开关对电源短路"}, {{0x11, 0x28, 0x12}, "后排右侧座椅检测开关对电源短路"},
    {{0x11, 0x42, 0x96}, "驾驶员侧面碰撞传感器损坏"}, {{0x11, 0x42, 0x11}, "驾驶员侧面碰撞传感器对地短路"},
    {{0x11, 0x42, 0x12}, "驾驶员侧面碰撞传感器对电源短路"}, {{0x11, 0x42, 0x86}, "驾驶员侧面碰撞传感器通讯故障"}, {{0x11, 0x42, 0x4A}, "驾驶员侧面碰撞传感器不匹配"},
    {{0x11, 0x43, 0x96}, "前排乘员侧面碰撞传感器损坏"}, {{0x11, 0x43, 0x11}, "前排乘员侧面碰撞传感器对地短路"},
    {{0x11, 0x43, 0x12}, "前排乘员侧面碰撞传感器对电源短路"}, {{0x11, 0x43, 0x86}, "前排乘员侧面碰撞传感器通讯故障"}, {{0x11, 0x43, 0x4A}, "前排乘员侧面碰撞传感器不匹配"},
    {{0x11, 0x44, 0x96}, "驾驶员前置碰撞传感器损坏"}, {{0x11, 0x44, 0x11}, "驾驶员前置碰撞传感器对地短路"},
    {{0x11, 0x44, 0x12}, "驾驶员前置碰撞传感器对电源短路"}, {{0x11, 0x44, 0x86}, "驾驶员前置碰撞传感器通讯故障"}, {{0x11, 0x44, 0x4A}, "驾驶员前置碰撞传感器不匹配"},
    {{0x11, 0x45, 0x96}, "前排乘员前置碰撞传感器损坏"}, {{0x11, 0x45, 0x11}, "前排乘员前置碰撞传感器对地短路"},
    {{0x11, 0x45, 0x12}, "前排乘员前置碰撞传感器对电源短路"}, {{0x11, 0x45, 0x86}, "前排乘员前置碰撞传感器通讯故障"}, {{0x11, 0x45, 0x4A}, "前排乘员前置碰撞传感器不匹配"},
    {{0x11, 0x32, 0x14}, "碰撞输出1对地短路"}, {{0x11, 0x32, 0x12}, "碰撞输出1对电源短路"}, {{0x11, 0x33, 0x14}, "碰撞输出2对地短路"}, {{0x11, 0x33, 0x12}, "碰撞输出2对电源短路"},
    {{0x11, 0x01, 0x49}, "ACU内部存储模块故障"}, {{0x11, 0x02, 0x49}, "ACU内部加计模块故障"}, {{0x11, 0x03, 0x49}, "ACU内部储能电容模块故障"}, {{0x11, 0x01, 0x00}, "车辆不匹配"},
    {{0x11, 0x50, 0x00}, "前向正面碰撞点火（更换ACU）"}, {{0x11, 0x51, 0x00}, "侧向正面碰撞点火（更换ACU）"}
};

void CenterWindow::InitUI()
{
    LOG(INFO) << "Initial CenterWindow.";
    base_widget_ = new QWidget(this);
    QHBoxLayout* base_layout = new QHBoxLayout;  //
    QVBoxLayout *info_fault_info_layout = new QVBoxLayout;
    // ECU information
    // ——————QFormLayout(ECU_information_form)——————————————————
    //|
    //|     |序列号|        serial_line_
    //|     |硬件版本号|   hardware_version_line_
    //|     |软件版本号|     software_version_line_
    //|     |生产日期|       manufacturing_date_line_
    //|     |功能配置字|     function_configration_data_line_
    //|_________________________________________________________
    QFormLayout *ecu_information_form = new QFormLayout;   // 放置ECU信息控件 表单
    QStringList ecu_information_string = {"序列号", "硬件版本号", "软件版本号", "生产日期", "功能配置字"};
    for (int i = 0; i < 5; i++) {
        ecu_information_btn_[i] = new QPushButton(ecu_information_string[i]);
        ecu_information_line_[i] = new QLineEdit;
        ecu_information_form->addRow(ecu_information_btn_[i], ecu_information_line_[i]);
    }
    ecu_information_form->setMargin(0);
    info_fault_info_layout->addLayout(ecu_information_form);

    //Fault information
    // ——————QFormLayout(ECU_information_form)——————————————————
    //|
    //|     |           清除故障码           |
    //|     |           读取故障码           |
    //|     __________print_dtc_table________
    //|     |   故障码   |        含义       |
    //|     |-----------|-------------------|
    //|     |           |                   |
    //|     |-----------|-------------------|
    //|     |           |                   |
    //|     |-----------|-------------------|
    //|     |           |                   |
    //|     |-----------|-------------------|
    //|     |           |                   |
    //|     |-----------|-------------------|
    QVBoxLayout *fault_information_box = new QVBoxLayout;
    clear_dtc_btn = new QPushButton("清除故障码");
    //   clear_dtc_btn->setMaximumWidth(200);
    read_dtc_btn = new QPushButton("读取故障码");
    //   read_dtc_btn->setMaximumWidth(200);
    clear_dtc_inf_btn_ = new QPushButton("清空数据");
    // Creates a new table view with the 0 rows and 3 columns, and with the given parent.
    print_dtc_table_ = new QTableWidget(0, 3, this);
    // Sets the horizontal header labels using QStringList() << "DTC" << "Status" << "Description   "
    print_dtc_table_->setHorizontalHeaderLabels(QStringList() << "DTC" << "Status" << "Description   ");
    // Initiate item No editing possible.
    print_dtc_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Resizes all columns based on the size hints of the delegate used to render each item in the columns.
    print_dtc_table_->resizeColumnsToContents();
    // Resizes all rows based on the size hints of the delegate used to render each item in the rows.
    print_dtc_table_->resizeRowsToContents();
    print_dtc_table_->horizontalHeader()->setStretchLastSection(true);
    //   print_dtc_table_->setMaximumWidth(200);

    fault_information_box->addWidget(clear_dtc_btn);
    fault_information_box->addWidget(read_dtc_btn);
    fault_information_box->addWidget(clear_dtc_inf_btn_);
    fault_information_box->addWidget(print_dtc_table_);
    info_fault_info_layout->addLayout(fault_information_box);

    //Event data
    // —————————————QGridLayout(event_data_box)—————————————
    //| 事件数据
    //|     |FA13||FA14||FA15||0216||0217||0218||0219|
    //|     ------------print_event_data_table_-------------
    //|     |               |                              |
    //|     |----------------------------------------------|
    //|     |               |                              |
    //|     |----------------------------------------------|
    //|     |               |                              |
    //|     |----------------------------------------------|
    //|     |               |                              |
    //|     |----------------------------------------------|
    //|     |               |                              |
    //|     |----------------------------------------------|
    //|
    QVBoxLayout *event_data_plot_layout = new QVBoxLayout;
    QGridLayout *event_data_box = new QGridLayout;
    QLabel *event_data_label = new QLabel("事件数据");
    event_data_box->addWidget(event_data_label,0, 0);
    QStringList event_data_string = {"FA13", "FA14", "FA15", "0216", "0217", "0218", "0219", "清空"};
    for (int i = 0; i < event_data_string.size(); i++) {
        event_data_btn_[i] = new QPushButton(event_data_string[i]);
        event_data_box->addWidget(event_data_btn_[i], 1, i);
    }
    print_event_data_table_ = new QTableWidget(0, 2, this);
    // Sets the horizontal header labels using QStringList() << "名称" << "数据"
    print_event_data_table_->setHorizontalHeaderLabels(QStringList() << "名称" << "数据");
    // Initiate item No editing possible.
    print_event_data_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Resizes all columns based on the size hints of the delegate used to render each item in the columns.
//    connect(this->print_event_data_table_, &QTableWidget::itemChanged
//            , this->print_event_data_table_, &QTableWidget::resizeColumnsToContents);
    print_event_data_table_->resizeColumnsToContents();
    // Resizes the given row based on the size hints of the delegate used to render each item in the row.
    connect(print_event_data_table_, &QTableWidget::cellChanged
            , print_event_data_table_, &QTableWidget::resizeRowToContents);
    print_event_data_table_->setColumnWidth(0, 120);
//    print_event_data_table_->verticalHeader()->setVisible(true);
//    print_event_data_table_->verticalHeader()->setStretchLastSection(true);
//    print_event_data_table_->verticalHeader()->setHighlightSections(true);
    print_event_data_table_->horizontalHeader()->setStretchLastSection(true);
//    print_event_data_table_->horizontalHeader()->setHighlightSections(true);
//    print_event_data_table_->setSelectionBehavior(QAbstractItemView::SelectRows);
//    print_event_data_table_->setSelectionMode(QAbstractItemView::SingleSelection);
//    print_event_data_table_->verticalHeader()->setDefaultSectionSize(20);


    event_data_box->addWidget(print_event_data_table_, 2, 0, 10, 10);
    event_data_plot_layout->addLayout(event_data_box);

    //Axis-Event
    // —————————————QGridLayout(axis_box)—————————————
    //| 事件数据
    //|     |FA13||FA14||FA15||0216||0217||0218||0219|
    //|
    //|     |                     *.           | -                             |
    //|     |                *.  *.   *.       | * -                           |
    //|     |                 *.         *.    |    *-                         |
    //|     |               *.            *.   |     * -  -                    |
    //|     |         * . * .                  |       *     - -               |
    //|     |        * .                       |         *        -            |
    //|     |      * .                         |            * *       -   -    |
    //|     |     *.                           |                  *          - |
    //|     |   *.                             |                     * *  *    |

    QGridLayout *axis_box = new QGridLayout;
    QLabel *plot_label = new QLabel("数据曲线");
    axis_box->addWidget(plot_label,0, 0);
    QStringList axis_string = {"FA13", "FA14", "FA15", "0216", "0217", "0218", "0219"};
    for (int i = 0; i < axis_string.size(); i++) {
        axis_btn_[i] = new QPushButton(event_data_string[i]);
        axis_box->addWidget(axis_btn_[i], 1, i);
    }
    acc_axis_ = new FCustomPlot;
//    SetupAccAxis(acc_axis_, );
    data_axis_ = new FCustomPlot;
//    SetupAccAxis(data_axis_);
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

void CenterWindow::InitConnect()
{
    // ECU Serial Data Identifier
    //
//    connect(this->ecu_information_btn_[0], &QPushButton::clicked, [this](){
//        char serial_char[17] = {0x20, 0x20, 0x20, 0x57, 0x54, 0x44, 0x32, 0x32, 0x30, 0x36, 0x30, 0x39, 0x30, 0x30, 0x30, 0x30, 0x31};
//        QByteArray serial_;
//        for (auto data : serial_char) {
//            serial_.push_back(data);
//        }
//        PrintStringInfo(*ecu_information_line_[0], serial_);
//    });

    // ECU Hardversion Data Identifier
    //
//    connect(this->ecu_information_btn_[1], &QPushButton::clicked, [=](){
//        char hard_version[8] = {0x48, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
//        QByteArray hard_;
//        for (auto data : hard_version) {
//            hard_.push_back(data);
//        }
//        PrintStringInfo(*ecu_information_line_[1], hard_);
//    });

    // ECU Softversion Data Identifier
    //
//    connect(this->ecu_information_btn_[2], &QPushButton::clicked, [=](){
//        char soft_version[8] = {0x53, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
//        QByteArray soft_;
//        for (auto data : soft_version) {
//            soft_.push_back(data);
//        }
//        PrintStringInfo(*ecu_information_line_[2], soft_);
//    });

    // ECU Manufacture Data Identifier
    //
//    connect(this->ecu_information_btn_[3], &QPushButton::clicked, [=](){
//        char manufacture_data[8] = {0x22, 0x06, 0x10};
//        QByteArray manufacture_data_;
//        for (auto data : manufacture_data) {
//            manufacture_data_.push_back(data);
//        }
//        PrintDateIdentInfo(*ecu_information_line_[3], manufacture_data_);
//    });


    // ECU Function Configration Data Identifier
    //
//    connect(this->ecu_information_btn_[4], &QPushButton::clicked, [=](){
//        char function_configration_data_identifier[1] = {0x02};
//        QByteArray function_configration_data_identifier_;
//        for (auto data : function_configration_data_identifier) {
//            function_configration_data_identifier_.push_back(data);
//        }
//        PrintWorkModeInfo(*ecu_information_line_[4], function_configration_data_identifier_);
//    });

    // Decode DTC information
    //
//    connect(this->read_dtc_btn, &QPushButton::clicked, [=](){
//        char dtc[23] = {0x59, 0x02, 0x09, 0x11, 0x01, 0x00, 0x09, 0x11, 0x01, 0x00, 0x09, static_cast<char>(0xC1), 0x41, 0x00, 0x09, static_cast<char>(0xC1), 0x00, 0x00, 0x09, 0x01, 0x01, 0x00, 0x09};
//        QByteArray dtc_;
//        for (auto data : dtc) {
//            dtc_.push_back(data);
//        }
//        DecodeDTC(*print_dtc_table_, dtc_);
//    });

    // Decade EDR Data 0x22 FA 13
    //
//    connect(this->event_data_btn_[0], &QPushButton::clicked, [=](){
//        QByteArray data = ReadFromFile("E:\\Project\\EDRReader\\Code\\EDRReader\\Test\\FA13.zudslog");
//        EventDataProcess(*print_event_data_table_, data);
//    });

    // Decade EDR Data 0x22 FA 14
    //
//    connect(this->event_data_btn_[1], &QPushButton::clicked, [=](){
//        QByteArray data = ReadFromFile("E:\\Project\\EDRReader\\Code\\EDRReader\\Test\\FA14.zudslog");
//        EventDataProcess(*print_event_data_table_, data);
//    });

    // Decade EDR Data 0x22 FA 15
    //
//    connect(this->event_data_btn_[2], &QPushButton::clicked, [=](){
//        QByteArray data = ReadFromFile("E:\\Project\\EDRReader\\Code\\EDRReader\\Test\\FA15.zudslog");
//        EventDataProcess(*print_event_data_table_, data);
//    });
  connect(this->acc_axis_->xAxis, SIGNAL(rangeChanged(QCPRange)), this->acc_axis_->yAxis, SLOT(setRange(QCPRange)));

  connect(this->clear_dtc_inf_btn_, &QPushButton::clicked, [=](){
      ClearWidgetData(*print_dtc_table_);
    });
  connect(this->event_data_btn_[7], &QPushButton::clicked, [=](){
      ClearWidgetData(*print_event_data_table_);
    });
  connect(this->axis_btn_[0], &QPushButton::clicked, [=](){
      SetupAccAxis(*acc_axis_, GraphIndexSet(0), data_FA13_.longitudinal_acceleration, "FA13_edr_acc");  //
      SetupVehicleSpeedAxis(*data_axis_, GraphIndexSet(0), data_FA13_.vehicle_speed, "FA13_speed");
    });
  connect(this->axis_btn_[1], &QPushButton::clicked, [=](){
      SetupAccAxis(*acc_axis_, GraphIndexSet(0), data_FA14_.longitudinal_acceleration, "FA14_edr_acc");
      SetupVehicleSpeedAxis(*data_axis_, GraphIndexSet(0), data_FA14_.vehicle_speed, "FA14_speed");
    });
  connect(this->axis_btn_[2], &QPushButton::clicked, [=](){
      SetupAccAxis(*acc_axis_, GraphIndexSet(0), data_FA15_.longitudinal_acceleration, "FA15_edr_acc");
      SetupVehicleSpeedAxis(*data_axis_, GraphIndexSet(0), data_FA15_.vehicle_speed, "FA15_speed");
    });

}

void CenterWindow::DecodeEDRData(EDRData &data_processed, const QMap<QString, QVector<char>> data_original)
{
    // 解析数据
    // N 表示 EDR 读取的原始数据;
    // E 表示提取工具使用转化公式将 N 转译之后的 EDR 数据
//    bool ok;
    QMap<QString, QVector<char>>::const_iterator data_original_iterator = data_original.constBegin();
    while(data_original_iterator != data_original.constEnd()){
        if(data_original_iterator.key() == "01纵向 delta-V"){
            // 转化公式 E = N - 127
            // 0xFF: 无法获取值, 0xFE: 无效值
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                data_.push_back(static_cast<uint8_t>(data__) - 127);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
//                data_.push_back(data__ - 127);
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["01纵向 delta-V"] = data_str;
        }
        if(data_original_iterator.key() == "02最大记录纵向 delta-V"){
            // 转化公式 E = N - 127
            // 0xFF: 无法获取值, 0xFE: 无效值
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                data_.push_back(static_cast<uint8_t>(data__) - 127);
            }
                else data_.push_back(static_cast<uint8_t>(data__));
//                data_.push_back(data__ - 127);
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["02最大记录纵向 delta-V"] = data_str;
        }
        if(data_original_iterator.key() == "03达到最大记录纵向 delta-V 时间"){
            // 转化公式 E = N - 127
            // 0xFF: 无法获取值, 0xFE: 无效值
            QVector<double> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                data_.push_back(static_cast<uint8_t>(data__) * 2.5);
            }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["03达到最大记录纵向 delta-V 时间"] = data_str;
        }
        if(data_original_iterator.key() == "04削波标志"){
            // 转化公式 E = N
            // 第一个字节 0xFF: 无法获取值, 0xFE: 无效值
            // 第二个字节 0xFF: 无法获取值, 0xFE: 无效值
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["04削波标志"] = data_str;
        }
        if(data_original_iterator.key() == "05车辆速度"){
            // 转化公式 E = N
            // 范围 0 ~ 250
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["05车辆速度"] = data_str;
        }
        if(data_original_iterator.key() == "06行车制动"){
            // 转化公式 0 关闭  1 开启
            // 范围 不适用
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Open");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["06行车制动"] = data_str;
        }
        if(data_original_iterator.key() == "07驾驶员安全带状态"){
            // 转化公式 0 系  1 未系
            // 范围 不适用
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Buckled");
                    break;
                case 1:
                    data_str.push_back("Unbuckled");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["07驾驶员安全带状态"] = data_str;
        }
        if(data_original_iterator.key() == "08加速踏板位置"){
            // 转化公式 E = N ，全开位置的百分比
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["08加速踏板位置"] = data_str;
        }
        if(data_original_iterator.key() == "09每分钟转数"){
            // 转化公式 E = N * 100
            //
            QVector<uint16_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                data_.push_back((static_cast<uint16_t>(data__) & 0x00FF) * 100);
                  }
                else data_.push_back((static_cast<uint16_t>(data__) & 0x00FF));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["09每分钟转数"] = data_str;
        }
        if(data_original_iterator.key() == "10事件中上电周期"){
            //  转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["10事件中上电周期"] = data_str;
        }
        if(data_original_iterator.key() == "11读取时上电周期"){
            //  转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["11读取时上电周期"] = data_str;
        }
        if(data_original_iterator.key() == "12事件数据记录完整状态"){
            // 转化公式  0 未完成 1 完成
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["12事件数据记录完整状态"] = data_str;
        }
        if(data_original_iterator.key() == "13本次事件距上次事件的时间间隔"){
            // 转化公式 E = N * 0.1
            //
            QVector<double> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<double>(data__) * 0.1);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["13本次事件距上次事件的时间间隔"] = data_str;
        }
        if(data_original_iterator.key() == "14车辆识别代号"){
            // 转化公式 ASCII
            //
            QVector<QString> data_str;
            QString str;
            for(auto data__ : data_original_iterator.value()){
                str.push_back(QChar(data__));
            }
            data_str.push_back(str);
            data_processed.EDR_data_CHN_str["14车辆识别代号"] = data_str;
        }
        if(data_original_iterator.key() == "15记录EDR数据的ECU硬件编号"){
            // 转化公式 ASCII
            //
            QVector<QString> data_str;
            QString str;
            for(auto data__ : data_original_iterator.value()){
                str.push_back(QChar(data__));
            }
            data_str.push_back(str);
            data_processed.EDR_data_CHN_str["15记录EDR数据的ECU硬件编号"] = data_str;
        }
        if(data_original_iterator.key() == "16记录EDR数据的ECU序列号"){
            // 转化公式 ASCII
            //
            QVector<QString> data_str;
            QString str;
            for(auto data__ : data_original_iterator.value()){
                str.push_back(QChar(data__));
            }
            data_str.push_back(str);
            data_processed.EDR_data_CHN_str["16记录EDR数据的ECU序列号"] = data_str;
        }
        if(data_original_iterator.key() == "17记录EDR数据的ECU软件编号"){
            // 转化公式 ASCII
            //
            QVector<QString> data_str;
            QString str;
            for(auto data__ : data_original_iterator.value()){
                str.push_back(QChar(data__));
            }
            data_str.push_back(str);
            data_processed.EDR_data_CHN_str["17记录EDR数据的ECU软件编号"] = data_str;
        }
        if(data_original_iterator.key() == "18纵向加速度"){
            // 转化公式 E = N - 127
            //
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) - 127);
                }
                else data_.push_back(static_cast<uint8_t>(data__));

            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["18纵向加速度"] = data_str;
        }

        if(data_original_iterator.key() == "19横向加速度"){
            // 转化公式 E = N - 127
            //
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) - 127);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["19横向加速度"] = data_str;
        }

        if(data_original_iterator.key() == "20横向 delta-V"){
            // 转化公式 E = N - 127
            //
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) - 127);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["20横向 delta-V"] = data_str;
        }

        if(data_original_iterator.key() == "21最大记录横向 delta-V"){
            // 转化公式 E = N - 127
            //
            QVector<int> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) - 127);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["21最大记录横向 delta-V"] = data_str;
        }

        if(data_original_iterator.key() == "22最大记录合量 delta-V 平方"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(1) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(0)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["22最大记录合量 delta-V 平方"] = data_str;
        }

        if(data_original_iterator.key() == "23达到最大记录横向 delta-V 时间"){
            // 转化公式 E = N * 2.5
            //
            QVector<double> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<double>(data__) * 2.5);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["23达到最大记录横向 delta-V 时间"] = data_str;
        }

        if(data_original_iterator.key() == "24达到最大记录合量 delta-V 平方的时间"){
            // 转化公式 E = N * 2.5
            //
            QVector<double> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<double>(data__) * 2.5);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["24达到最大记录合量 delta-V 平方的时间"] = data_str;
        }

        if(data_original_iterator.key() == "25横摆角速度"){
            // 转化公式 E = N * 0.1 -300
            //
            QVector<double> data_;
            QVector<uint16_t> data_uint16_t;
            for (int i = 0;i < data_original_iterator.value().size(); i += 2) {

                data_uint16_t.push_back((static_cast<uint16_t>(data_original_iterator.value().at(i + 1) << 8))
                                        + (static_cast<uint16_t>(data_original_iterator.value().at(i)) & 0x00FF));

            }
            for(auto data__ : data_uint16_t){
                if(IsValid(data__)){
                    data_.push_back(static_cast<double>(data__) * 0.1 - 300);
                }
                else  data_.push_back(static_cast<uint16_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["25横摆角速度"] = data_str;
        }

        if(data_original_iterator.key() == "26转向角度"){
            // 转化公式 E = N * 5 -780
            //
            QVector<uint16_t> data_;
            QVector<uint16_t> data_uint16_t;
            for (int i = 0;i < data_original_iterator.value().size(); i += 2) {
                data_uint16_t.push_back((static_cast<uint16_t>(data_original_iterator.value().at(i + 1) << 8))
                                        + (static_cast<uint16_t>(data_original_iterator.value().at(i)) & 0x00FF));
            }
            for(auto data__ : data_uint16_t){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint16_t>(data__) * 5 - 780);
                }
                else  data_.push_back(static_cast<uint16_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["26转向角度"] = data_str;
        }

        if(data_original_iterator.key() == "27Tend"){
            // 转化公式 E = N *2.5
            //
            QVector<double> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<double>(data__) * 2.5);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 2);
            data_processed.EDR_data_CHN_str["27Tend"] = data_str;
        }

        if(data_original_iterator.key() == "28年"){
            // 转化公式 E = N + 2000
            //
            QVector<uint16_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) + static_cast<uint16_t>(2000));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["28年"] = data_str;
        }

        if(data_original_iterator.key() == "29月"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["29月"] = data_str;
        }

        if(data_original_iterator.key() == "30日"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["30日"] = data_str;
        }

        if(data_original_iterator.key() == "31时"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["31时"] = data_str;
        }

        if(data_original_iterator.key() == "32分"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["32分"] = data_str;
        }

        if(data_original_iterator.key() == "33秒"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["33秒"] = data_str;
        }

        if(data_original_iterator.key() == "34挡位"){
            // 转化公式 0：P档，1：R档，2：N档，3：D档
            //
            QVector<uint8_t> data_;
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch(data__){
                case 0:
                    data_str.push_back("P");
                    break;
                case 1:
                    data_str.push_back("R");
                    break;
                case 2:
                    data_str.push_back("N");
                    break;
                case 3:
                    data_str.push_back("D");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
                data_.push_back(static_cast<uint8_t>(data__));
            }
            data_processed.EDR_data_CHN_str["34挡位"] = data_str;
        }

        if(data_original_iterator.key() == "35发动机节气门位置"){
            // 转化公式 E = N
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__));
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["35发动机节气门位置"] = data_str;
        }

        if(data_original_iterator.key() == "36制动踏板位置"){
            // 转化公式 E = N * 5
            //
            QVector<uint8_t> data_;
            for(auto data__ : data_original_iterator.value()){
                if(IsValid(data__)){
                    data_.push_back(static_cast<uint8_t>(data__) * 5);
                }
                else data_.push_back(static_cast<uint8_t>(data__));
            }
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["36制动踏板位置"] = data_str;
        }

        if(data_original_iterator.key() == "37驻车系统状态"){
            // 转化公式 0：开启，1：故障，2：关闭
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch(data__){
                case 0:
                    data_str.push_back("Open");
                    break;
                case 1:
                    data_str.push_back("Malfunction");
                    break;
                case 2:
                    data_str.push_back("Close");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                }
            }
            data_processed.EDR_data_CHN_str["37驻车系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "38转向信号开关状态"){
            // 转化公式 0：关闭，1：左，2：右，3：双闪
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch(data__){
                case 0:
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Left");
                    break;
                case 2:
                    data_str.push_back("Right");
                    break;
                case 3:
                    data_str.push_back("DoubleFlash");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                }
            }
            data_processed.EDR_data_CHN_str["38转向信号开关状态"] = data_str;
        }

        if(data_original_iterator.key() == "39驾驶员安全带预紧装置展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["39驾驶员安全带预紧装置展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "40驾驶员正面气囊展开时间(第一阶段)"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["40驾驶员正面气囊展开时间(第一阶段)"] = data_str;
        }

        if(data_original_iterator.key() == "41驾驶员正面气囊展开时间(第二阶段)"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["41驾驶员正面气囊展开时间(第二阶段)"] = data_str;
        }

        if(data_original_iterator.key() == "42驾驶员侧面气囊展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["42驾驶员侧面气囊展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "43驾驶员侧气帘展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["43驾驶员侧气帘展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "44前排乘员安全带状态"){
            // 转化公式 0：系，1：未系
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Buckled");
                    break;
                case 1:
                    data_str.push_back("UnBuckled");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["44前排乘员安全带状态"] = data_str;
        }

        if(data_original_iterator.key() == "45前排乘员安全带预紧器装置展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["45前排乘员安全带预紧器装置展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "46前排乘员正面气囊抑制状态"){
            // 转化公式 0：关闭(气囊可用)，1：开启(气囊不可用/抑制)
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Open");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["46前排乘员正面气囊抑制状态"] = data_str;
        }

        if(data_original_iterator.key() == "47前排乘员正面气囊展开时间(第一阶段)"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["47前排乘员正面气囊展开时间(第一阶段)"] = data_str;
        }

        if(data_original_iterator.key() == "48前排乘员正面气囊展开时间(第二阶段)"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["48前排乘员正面气囊展开时间(第二阶段)"] = data_str;
        }

        if(data_original_iterator.key() == "49前排乘员侧气囊展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["49前排乘员侧气囊展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "50前排乘员侧气帘展开时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["50前排乘员侧气帘展开时间"] = data_str;
        }

        if(data_original_iterator.key() == "51乘员保护系统报警状态"){
            // 转化公式 0：关闭，1：开启
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Open");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["51乘员保护系统报警状态"] = data_str;
        }

        if(data_original_iterator.key() == "52轮胎压力监测系统报警状态"){
            // 转化公式 0：关闭，1：开启
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Open");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["52轮胎压力监测系统报警状态"] = data_str;
        }

        if(data_original_iterator.key() == "53制动系统报警状态"){
            // 转化公式 0：关闭，1：开启
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("Close");
                    break;
                case 1:
                    data_str.push_back("Open");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["53制动系统报警状态"] = data_str;
        }

        if(data_original_iterator.key() == "54定速巡航系统状态"){
            // 转化公式 0：开启未激活，1：开启激活，2：命令关闭，3：故障，4 ~ 253：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("OpenButNotActivated");
                    break;
                case 1:
                    data_str.push_back("OpenAndActivated");
                    break;
                case 2:
                    data_str.push_back("CommandClosed");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["54定速巡航系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "55自适应巡航系统状态"){
            // 转化公式 0：开启未激活，1：开启激活，2：命令关闭，3：故障，4 ~ 253：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("OpenButNotActivated");
                    break;
                case 1:
                    data_str.push_back("OpenAndActivated");
                    break;
                case 2:
                    data_str.push_back("CommandClosed");
                    break;
                case 3:
                    data_str.push_back("Malfunction");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["55自适应巡航系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "56防抱制动系统状态"){
            // 转化公式 0: 未激活，1：激活，2: 故障，3 ~ 253：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("NotActivated");
                    break;
                case 1:
                    data_str.push_back("Actiavted");
                    break;
                case 2:
                    data_str.push_back("Malfunction");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["56防抱制动系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "57自动紧急制动系统状态"){
            // 转化公式 0：开启未激活，1：开启激活，2：命令关闭，3：故障，4 ~ 256：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("OpenButNotActivated");
                    break;
                case 1:
                    data_str.push_back("OpenAndActivated");
                    break;
                case 2:
                    data_str.push_back("CommandClosed");
                    break;
                case 3:
                    data_str.push_back("Malfunction");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["57自动紧急制动系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "58电子稳定性控制系统状态"){
            // 转化公式 0：开启未激活，1：开启激活，2：命令关闭，3：故障，4 ~ 256：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("OpenButNotActivated");
                    break;
                case 1:
                    data_str.push_back("OpenAndActivated");
                    break;
                case 2:
                    data_str.push_back("CommandClosed");
                    break;
                case 3:
                    data_str.push_back("Malfunction");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["58电子稳定性控制系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "59牵引力控制系统状态"){
            // 转化公式 0：开启未激活，1：开启激活，2：命令关闭，3：故障，4 ~ 256：自定义
            //
            QVector<QString> data_str;
            for(auto data__ : data_original_iterator.value()){
                switch (data__) {
                case 0 :
                    data_str.push_back("OpenButNotActivated");
                    break;
                case 1:
                    data_str.push_back("OpenAndActivated");
                    break;
                case 2:
                    data_str.push_back("CommandClosed");
                    break;
                case 3:
                    data_str.push_back("Malfunction");
                    break;
                default:
                    data_str.push_back(QString::number(static_cast<uint8_t>(data__), 10));
                    break;
                }
            }
            data_processed.EDR_data_CHN_str["59牵引力控制系统状态"] = data_str;
        }

        if(data_original_iterator.key() == "60事件前同步计时时间"){
            // 转化公式 E = N
            //
            QVector<uint16_t> data_;
            data_.push_back((static_cast<uint16_t>(data_original_iterator.value().at(0) << 8))
                            + (static_cast<uint16_t>(data_original_iterator.value().at(1)) & 0x00FF));
            QVector<QString> data_str = DataToString(data_, 10);
            data_processed.EDR_data_CHN_str["60事件前同步计时时间"] = data_str;
        }
        data_original_iterator++;
    }
}

void CenterWindow::AlgorithmIntermediateVariableProcess(EDRData &data_processed, const QMap<QString, QVector<char>> data_original)
{

}
void CenterWindow::InitPlot(QCustomPlot &customPlot, QString graph0_name, QString graph1_name)
{
  customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  customPlot.setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
  customPlot.legend->setVisible(true);
  QFont legendFont = font();  // start out with MainWindow's font..
  legendFont.setPointSize(9); // and make a bit smaller for legend
  customPlot.legend->setFont(legendFont);
  customPlot.legend->setBrush(QBrush(QColor(255, 255, 255, 230)));

  // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
  customPlot.axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

  // setup for graph 0: key axis left, value axis bottom
  // will contain left maxwell-like function
  customPlot.addGraph(customPlot.xAxis, customPlot.yAxis);
  customPlot.graph(0)->setPen(QPen(QColor(255, 100, 0)));
//    customPlot.graph(0).setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // fill with texture of specified image
  customPlot.graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
  customPlot.graph(0)->setName(graph0_name);
  // setup for graph 1: key axis bottom, value axis left (those are the default axes)
  // will contain bottom maxwell-like function
  customPlot.addGraph();
  customPlot.graph(1)->setPen(QPen(Qt::blue));
//    customPlot.graph(1).setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // same fill as we used for graph 0
  customPlot.graph(1)->setLineStyle(QCPGraph::lsLine);
  customPlot.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, Qt::blue, Qt::white, 4));
//    customPlot.graph(1).setErrorType(QCPGraph::etValue);
  customPlot.graph(1)->setName(graph1_name);
//  customPlot.xAxis->setRange(-5, 20 + 2);
//  customPlot.yAxis->setRange(-2, 1.1);

}

void CenterWindow::GetEventData(EventData &event_data, const EDRData data_processed)
{
  if(data_processed.EDR_data_CHN_str.contains("18纵向加速度")){
      event_data.longitudinal_acceleration.clear();
      for(auto acc_s :data_processed.EDR_data_CHN_str.value("18纵向加速度")){
          if(IsValid(acc_s))
            event_data.longitudinal_acceleration.push_back(acc_s.toInt());
        }
    }
  if(data_processed.EDR_data_CHN_str.contains("05车辆速度")){
      event_data.vehicle_speed.clear();
      for(auto acc_s :data_processed.EDR_data_CHN_str.value("05车辆速度")){
          if(IsValid(acc_s))
            event_data.vehicle_speed.push_back(acc_s.toInt());
        }
    }
}

void CenterWindow::PrintStringInfo(QLineEdit &line_edit, QByteArray &data)
{
    QString string;
    for (auto data_ : data) {
        string.push_back(QChar(data_));  // ASCII To QString
    }
    line_edit.clear();
    line_edit.insert(string);
}

void CenterWindow::PrintWorkModeInfo(QLineEdit &line_edit, QByteArray &data)
{
    const char normol_mode = 0x01;   // 正常模式
    const char factory_mode = 0x02;  // 工厂模式
    line_edit.clear();
    switch (data[0]) {
    case normol_mode:
        line_edit.insert("正常模式");
        break;
    case factory_mode:
        line_edit.insert("工厂模式");
        break;
    default:
        line_edit.insert("未知模式:" + data.toHex());
        break;
    }

}

void CenterWindow::PrintDateIdentInfo(QLineEdit &line_edit, QByteArray &data)
{
    bool ok;
//    int year_int = QString::number(data[0], 16).toInt(&ok, 10);
    DataType year = static_cast<unsigned int>(2000 + QString::number(data[0], 16).toInt(&ok, 10));
    DataType month = static_cast<unsigned int>(QString::number(data[1], 16).toInt(&ok, 10));
    DataType day = static_cast<unsigned int>(QString::number(data[2], 16).toInt(&ok, 10));
    line_edit.clear();
    line_edit.insert(QString::number(year,10) + "." + QString::number(month, 10) + "." + QString::number(day, 10));
}

void CenterWindow::DecodeDTC(QTableWidget &table_widget, QByteArray &data)
{
    // Removes all the row and all its items from the table.
    int row_counter = table_widget.rowCount();
    while(row_counter--)
        table_widget.removeRow(row_counter);
    // 分割故障码
    QVector<QVector<unsigned char>> dtc_vector;
//    data.remove(0, 3);
    for (int i = 0;i < data.size() / 4; i++) {
        QVector<unsigned char> dtc_vector_;
        for (int j = i * 4;j < i * 4 + 4; j++) {
            dtc_vector_.push_back(static_cast<unsigned char>(data.at(j)));
        }
        dtc_vector.push_back(dtc_vector_);
    }
    for (auto dtc_vector_ : dtc_vector) {
        QByteArray dtc_status;
        dtc_status[0] = static_cast<char>(dtc_vector_.last());  // 获取故障码状态
        dtc_vector_.remove(3);
        auto search = DTC.find(dtc_vector_);   // 查找DTC中是否包含相应的故障码
        if (search != DTC.end()){              // 查找到响应的DTC
            QByteArray dtc_array_key;
            for (int i = 0; i < search.key().size(); i++) {  // 将char类型转为QByteArray类型
                dtc_array_key.push_back(static_cast<char>(search.key()[i]));
            }
            QString dtc_array_key_str = dataToHex(dtc_array_key);  // 将QByteArray类型转为QString
            QString dtc_status_str = dataToHex(dtc_status);
            int row_counter = table_widget.rowCount();
            table_widget.setRowCount(row_counter + 1);
            table_widget.setItem(row_counter, 0, new QTableWidgetItem(dtc_array_key_str));  // 打印DTC
            table_widget.setItem(row_counter, 1, new QTableWidgetItem(dtc_status_str));     // 打印DTC状态
            table_widget.setItem(row_counter, 2, new QTableWidgetItem(search.value()));     // 打印中文描述
        } else{   // 未查找到相应的DTC
            QByteArray dtc_array_unconfirmed;
            for (auto dtc_vector__ : dtc_vector_) {   //将char类型转为QByteArray类型
                dtc_array_unconfirmed.push_back(static_cast<char>(dtc_vector__));
            }
            QString dtc_array_unconfirmed_str = dataToHex(dtc_array_unconfirmed);  // 将QByteArray类型转为QString
            QString dtc_status_str = dataToHex(dtc_status);
            int row_counter = table_widget.rowCount();
            table_widget.setRowCount(row_counter + 1);
            table_widget.setItem(row_counter, 0, new QTableWidgetItem(dtc_array_unconfirmed_str));  // 打印DTC
            table_widget.setItem(row_counter, 1, new QTableWidgetItem(dtc_status_str));  // 打印DTC状态
            table_widget.setItem(row_counter, 2, new QTableWidgetItem("本地未定义"));     // 打印中文描述

        }
    }
}

void CenterWindow::SetupAccAxis(QCustomPlot &custom_plot, int index, QVector<double> acc, QString graph_name)
{
  if(acc.isEmpty()){
      QMessageBox message_box(QMessageBox::Warning, QString(tr("Warning")),QString(tr("Longitudinal acceleration data is empty.")));
      message_box.setStandardButtons (QMessageBox::Ignore | QMessageBox::Cancel);
//      message_box.setButtonText (QMessageBox::Yes, QString("Yes"));
//      message_box.setButtonText (QMessageBox::No, QString("Cancel"));
      message_box.exec();
      return;
    }
//    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
//    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
//    customPlot->legend->setVisible(true);
//    QFont legendFont = font();  // start out with MainWindow's font..
//    legendFont.setPointSize(9); // and make a bit smaller for legend
//    customPlot->legend->setFont(legendFont);
//    customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
//    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
//    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

//    // setup for graph 0: key axis left, value axis bottom
//    // will contain left maxwell-like function
//    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis);
//    customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
////    customPlot->graph(0)->setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // fill with texture of specified image
//    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
////    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    custom_plot.graph(index)->setName(graph_name);

//    // setup for graph 1: key axis bottom, value axis left (those are the default axes)
//    // will contain bottom maxwell-like function
//    customPlot->addGraph();
//    customPlot->graph(1)->setPen(QPen(Qt::blue));
////    customPlot->graph(1)->setBrush(QBrush(QPixmap("://skin/images/balboa.jpg"))); // same fill as we used for graph 0
//    customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
////    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, Qt::red, Qt::white, 7));
////    customPlot->graph(1)->setErrorType(QCPGraph::etValue);
//    customPlot->graph(1)->setName("ACU Acc");

    // Generate EDR Accelerate data
    QVector<double> acc_x;
//    QVector<double> acc_acu_x;
    // Get max and min element in EDR accelerate
    auto acc_max = std::max_element(acc.begin(), acc.end());
    auto acc_min = std::min_element(acc.begin(), acc.end());
    // data for graph 0 EDR Accelerate
    for (int i = 0; i < acc.size(); i++) {
        acc_x.append(i * 2);
    }
    // data for graph 1 ACU Accelerate
//    for (int i = 0; i < acc_acu.size(); ++i) {
//      acc_acu_x.append(i - 20);
//      acc_acu[i] = acc_acu[i] / 16;
//    }
    // pass data points to graphs:
    custom_plot.graph(index)->setData(acc_x, acc);
//    customPlot.graph(1)->setData(acc_acu_x, acc_acu);

    // activate top and right axes, which are invisible by default:
//    customPlot->xAxis2->setVisible(true);
//    customPlot->yAxis2->setVisible(true);

    // set ranges appropriate to show data:
    custom_plot.xAxis->setRange(-5, acc_x.last() + 2);
    custom_plot.yAxis->setRange(*acc_min - 2, *acc_max + 2);
//    customPlot->xAxis2->setRange(0, 3.0 * M_PI);
//    customPlot->yAxis2->setRange(-70, 35);
    custom_plot.replot();
}

void CenterWindow::SetupVehicleSpeedAxis(QCustomPlot &custom_plot, int index, QVector<double> speed, QString graph_name)
{
  if(speed.isEmpty()){
      QMessageBox message_box(QMessageBox::Warning, QString(tr("Warning")),QString(tr("Vehicle speed data is empty.")));
      message_box.setStandardButtons (QMessageBox::Ignore | QMessageBox::Cancel);
//      message_box.setButtonText (QMessageBox::Yes, QString("Yes"));
//      message_box.setButtonText (QMessageBox::No, QString("Cancel"));
      message_box.exec();
      return;
    }
  custom_plot.graph(index)->setName(graph_name);
  QVector<double> speed_x;
  auto speed_max = std::max_element(speed.begin(), speed.end());
  auto speed_min = std::min_element(speed.begin(), speed.end());
  for (int i = 0; i < speed.size(); i++) {
      speed_x.append(i);
    }
  custom_plot.graph(index)->setData(speed_x, speed);
  custom_plot.xAxis->setRange(speed_x.first() - 1, speed_x.last() + 2);
  custom_plot.yAxis->setRange(*speed_min - 2, *speed_max + 2);
  custom_plot.replot();
}

void CenterWindow::EventDataProcess(QTableWidget &table_widget, QByteArray &data)
{
  QString event_name = data.mid(1, 2).toHex().toUpper();   // Gets which event it is.
  LOG(INFO) << "Event data: " << dataToHex(data).toStdString();
  data.remove(0, 3);
  // Creat EDR data map and populate it with original data.
  QMap<QString, QVector<char>>data_original;
  QMap<QString, QVector<int>>::const_iterator EDR_data_position_iterator = EDRDataPositionCHN.constBegin();
  while(EDR_data_position_iterator != EDRDataPositionCHN.constEnd()){
      QVector<char> data_;
      // get data from idex EDR_data_position_iterator.value(0) to idex EDR_data_position_iterator.value(1) in data
      for(int i = EDR_data_position_iterator.value().at(0); i < EDR_data_position_iterator.value().at(1) + 1; i++){
          data_.push_back(data[i]);
        }
      data_original.insert(EDR_data_position_iterator.key(), data_);
      EDR_data_position_iterator++;
    }

  // Parse the EDR data.
  EDRData data_processed;
  DecodeEDRData(data_processed, data_original);

  // Get event data.
  //
  if(event_name == "FA13"){
      GetEventData(data_FA13_, data_processed);
    }
  else if(event_name == "FA14"){
      GetEventData(data_FA14_, data_processed);
    }
  else if(event_name == "FA15"){
      GetEventData(data_FA15_, data_processed);
    }

  // Removes all the row and all its items from the table.
  int row_counter = table_widget.rowCount();
  while(row_counter--)
    table_widget.removeRow(row_counter);
  // Print data to tablewidget
  QMap<QString, QVector<QString>>::const_iterator data_processed_iterator = data_processed.EDR_data_CHN_str.constBegin();
  while(data_processed_iterator != data_processed.EDR_data_CHN_str.constEnd()){
      row_counter = table_widget.rowCount();
      table_widget.setRowCount(row_counter + 1);
      table_widget.setItem(row_counter, 0, new QTableWidgetItem(data_processed_iterator.key().mid(2)));  // 打印元素名称
      QString data_str = {};
      for (auto str : data_processed_iterator.value()) {
          data_str.push_back(str + " ");
        }
      table_widget.setItem(row_counter, 1, new QTableWidgetItem(data_str));  // 打印元素数据
      data_processed_iterator++;
    }

  // Save tabledidget data to .csv type file
  SaveTablewidgetData(table_widget, "Output", event_name);

}

void CenterWindow::DecodeAlgorithmIntermediateVariable(QTableWidget &table_widget, QByteArray &data)
{

}

bool CenterWindow::SaveTablewidgetData(QTableWidget &table_widget, QString dir_name, QString file_name)
{
  QDir dir(dir_name);
  QString full_dir_name = QDir::currentPath() + "/" + dir_name;
  if(!dir.exists()){
     dir.mkdir(full_dir_name);
    }
  QString time_str = "_" + QDateTime::currentDateTime().toString("hh:mm:s");
  file_name += time_str.replace(":", "-");
  QString dir_file = full_dir_name + "/" + file_name + ".csv";
  QFile file(dir_file);
  bool ret = file.open(QIODevice::Truncate | QIODevice::ReadWrite);
  if(!ret)
  {
      qDebug() << "open failure";
      return ret;
  }
  QTextStream stream(&file);
  QString contents;
  contents = QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:s") + "\n";
  // 写入头
  QHeaderView * header = table_widget.horizontalHeader();
  if(nullptr != header){
      for (int i = 0; i < header->count(); i++) {
          QTableWidgetItem *item = table_widget.horizontalHeaderItem(i);
          if(nullptr != item){
              contents += item->text() + ",";
            }
        }
      contents += "\n";
    }

  // 写内容
  for (int row = 0; row < table_widget.rowCount(); row++){
      for(int column = 0; column < table_widget.columnCount(); column++){
          QTableWidgetItem * item = table_widget.item(row, column);
          if(nullptr != item){
              QString str = item->text();
              str.replace(",", " ");
              contents += str + ",";
            }
        }
      contents += "\n";
    }
  stream << contents;
  file.close();
  return true;
}

void CenterWindow::PrintSerialData(QByteArray &serial_data)
{
    QString serial_string;
    for (auto data : serial_data) {
        serial_string.push_back(QChar(data));
    }
    ecu_information_line_[0]->clear();
    ecu_information_line_[0]->insert(serial_string);
}

void CenterWindow::PrintHardversionData(QByteArray &hard_version_data)
{
    QString hard_version_string;
    for (auto data : hard_version_data) {
        hard_version_string.push_back(QChar(data));
    }
    ecu_information_line_[1]->clear();
    ecu_information_line_[1]->insert(hard_version_string);
}

void CenterWindow::PrintSoftversionData(QByteArray &soft_version_data)
{
    QString soft_version_string;
    for (auto data : soft_version_data) {
        soft_version_string.push_back(QChar(data));
    }
    ecu_information_line_[2]->clear();
    ecu_information_line_[2]->insert(soft_version_string);
}

void CenterWindow::ReceivedDataHandle(const QTime &time,const QString &dir,const QByteArray &data)
{
  if(dir == "Rx"){
      QByteArray request_type = data.mid(4, 3);
     request_type[0] = request_type.at(0) - 0x40;
      if(request_type == serial_port::MasterSerialThread::ECUSerialNumberDataIdentifier){
          QByteArray data_ = data.mid(7, 17);
          PrintStringInfo(*ecu_information_line_[0], data_);
        }
      if(request_type == serial_port::MasterSerialThread::ECUHardWareVersionNumberDataIdentifier){
          QByteArray data_ = data.mid(7, 10);
          PrintStringInfo(*ecu_information_line_[1], data_);
         }
      if(request_type == serial_port::MasterSerialThread::ECUSoftWareVersionNumberDataIdentifier){
          QByteArray data_ = data.mid(7, 10);
          PrintStringInfo(*ecu_information_line_[2], data_);
         }
      if(request_type == serial_port::MasterSerialThread::ECUManufacturingDateOfProduction){
          QByteArray data_ = data.mid(7, 3);
          PrintDateIdentInfo(*ecu_information_line_[3], data_);
         }
      if(request_type == serial_port::MasterSerialThread::functionConfigrationDataIdentifier){
          QByteArray data_ = data.mid(7, 1);
          PrintWorkModeInfo(*ecu_information_line_[4], data_);
         }
      if(request_type == serial_port::MasterSerialThread::clearDiagnosticInformation){

         }
      if(request_type.mid(0, 2) == serial_port::MasterSerialThread::reportDTCByStatusMask.mid(0, 2)){
          QByteArray data_ = data.mid(7, data.size() - 8);
          DecodeDTC(*print_dtc_table_, data_);
         }
      if(request_type == serial_port::MasterSerialThread::eventData13){
          QByteArray data_ = data.mid(4, 250) + data.mid(259, 250) + data.mid(514, 250) + data.mid(769, 25);
          EventDataProcess(*print_event_data_table_, data_);
         }
      if(request_type == serial_port::MasterSerialThread::eventData14){
          QByteArray data_ = data.mid(4, 250) + data.mid(259, 250) + data.mid(514, 250) + data.mid(769, 25);
          EventDataProcess(*print_event_data_table_, data_);
         }
      if(request_type == serial_port::MasterSerialThread::eventData15){
          QByteArray data_ = data.mid(4, 250) + data.mid(259, 250) + data.mid(514, 250) + data.mid(769, 25);
          EventDataProcess(*print_event_data_table_, data_);
         }
    }
}

void CenterWindow::ClearECUInf()
{
  QMessageBox message_box(QMessageBox::Warning, QString(tr("Warning")),QString(tr("All ECU information is about to be cleared.")));
  message_box.setStandardButtons (QMessageBox::Yes|QMessageBox::No);
  message_box.setButtonText (QMessageBox::Yes,QString("Yes"));
  message_box.setButtonText (QMessageBox::No,QString("Cancel"));
  int res= message_box.exec();
  if(res == QMessageBox::Yes){
      // Removes its items from the QLineEdit.
      for (int i = 0; i < 5; i++) {
          ecu_information_line_[i]->clear();
        }
    }

}

void CenterWindow::ClearWidgetData(QTableWidget &table)
{
  QMessageBox message_box(QMessageBox::Warning, QString(tr("Warning")),QString(tr("Everything is about to be cleared.")));
  message_box.setStandardButtons (QMessageBox::Yes | QMessageBox::No);
  message_box.setButtonText (QMessageBox::Yes, QString("Yes"));
  message_box.setButtonText (QMessageBox::No, QString("Cancel"));
  int res= message_box.exec();
  if(res == QMessageBox::Yes){
      // Removes all the row and all its items from the table.
      int row_counter = table.rowCount();
      while(row_counter--)
        table.removeRow(row_counter);
    }
}


