#include "mainwindow.h"

u32 MainWindow::crc_chk(u8* data, u8 length){
    int j;
    u32 reg_crc=0xFFFF;

    while( length-- ) {
        reg_crc^= *data++;
        for (j=0; j<8; j++ ) {
            if( reg_crc & 0x01 ) {
                reg_crc = (reg_crc >> 1)^0xA001;
            }
            else {
                reg_crc = (reg_crc>>1);
            }
        }
    }
    return reg_crc;
}
void MainWindow::serial_response_handler(void){
    u32 fcrc;
    u8 crc_low,crc_high;
    QByteArray data_array;
    data_array.resize(25);

    read_timer->stop();
    data_array = serial.readAll();

    if((data_array[0] == 'A') && (data_array[1] == 'N') && (data_array[2] == 'S')){
        fcrc = crc_chk((u8*)data_array.data(),23);
        crc_high = (fcrc)%256;
        crc_low = (fcrc)/256;
        if((crc_high == (u8)data_array[23])&&(crc_low == (u8)data_array[24])){
            qDebug("OK");
        }
    }
}
void MainWindow::EOL(char *base_array, u8 i){
    base_array[i] 	= 0x0D;
    base_array[i+1] = 0x0A;
}
void MainWindow::serial_request_sender(void){
    QByteArray data;
    data.resize(16);

    data[0] = 'C';
    data[1] = 'O';
    data[2] = 'N';
    data[3] = 'V';
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;

    data[8] = 48;
    data[9] = 48;

    data[10] = 0;
    data[11] = 0;
    data[12] = 0;
    data[13] = 0;

    EOL(data.data(),14);

    serial.write(data);
    read_timer->start();

    qDebug() << "sending";
}
void MainWindow::serial_port_setup(void){
    serial.setPortName("ttyUSB0");
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.setStopBits(QSerialPort::TwoStop);
    serial.open(QIODevice::ReadWrite);

    qDebug() << QString("Serial port status is %1").arg(serial.isOpen());

}

