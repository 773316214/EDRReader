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

#include "masterthread.h"
#include "Log/flog.h"
#include "Universal/universal.h"

namespace serial_port
{

   const QByteArray MasterSerialThread::ECUInformationCheck = QByteArrayLiteral("\xAA\xAA\xAA");
   const QByteArray MasterSerialThread::ECUSerialNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x8C");
   const QByteArray MasterSerialThread::ECUHardWareVersionNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x93");
   const QByteArray MasterSerialThread::ECUSoftWareVersionNumberDataIdentifier = QByteArrayLiteral("\x22\xF1\x95");
   const QByteArray MasterSerialThread::ECUManufacturingDateOfProduction = QByteArrayLiteral("\x22\xF1\x8B");
   const QByteArray MasterSerialThread::functionConfigrationDataIdentifier = QByteArrayLiteral("\x22\xF1\x01");
   const QByteArray MasterSerialThread::clearDiagnosticInformation = QByteArrayLiteral("\x14\xFF\xFF");
   const QByteArray MasterSerialThread::reportDTCByStatusMask = QByteArrayLiteral("\x19\x02\xFF");
   const QByteArray MasterSerialThread::eventData13 = QByteArrayLiteral("\x22\xFA\x13");
   const QByteArray MasterSerialThread::eventData14 = QByteArrayLiteral("\x22\xFA\x14");
   const QByteArray MasterSerialThread::eventData15 = QByteArrayLiteral("\x22\xFA\x15");
   const QByteArray MasterSerialThread::eventData16 = QByteArrayLiteral("\x22\x02\x16");
   const QByteArray MasterSerialThread::eventData17 = QByteArrayLiteral("\x22\x02\x17");
   const QByteArray MasterSerialThread::eventData18 = QByteArrayLiteral("\x22\x02\x18");
   const QByteArray MasterSerialThread::eventData19 = QByteArrayLiteral("\x22\x02\x19");

   const QByteArray MasterSerialThread::SOF = QByteArrayLiteral("\xAA\xAA");  // start of frame
   const QByteArray MasterSerialThread::slaveID = QByteArrayLiteral("\x01");  // slave device ID

MasterSerialThread::MasterSerialThread(QObject *parent) :
    QThread(parent)
{
  GetSerialInfo();
  TransAction(100, ECUInformationCheck);
}




MasterSerialThread::~MasterSerialThread()
{
    mutex_.lock();
    quit_ = true;
    cond_.wakeOne();
    mutex_.unlock();
    wait();
}
void MasterSerialThread::TransAction(int wait_timeout, const QByteArray &request)
{
    const QMutexLocker locker(&mutex_);
    wait_timeout_ = wait_timeout;
    request_ = SOF + slaveID + request;
    request_.insert(3, static_cast<signed char>(request_.size()));   // Insert data length code at idex 3
    request_.push_back(CalculateCheckSum(request_));
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
                LOG(INFO) << tr("Can't open %1, error code %2").arg(port_name_).arg(serial.error()).toStdString();
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
        emit ResponseOrRequest(QTime::currentTime(), "Tx", request_data);  //finish sending
        LOG(INFO) << "Write data: " + dataToHex(request_data).toStdString();
        if (serial.waitForBytesWritten(wait_timeout_)) {
            // read response
            if (serial.waitForReadyRead(current_wait_timeout)) {
                QByteArray response_data = {};
                response_data = serial.readAll();
                while (serial.waitForReadyRead(100)){
                    response_data += serial.readAll();
                  }
                LOG(INFO) << "Receive data: " + dataToHex(response_data).toStdString();
                QByteArray request_data_ = request_data.mid(4, 3);
                QByteArray response_data_ = response_data.mid(4, 3);
                response_data_[0] = response_data_[0] - 0x40;
                if(request_data_ == response_data_){
                    emit ResponseOrRequest(QTime::currentTime(), "Rx", response_data);  // finish receiving
                  }
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
                emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ", kErrorResponseTimeout); //response timeout
                LOG(INFO) << "Error code:" << ('\t' + QString::number(kErrorResponseTimeout, 16)).toStdString();
            }
        } else {
            emit ErrorCode(QTime::currentTime().toString("hh:mm:ss.zzz") + "   error code   ", kErrorWriteTimeout); //write timeout
            LOG(INFO) << "Error code:" << ('\t' + QString::number(kErrorWriteTimeout, 16)).toStdString();
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

checksum_type MasterSerialThread::CalculateCheckSum(QByteArray &data)
{
  signed char check_sum = '\0';
  for(auto data_ : data){
      check_sum += data_;
    }
  return check_sum;
}

// 设置串口参数
// 默认配置： 波特率 = 256000; 数据位 = 8; 校验位 = None; 停止位 = 1;
void MasterSerialThread::SetSCOM(qint32 baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    baud_rate_ = baudRate;
    data_bits_ = dataBits;
    parity_ = parity;
    stop_bits_ = stopBits;
}

// 获取描述信息
void MasterSerialThread::GetSerialInfo()
{
    QList<QSerialPortInfo> serial_port_info = QSerialPortInfo::availablePorts();
    int count = serial_port_info.count();
    QString target_serial_description = "USB-SERIAL CH340";
    for(int i = 0;i < count;i++){
        if(serial_port_info[i].description() == target_serial_description){
            port_name_ = serial_port_info[i].portName();
          }
    }
}
};


