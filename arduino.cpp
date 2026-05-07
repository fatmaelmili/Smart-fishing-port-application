#include "arduino.h"
#include <QRegularExpression>
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    arduino_is_available = false;
    arduino_port_name = "";

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {

        qDebug() << "Port name:" << serial_port_info.portName();
        qDebug() << "Description:" << serial_port_info.description();
        qDebug() << "Manufacturer:" << serial_port_info.manufacturer();
        qDebug() << "Has vendor id:" << serial_port_info.hasVendorIdentifier();
        qDebug() << "Has product id:" << serial_port_info.hasProductIdentifier();

        if (serial_port_info.hasVendorIdentifier())
            qDebug() << "Vendor ID:" << serial_port_info.vendorIdentifier();

        if (serial_port_info.hasProductIdentifier())
            qDebug() << "Product ID:" << serial_port_info.productIdentifier();

        qDebug() << "---------------------";

        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {

            quint16 vendorId = serial_port_info.vendorIdentifier();
            quint16 productId = serial_port_info.productIdentifier();

            if ((vendorId == arduino_uno_vendor_id && productId == arduino_uno_product_id) ||
                (vendorId == ch340_vendor_id && productId == ch340_product_id))
            {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break;
            }
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);

        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }

    return -1;
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;


}


QByteArray Arduino::read_from_arduino()
{
    if (serial->isReadable()) {
        data = serial->readAll(); // récupérer les données reçues
        return data;
    }

    return QByteArray();
}


void Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}


//arduino dhia
int Arduino::readDistance()
{
    if (serial->canReadLine()) {

        QByteArray line = serial->readLine().trimmed();

        qDebug() << "Arduino line:" << line;

        QRegularExpression regex("Distance: (\\d+)");
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch()) {
            return match.captured(1).toInt();
        }
    }

    return -1; // invalid reading
}
void Arduino::sendBuzzerCommand(int status)
{
    if (serial->isWritable()) {

        if (status == 1) {
            serial->write("1");
            qDebug() << "Sent buzzer ON";
        }
        else {
            serial->write("0");
            qDebug() << "Sent buzzer OFF";
        }
    }
}





