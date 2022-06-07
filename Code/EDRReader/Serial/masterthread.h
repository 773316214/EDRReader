/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.0
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.07-2022.06.07
**
****************************************************************************/

#ifndef SERIAL_PROTOCOL
#define SERIAL_PROTOCOL

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QTextBrowser>
#include <QMap>
#include <QMetaType>


static const char kErrorCodeCRC = static_cast<char>(0x00);
static const char kErrorWriteTimeout = static_cast<char>(0x01);
static const char kErrorResponseData = static_cast<char>(0x02);
static const char kErrorResponseTimeout = static_cast<char>(0x03);

static const QByteArray ECUInformationCheck = QByteArrayLiteral("\xAA\xAA\xAA");
static const QByteArray functionConfigrationDataIdentifier = QByteArrayLiteral("\x22\xF1\x01");
static const QByteArray ECUManufacturingDateOfProduction = QByteArrayLiteral("\x22\xF1\x8B");
static const QByteArray ECUSerialNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x8C");
static const QByteArray ECUHardWareVersionNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x93");
static const QByteArray ECUSoftWareVersionNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x95");
static const QByteArray reportDTCByStatusMask = QByteArrayLiteral("\x19\x02\xFF");
static const QByteArray clearDiagnosticInformation = QByteArrayLiteral("\x14\xFF\xFF");
static const QByteArray eventData13 = QByteArrayLiteral("\x22\xFA\x13");
static const QByteArray eventData14 = QByteArrayLiteral("\x22\xFA\x14");
static const QByteArray eventData15 = QByteArrayLiteral("\x22\xFA\x15");
static const QByteArray eventData16 = QByteArrayLiteral("\x22\xFA\x16");
static const QByteArray eventData17 = QByteArrayLiteral("\x22\xFA\x17");
static const QByteArray eventData18 = QByteArrayLiteral("\x22\xFA\x18");
static const QByteArray eventData19 = QByteArrayLiteral("\x22\xFA\x19");



namespace serial_port
{
//! [0]
class MasterSerialThread : public QThread
{
    Q_OBJECT

public:
    explicit MasterSerialThread(QObject *parent = nullptr);
    ~MasterSerialThread() override;

    /// <summary>
    /// 发送数据，串口号、超时时间、数据;
    /// </summary>
    void TransAction(const QString &port_name, int wait_timeout, const QByteArray &request);

    /// <summary>
    /// 设置串口通信 波特率、数据位、校验位、停止位
    /// </summary>
    void SetSCOM(qint32 baudRate , QSerialPort::DataBits dataBits ,QSerialPort::Parity parity,QSerialPort::StopBits stopBits);

    /// <summary>
    /// 获取串口信息
    /// </summary>
    void GetSerialInfo();


signals:
    void ResponseOrRequest(const QTime &time,const QString &dir,const QByteArray &s);
    void Error(const QString &s);

    /// <summary>
    /// 错误码 包含系统时间、错误类型
    /// </summary>
    void ErrorCode(const QString &time,const char &error_code);
    void Timeout(const QString &s);
    void SerialStatus(const QString &port_name, const qint32 baudrate, const bool flag);

private:
    void run() override;

    QString port_name_;     // 串口号
    QByteArray request_;    // 请求数据
    int wait_timeout_ = 0;  // 超时时间，默认为0
    QMutex mutex_;
    QWaitCondition cond_;
    bool quit_ = false;          // 退出线程标志位
    qint32 baud_rate_ = 256000;  // 波特率256000
    QSerialPort::DataBits data_bits_ = QSerialPort::Data8;
    QSerialPort::Parity parity_ = QSerialPort::NoParity;  // 无校验位
    QSerialPort::StopBits stop_bits_ = QSerialPort::OneStop;
};
//! [0]


};

#endif // MASTERSERIALTHREAD_H
