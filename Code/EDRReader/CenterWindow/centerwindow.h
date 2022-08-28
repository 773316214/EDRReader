/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 1.0.2
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.24
**
****************************************************************************/

#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include "dataconfiguration.h"

#include "QCustomPlot/fcustomplot.h"

struct EventData{
  QVector<double> longitudinal_acceleration{};
  QVector<double> vehicle_speed{};
};

class CenterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWindow(QWidget *parent = nullptr);

public:
    void InitUI();
    void InitConnect();
    void DecodeEDRData(EDRData &data_processed, const QMap<QString, QVector<char> > data_original);
    void AlgorithmIntermediateVariableProcess(EDRData &data_processed, const QMap<QString, QVector<char>> data_original);
    void InitPlot(QCustomPlot &customplot, QString graph1_name, QString graph2_name);
    void GetEventData(EventData &event_data, const EDRData data_processed);
    // <summary>
    // ECU information btn
    // ecu_information_btn_[0] : 序列号
    // ecu_information_btn_[1] : 硬件版本号
    // ecu_information_btn_[2] : 软件版本号
    // ecu_information_btn_[3] : 生产日期
    // ecu_information_btn_[4] : 功能配置字
    // <summary>
    QPushButton *ecu_information_btn_[5]{nullptr};

    // ECU fault information
    QPushButton *clear_dtc_btn{nullptr};  // 清除DTC
    QPushButton *read_dtc_btn{nullptr};   // 读取DTC
    //Event data
    QPushButton *event_data_btn_[8]{nullptr};
private:
    QWidget* base_widget_{nullptr};  // 基础窗体

    // <summary>
    // ECU information line
    // ecu_information_line_[0] : 序列号
    // ecu_information_line_[1] : 硬件版本号
    // ecu_information_line_[2] : 软件版本号
    // ecu_information_line_[3] : 软件版本号
    // ecu_information_line_[4] : 功能配置字
    // <summary>
    QLineEdit *ecu_information_line_[5]{nullptr};

    // ECU fault information
    QPushButton *clear_dtc_inf_btn_{nullptr};   //
    QTableWidget *print_dtc_table_{nullptr};    // 打印DTC
    //Event data
    QTableWidget *print_event_data_table_{nullptr};    // 打印DTC

    //Axis-Event
    QPushButton *axis_btn_[7]{nullptr};
    FCustomPlot *acc_axis_{nullptr};
    FCustomPlot *data_axis_{nullptr};
    EventData data_FA13_;
    EventData data_FA14_;
    EventData data_FA15_;
//    QVector<double> longitudinal_acceleration13_{};
//    QVector<double> longitudinal_acceleration14_{};
//    QVector<double> longitudinal_acceleration15_{};
    QMap<QString, QVector<double>>acceleration16_{};
    QMap<QString, QVector<double>>acceleration17_{};
    QMap<QString, QVector<double>>acceleration18_{};
    QMap<QString, QVector<double>>acceleration19_{};

    enum GraphIndexSet{edr_index = 0, acu_index = 1};  // 曲线索引
signals:

public slots:

    // <function summary>
    // 向QLineEdit打印字符串
    // 输入ASCII, 输出QString
    // e.g.
    // QByteArray soft_version = {0x53, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
    // QLineEdit *information_line = new QEditLine;
    // PrintStringInfo(*information_line, soft_version);  // information_line 输出 SW:01.01
    //
    // <function summary>
    void PrintStringInfo(QLineEdit &line_edit, QByteArray &data);

    // <function summary>
    // 向QLineEdit打印字符串
    // 输入ASCII, 输出工作模式
    // e.g.
    // QByteArray work_mode = {0x01};
    // QLineEdit *information_line = new QEditLine;
    // PrintStringInfo(*information_line, work_mode);  // information_line 输出 正常模式
    //
    // <function summary>
    void PrintWorkModeInfo(QLineEdit &line_edit, QByteArray &data);

    // <function summary>
    // 向QLineEdit打印字符串
    // 输入BCD, 输出日期
    // e.g.
    // QByteArray date_identifier = {0x22, 0x06, 0x10};
    // QLineEdit *information_line = new QEditLine;
    // PrintStringInfo(*information_line, date_identifier);  // information_line 输出 2022.6.10
    //
    // <function summary>
    void PrintDateIdentInfo(QLineEdit &line_edit, QByteArray &data);

    // <function summary>
    // 解析DTC并输出至QTableWidget
    //
    // <function summary>
    void DecodeDTC(QTableWidget &table_widget, QByteArray &data);

    // <function summary>
    // 绘制加速度曲线
    //
    // <function summary>
    void SetupAccAxis(QCustomPlot &custom_plot, int index, QVector<double> acc, QString graph_name);

    // <function summary>
    // 绘制车辆速度曲线
    //
    // <function summary>
    void SetupVehicleSpeedAxis(QCustomPlot &custom_plot, int index, QVector<double> speed, QString graph_name);

    // <function summary>
    // Decode EDR data
    //
    // <function summary>
    void EventDataProcess(QTableWidget &table_widget, QByteArray &data);
    void DecodeAlgorithmIntermediateVariable(QTableWidget &table_widget, QByteArray &received_data);
    void GetAlgorithmIntermediateVariable(QByteArray received_data, QMap<QString, QVector<QString>> &algo_intermediate_varible, QMap<QString, QMap<QString, int>> data_length);


    // <function summary>
    // Save tablewidget data
    //
    // <function summary>
    bool SaveTablewidgetData(QTableWidget &table_widget, QString dir_name, QString file_name);

    void PrintSerialData(QByteArray &serial_data);  // ecu_information_line_[0]
    void PrintHardversionData(QByteArray &hard_version_data);  // ecu_information_line_[1]
    void PrintSoftversionData(QByteArray &soft_version_data);

    // <function summary>
    // Process the received serial port data
    //
    // <function summary>
    void ReceivedDataHandle(const QTime &time,const QString &dir,const QByteArray &data);


    // <function summary>
    // Clears the contents of QLineEdit
    //
    // <function summary>
    void ClearECUInf();

    // <function summary>
    // Clears the contents of QTableWidget
    //
    // <function summary>
    void ClearWidgetData(QTableWidget &table);

};


#endif // CENTERWINDOW_H
