/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.4
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.02-2022.06.20
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

extern QByteArray dataToHex(const QByteArray &data, const QString &separator = " ", const QString &prefix = "");
extern QByteArray ReadFromFile(QString path);
extern QVector<QString> DataToString(QByteArray array, int base);
extern QVector<QString> DataToString(QVector<int> array, int base);
extern QVector<QString> DataToString(QVector<double> array, int precision);
extern QVector<QString> DataToString(char array, int precision);
extern QVector<QString> DataToString(QVector<uint8_t> array, int precision);
extern QVector<QString> DataToString(QVector<uint16_t> array, int precision);

extern bool IsValid(char data);
extern bool IsValid(uint16_t data);

class CenterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWindow(QWidget *parent = nullptr);

public:
    void InitUI();
    void InitConnect();
    void EDRDataProcess(EDRData &data_processed, const QMap<QString, QVector<char> > data_original);

private:
    QWidget* base_widget_{nullptr};  // 基础窗体

    /// <summary>
    /// ECU information
    /// ecu_information_btn_[0] : 序列号
    /// ecu_information_btn_[1] : 硬件版本号
    /// ecu_information_btn_[2] : 软件版本号
    /// ecu_information_btn_[3] : 生产日期
    /// ecu_information_btn_[4] : 功能配置字
    ///
    /// ecu_information_line_[0] : 序列号
    /// ecu_information_line_[1] : 硬件版本号
    /// ecu_information_line_[2] : 软件版本号
    /// ecu_information_line_[3] : 软件版本号
    /// ecu_information_line_[4] : 功能配置字
    /// <summary>
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

    /// <function summary>
    /// 向QLineEdit打印字符串
    /// 输入ASCII, 输出QString
    /// e.g.
    /// QByteArray soft_version = {0x53, 0x57, 0x3a, 0x30, 0x31, 0x2e, 0x30, 0x31};
    /// QLineEdit *information_line = new QEditLine;
    /// PrintStringInfo(*information_line, soft_version);  // information_line 输出 SW:01.01
    ///
    /// <function summary>
    void PrintStringInfo(QLineEdit &line_edit, QByteArray &data);

    /// <function summary>
    /// 向QLineEdit打印字符串
    /// 输入ASCII, 输出工作模式
    /// e.g.
    /// QByteArray work_mode = {0x01};
    /// QLineEdit *information_line = new QEditLine;
    /// PrintStringInfo(*information_line, work_mode);  // information_line 输出 正常模式
    ///
    /// <function summary>
    void PrintWorkModeInfo(QLineEdit &line_edit, QByteArray &data);

    /// <function summary>
    /// 向QLineEdit打印字符串
    /// 输入BCD, 输出日期
    /// e.g.
    /// QByteArray date_identifier = {0x22, 0x06, 0x10};
    /// QLineEdit *information_line = new QEditLine;
    /// PrintStringInfo(*information_line, date_identifier);  // information_line 输出 2022.6.10
    ///
    /// <function summary>
    void PrintDateIdentInfo(QLineEdit &line_edit, QByteArray &data);

    /// <function summary>
    /// 解析DTC并输出至QTableWidget
    ///
    /// <function summary>
    void DecodeDTC(QTableWidget &table_widget, QByteArray &data);

    /// <function summary>
    /// 绘制加速度曲线
    ///
    /// <function summary>
    void SetupAccAxis(QCustomPlot *customPlot);

    /// <function summary>
    /// Decode EDR data
    ///
    /// <function summary>
    void DecodeEventData(QTableWidget &table_widget, QByteArray &data);

    /// <function summary>
    /// Save tablewidget data
    ///
    /// <function summary>
    bool SaveTablewidgetData(QTableWidget &table_widget, QString dir_name, QString file_name);

    void PrintSerialData(QByteArray &serial_data);  // ecu_information_line_[0]
    void PrintHardversionData(QByteArray &hard_version_data);  // ecu_information_line_[1]
    void PrintSoftversionData(QByteArray &soft_version_data);

};


#endif // CENTERWINDOW_H
