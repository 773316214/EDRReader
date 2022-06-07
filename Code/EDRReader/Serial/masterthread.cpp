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

#include "masterthread.h"
#include "Log/flog.h"

namespace serial_port
{

MasterSerialThread::MasterSerialThread(QObject *parent) :
    QThread(parent)
{
}




MasterSerialThread::~MasterSerialThread()
{
    mutex_.lock();
    quit_ = true;
    cond_.wakeOne();
    mutex_.unlock();
    wait();
}
void MasterSerialThread::TransAction(const QString &port_name, int wait_timeout, const QByteArray &request)
{
    const QMutexLocker locker(&mutex_);
    port_name_ = port_name;
    wait_timeout_ = wait_timeout;
    request_ = request;
    if (!isRunning())
        start();
    else
        cond_.wakeOne();
}

void MasterSerialThread::run()
{
    bool current_port_name_changed = false;

    mutex_.lock();
    QString current_port_name;
    if (current_port_name != port_name_) {
        current_port_name = port_name_;
        current_port_name_changed = true;
    }

    int current_wait_timeout = wait_timeout_;
    QByteArray current_request = request_;
    mutex_.unlock();
    QSerialPort serial;

    if (current_port_name.isEmpty()) {
        emit Error(tr("No port name specified"));
        return;
    }

    while (!quit_) {
        if (current_port_name_changed) {
            serial.close();  //串口关闭
            emit SerialStatus(port_name_, baud_rate_, false); //发送串口关闭信号
            serial.setPortName(current_port_name);

            if (!serial.open(QIODevice::ReadWrite)) {
                emit Error(tr("Can't open %1, error code %2")
                           .arg(port_name_).arg(serial.error()));
                return;
            }
            serial.setBaudRate(baud_rate_);         // 波特率
            serial.setDataBits(data_bits_);         // 数据位
            serial.setParity(parity_);             // 校验位
            serial.setStopBits(stop_bits_);         // 停止位

            emit SerialStatus(port_name_, baud_rate_, true); //串口已打开 发送串口开启信号
        }
        // write request
        const QByteArray request_data = current_request;
        serial.write(request_data); //发送串口指令
        emit ResponseOrRequest(QTime::currentTime(),"Tx",request_data); //finish sending
        if (serial.waitForBytesWritten(wait_timeout_)) {
            // read response
            if (serial.waitForReadyRead(current_wait_timeout)) {
                QByteArray response_data = {};
                response_data = serial.readAll();
                while (serial.waitForReadyRead(100))
                    response_data += serial.readAll();
                emit ResponseOrRequest(QTime::currentTime(),"Rx",response_data); //finish receiving
#if 0
                //check response
                QByteArray  response_data_temp = request_data;
                if(response_data_temp[4] == response_data[4]){
                    //crc check
                    char crc = '\0';
                    for(int i = 0;i < response_data.size() - 1; i++){
                        crc += response_data[i];
                    }
                    crc = crc & (static_cast<char>(0xff));
                    if(response_data[8] != crc){
                        emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ",kErrorCodeCRC); //crc error
                    }
                }
                else emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ",kErrorResponseData); //response data error
#endif
            } else {
                emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ",kErrorResponseTimeout); //response timeout
            }
        } else {
            emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ",kErrorWriteTimeout); //write timeout
        }
        mutex_.lock();
        cond_.wait(&mutex_);
        if (current_port_name != port_name_) {
            current_port_name = port_name_;
            current_port_name_changed = true;
        } else {
            current_port_name_changed = false;
        }
        current_wait_timeout = wait_timeout_;
        current_request = request_;
        mutex_.unlock();
    }
}

/// 设置串口参数
/// 默认配置： 波特率 = 256000 ； 数据位 = 8 ; 校验位 = None ； 停止位 = 1 ；
void MasterSerialThread::SetSCOM(qint32 baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    baud_rate_ = baudRate;
    data_bits_ = dataBits;
    parity_ = parity;
    stop_bits_ = stopBits;
}

void MasterSerialThread::GetSerialInfo()
{
    QList<QSerialPortInfo> serial_port_info = QSerialPortInfo::availablePorts();
    int count = serial_port_info.count();
    for(int i = 0;i < count;i++){
        serial_port_info[i].description();  // 获取描述信息
    }
}
};


