#include "universal.h"

universal::universal()
{

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

QByteArray ReadFromFile(QString path)
{
    QFile file(path);  // 文件地址
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return nullptr;
    }
    QByteArray data;
    while(!file.atEnd()){
        bool ok;
        QByteArray array = file.readAll();
        for(int i = 0; i < array.size(); i += 3){
            QString data_str;
            data_str.push_back(array.at(i));
            data_str.push_back(array.at(i + 1));
            data.push_back(static_cast<char>(data_str.toInt(&ok, 16)));
        }

    }
    return data;
}

QVector<QString> DataToString(QByteArray data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        str.push_back(QString::number(data_, base));
//        if(data != ' '){
//        }
//        else str.push_back(data);
    }
    return str;
}
QVector<QString> DataToString(QVector<double> data, int precision)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, 'f', precision);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(char data, int base)
{
    QVector<QString> str;
    QString str_ = QString::number(data, base);
//    if(str_.size() < 2)
//        str_.prepend('0');
    str.push_back(str_);
    return str;
}
QVector<QString> DataToString(QVector<char> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(QVector<uint8_t> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(QVector<uint16_t> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(QVector<int16_t> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(QVector<uint32_t> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(QVector<int32_t> data, int base)
{
    QVector<QString> str;
    for(auto data_ : data){
        QString str_ = QString::number(data_, base);
//        if(str_.size() < 2)
//            str_.prepend('0');
        str.push_back(str_);
    }
    return str;
}
QVector<QString> DataToString(uint8_t data, int base)
{
    QVector<QString> str;
    QString str_ = QString::number(data, base);
//    if(str_.size() < 2)
//        str_.prepend('0');
    str.push_back(str_);
    return str;
}
bool IsValid(char data)
{
    return ((data != static_cast<char>(0xFF)) && (data != static_cast<char>(0xFE))) ? true : false;
}

bool IsValid(uint16_t data)
{
    return ((data != static_cast<uint16_t>(0xFFFF)) && (data != static_cast<uint16_t>(0xFFFE))) ? true : false;
}

bool IsValid(QString data)
{
  return ((data != "0xFF") && (data != "0xFE") && (data != "255") && (data != "254")) ? true : false;
}

bool IsValid(int16_t data)
{
    return ((data != static_cast<int16_t>(0xFFFF)) && (data != static_cast<int16_t>(0xFFFE))) ? true : false;
}
