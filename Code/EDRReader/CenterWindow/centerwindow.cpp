/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.3
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.10
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

typedef unsigned int data_type;

CenterWindow::CenterWindow(QWidget *parent) : QWidget(parent)
{
    InitUI();
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
    /// ECU information
    /// ——————QFormLayout(ECU_information_form)——————————————————
    ///|
    ///|     |序列号|        serial_line_
    ///|     |硬件版本号|   hardware_version_line_
    ///|     |软件版本号|     software_version_line_
    ///|     |生产日期|       manufacturing_date_line_
    ///|     |功能配置字|     function_configration_data_line_
    ///|_________________________________________________________
    QFormLayout *ecu_information_form = new QFormLayout;   /// 放置ECU信息控件 表单
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
    /// Creates a new table view with the 0 rows and 3 columns, and with the given parent.
    print_dtc_table_ = new QTableWidget(0, 3, this);
    /// Sets the horizontal header labels using QStringList() << "DTC" << "Status" << "Description   "
    print_dtc_table_->setHorizontalHeaderLabels(QStringList() << "DTC" << "Status" << "Description   ");
    /// Initiate item No editing possible.
    print_dtc_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /// Resizes all columns based on the size hints of the delegate used to render each item in the columns.
    print_dtc_table_->resizeColumnsToContents();
    /// Resizes all rows based on the size hints of the delegate used to render each item in the rows.
    print_dtc_table_->resizeRowsToContents();
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


void CenterWindow::InitConnect()
{
    /// ECU Serial Data Identifier
    connect(this->ecu_information_btn_[0], &QPushButton::clicked, [this](){
        char serial_char[17] = {0x20, 0x20, 0x20, 0x57, 0x54, 0x44, 0x32, 0x32, 0x30, 0x36, 0x30, 0x39, 0x30, 0x30, 0x30, 0x30, 0x31};
        QByteArray serial_;
        for (auto data : serial_char) {
            serial_.push_back(data);
        }
        PrintStringInfo(*ecu_information_line_[0], serial_);
    });

    /// ECU Hardversion Data Identifier
    connect(this->ecu_information_btn_[1], &QPushButton::clicked, [=](){
        char hard_version[8] = {0x48, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
        QByteArray hard_;
        for (auto data : hard_version) {
            hard_.push_back(data);
        }
        PrintStringInfo(*ecu_information_line_[1], hard_);
    });

    /// ECU Softversion Data Identifier
    connect(this->ecu_information_btn_[2], &QPushButton::clicked, [=](){
        char soft_version[8] = {0x53, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
        QByteArray soft_;
        for (auto data : soft_version) {
            soft_.push_back(data);
        }
        PrintStringInfo(*ecu_information_line_[2], soft_);
    });

    /// ECU Manufacture Data Identifier
    connect(this->ecu_information_btn_[3], &QPushButton::clicked, [=](){
        char manufacture_data[8] = {0x22, 0x06, 0x10};
        QByteArray manufacture_data_;
        for (auto data : manufacture_data) {
            manufacture_data_.push_back(data);
        }
        PrintDataIdentInfo(*ecu_information_line_[3], manufacture_data_);
    });


    /// ECU Function Configration Data Identifier
    connect(this->ecu_information_btn_[4], &QPushButton::clicked, [=](){
        char function_configration_data_identifier[1] = {0x03};
        QByteArray function_configration_data_identifier_;
        for (auto data : function_configration_data_identifier) {
            function_configration_data_identifier_.push_back(data);
        }
        PrintWorkModeInfo(*ecu_information_line_[4], function_configration_data_identifier_);
    });

    /// Decode DTC information
    ///
    connect(this->read_dtc_btn, &QPushButton::clicked, [=](){
        char dtc[23] = {0x59, 0x02, 0x09, 0x11, 0x01, 0x00, 0x09, 0x11, 0x01, 0x00, 0x09, static_cast<char>(0xC1), 0x41, 0x00, 0x09, static_cast<char>(0xC1), 0x00, 0x00, 0x09, 0x01, 0x01, 0x00, 0x09};
        QByteArray dtc_;
        for (auto data : dtc) {
            dtc_.push_back(data);
        }
        DecodeDTC(*print_dtc_table_, dtc_);
    });
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
    const char normol_mode = 0x01;   /// 正常模式
    const char factory_mode = 0x02;  /// 工厂模式
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

void CenterWindow::PrintDataIdentInfo(QLineEdit &line_edit, QByteArray &data)
{
    bool ok;
//    int year_int = QString::number(data[0], 16).toInt(&ok, 10);
    data_type year = static_cast<unsigned int>(2000 + QString::number(data[0], 16).toInt(&ok, 10));
    data_type month = static_cast<unsigned int>(QString::number(data[1], 16).toInt(&ok, 10));
    data_type day = static_cast<unsigned int>(QString::number(data[2], 16).toInt(&ok, 10));
    line_edit.clear();
    line_edit.insert(QString::number(year,10) + "." + QString::number(month, 10) + "." + QString::number(day, 10));
}

void CenterWindow::DecodeDTC(QTableWidget &table_widget, QByteArray &data)
{
    /// Removes all the row and all its items from the table.
    int row_counter = table_widget.rowCount();
    while(row_counter--)
        table_widget.removeRow(row_counter);
    /// 分割故障码
    QVector<QVector<unsigned char>> dtc_vector;
    data.remove(0, 3);
    for (int i = 0;i < data.size() / 4; i++) {
        QVector<unsigned char> dtc_vector_;
        for (int j = i * 4;j < i * 4 + 4; j++) {
            dtc_vector_.push_back(static_cast<unsigned char>(data.at(j)));
        }
        dtc_vector.push_back(dtc_vector_);
    }
    for (auto dtc_vector_ : dtc_vector) {
        QByteArray dtc_status;
        dtc_status[0] = static_cast<char>(dtc_vector_.last());  /// 获取故障码状态
        dtc_vector_.remove(3);
        auto search = DTC.find(dtc_vector_);   /// 查找DTC中是否包含相应的故障码
        if (search != DTC.end()){              /// 查找到响应的DTC
            QByteArray dtc_array_key;
            for (int i = 0; i < search.key().size(); i++) {  /// 将char类型转为QByteArray类型
                dtc_array_key.push_back(static_cast<char>(search.key()[i]));
            }
            QString dtc_array_key_str = dataToHex(dtc_array_key);  /// 将QByteArray类型转为QString
            QString dtc_status_str = dataToHex(dtc_status);
            int row_counter = table_widget.rowCount();
            table_widget.setRowCount(row_counter + 1);
            table_widget.setItem(row_counter, 0, new QTableWidgetItem(dtc_array_key_str));  /// 打印DTC
            table_widget.setItem(row_counter, 1, new QTableWidgetItem(dtc_status_str));     /// 打印DTC状态
            table_widget.setItem(row_counter, 2, new QTableWidgetItem(search.value()));     /// 打印中文描述
        } else{   /// 未查找到相应的DTC
            QByteArray dtc_array_unconfirmed;
            for (auto dtc_vector__ : dtc_vector_) {   ///将char类型转为QByteArray类型
                dtc_array_unconfirmed.push_back(static_cast<char>(dtc_vector__));
            }
            QString dtc_array_unconfirmed_str = dataToHex(dtc_array_unconfirmed);  /// 将QByteArray类型转为QString
            QString dtc_status_str = dataToHex(dtc_status);
            int row_counter = table_widget.rowCount();
            table_widget.setRowCount(row_counter + 1);
            table_widget.setItem(row_counter, 0, new QTableWidgetItem(dtc_array_unconfirmed_str));  /// 打印DTC
            table_widget.setItem(row_counter, 1, new QTableWidgetItem(dtc_status_str));  /// 打印DTC状态
            table_widget.setItem(row_counter, 2, new QTableWidgetItem("本地未定义"));     /// 打印中文描述

        }
    }

//    QMap<QVector<unsigned char>, QString>::const_iterator dtc_ = DTC.constBegin();
//    while(dtc_ != DTC.constEnd()){
//        QString dtc_string;
//        QByteArray dtc_array;
//        for (int i = 0; i < dtc_.key().size(); i++) {
//            dtc_array.push_back(static_cast<char>(dtc_.key()[i]));
//        }
//        dtc_string = dataToHex(dtc_array);
//        int row_counter = table_widget.rowCount();
//        table_widget.setRowCount(row_counter + 1);
//        table_widget.setItem(row_counter, 0, new QTableWidgetItem(dtc_string));
//        table_widget.setItem(row_counter, 2, new QTableWidgetItem(dtc_.value()));
//        ++dtc_;
//    }
}

void CenterWindow::SetupAccAxis(QCustomPlot *customPlot)
{
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    // setup for graph 0: key axis left, value axis bottom
    // will contain left maxwell-like function
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis);
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
    //customPlot->graph(1)->setErrorType(QCPGraph::etValue);
    customPlot->graph(1)->setName("ACU Acc");

    /// Generate data
    QVector<double> x0(126), y0(126);
    for (int i = 0; i < y0.size(); ++i) // data for graph 0
    {
      x0[i] = i;
//      srand(static_cast<unsigned>(time(NULL)));
      y0[i] = rand() % 120;
    }
    /// pass data points to graphs:
    customPlot->graph(0)->setData(x0, y0);
    /// activate top and right axes, which are invisible by default:
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    /// set ranges appropriate to show data:
    customPlot->xAxis->setRange(0, 130);
    customPlot->yAxis->setRange(0, 130);
    customPlot->xAxis2->setRange(0, 3.0*M_PI);
    customPlot->yAxis2->setRange(-70, 35);

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

QByteArray dataToHex(const QByteArray &data, const QString &separator, const QString &prefix) {
    if (separator.isEmpty() && prefix.isEmpty()) {
        return data.toHex().toUpper();
    }

    QStringList list;
    auto len = data.count();
    for (int i = 0; i < len; i++) {
        list.append(prefix);
        auto hex = QString::number(data.at(i) & 0xFF, 16).toUpper();
        while (hex.size() < 2) {
            hex.prepend('0');
        }
        list.append(hex);
        if (i < len - 1) {
            list.append(separator);
        }
    }
    return list.join("").toUtf8();
}
