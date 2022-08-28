#ifndef UNIVERSAL_H
#define UNIVERSAL_H
#include <QByteArray>
#include <QString>
#include <QFile>

extern QByteArray dataToHex(const QByteArray &data, const QString &separator = " ", const QString &prefix = "");
extern QByteArray ReadFromFile(QString path);
extern QVector<QString> DataToString(QByteArray data, int base);
extern QVector<QString> DataToString(QVector<double> data, int precision);
extern QVector<QString> DataToString(char data, int base);
extern QVector<QString> DataToString(QVector<uint8_t> data, int precision);
extern QVector<QString> DataToString(QVector<char> data, int base);
extern QVector<QString> DataToString(QVector<uint16_t> data, int base);
extern QVector<QString> DataToString(QVector<int16_t> data, int base);
extern QVector<QString> DataToString(QVector<uint32_t> data, int base);
extern QVector<QString> DataToString(QVector<int32_t> data, int base);
extern QVector<QString> DataToString(uint8_t data, int base);

extern bool IsValid(char data);
extern bool IsValid(uint16_t data);
extern bool IsValid(QString data);
extern bool IsValid(int16_t data);

class universal
{
public:
  universal();
};

#endif // UNIVERSAL_H
