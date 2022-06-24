/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version  : 0.0.1
** Author   : DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.07-2022.06.24
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

typedef signed char checksum_type;

static const char kErrorCodeCRC = static_cast<char>(0x00);
static const char kErrorWriteTimeout = static_cast<char>(0x01);
static const char kErrorResponseData = static_cast<char>(0x02);
static const char kErrorResponseTimeout = static_cast<char>(0x03);


namespace serial_port
{
//! [0]
class MasterSerialThread : public QThread
{
    Q_OBJECT

public:
    explicit MasterSerialThread(QObject *parent = nullptr);
    ~MasterSerialThread() override;

    // <summary>
    // 发送数据, 超时时间、数据;
    // </summary>
    void TransAction(int wait_timeout, const QByteArray &request);

    // <summary>
    // 设置串口通信 波特率、数据位、校验位、停止位
    // </summary>
    void SetSCOM(qint32 baudRate , QSerialPort::DataBits dataBits ,QSerialPort::Parity parity,QSerialPort::StopBits stopBits);

    // <summary>
    // 获取串口信息
    // </summary>
    void GetSerialInfo();

    static const QByteArray ECUInformationCheck;
    static const QByteArray ECUSerialNumberDataIdentifier;
    static const QByteArray ECUHardWareVersionNumberDataIdentifier;
    static const QByteArray ECUSoftWareVersionNumberDataIdentifier;
    static const QByteArray ECUManufacturingDateOfProduction;
    static const QByteArray functionConfigrationDataIdentifier;
    static const QByteArray clearDiagnosticInformation;
    static const QByteArray reportDTCByStatusMask;
    static const QByteArray eventData13;
    static const QByteArray eventData14;
    static const QByteArray eventData15;
    static const QByteArray eventData16;
    static const QByteArray eventData17;
    static const QByteArray eventData18;
    static const QByteArray eventData19;

    static const QByteArray SOF;  // start of frame
    static const QByteArray slaveID;  // slave device ID
signals:
    void ResponseOrRequest(const QTime &time,const QString &dir,const QByteArray &s);
    void Error(const QString &s);

    // <summary>
    // 错误码 包含系统时间、错误类型
    // </summary>
    void ErrorCode(const QString &time,const char &error_code);
    void Timeout(const QString &s);
    void SerialStatus(const QString &port_name, const qint32 baudrate, const bool flag);

private:
    void run() override;

    // <summary>
    // 计算校验和
    // </summary>
    checksum_type CalculateCheckSum(QByteArray &data);

    QString port_name_;     // port number
    QByteArray request_;    // request data
    QByteArray response_;   // response data
    int wait_timeout_ = 0;  // timeout, The default value is 0
    QMutex mutex_;
    QWaitCondition cond_;
    bool quit_ = false;          // 退出线程标志位
    qint32 baud_rate_ = 256000;  // baud rate 256000 bps
    QSerialPort::DataBits data_bits_ = QSerialPort::Data8;
    QSerialPort::Parity parity_ = QSerialPort::NoParity;  // 无校验位
    QSerialPort::StopBits stop_bits_ = QSerialPort::OneStop;


};
//! [0]


};

#endif // MASTERSERIALTHREAD_H
