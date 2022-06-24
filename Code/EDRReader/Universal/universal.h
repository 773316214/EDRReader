#ifndef UNIVERSAL_H
#define UNIVERSAL_H
#include <QByteArray>
#include <QString>
#include <QFile>

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
extern bool IsValid(QString data);

class universal
{
public:
  universal();
};

#endif // UNIVERSAL_H
