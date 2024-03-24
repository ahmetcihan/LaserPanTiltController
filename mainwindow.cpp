#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_port_setup();

    _100_msec_timer = new QTimer(this);
    _100_msec_timer->setInterval(100);
    //_100_msec_timer->start();
    connect(_100_msec_timer, SIGNAL(timeout()),this,SLOT(serial_request_sender()));

    read_timer = new QTimer(this);
    read_timer->setInterval(50);
    read_timer->start();
    connect(read_timer, SIGNAL(timeout()),this,SLOT(serial_response_handler()));

    connect(ui->pushButton_send_pan_left, SIGNAL(clicked()),this,SLOT(send_pan_left()));
    connect(ui->pushButton_send_pan_right, SIGNAL(clicked()),this,SLOT(send_pan_right()));
    connect(ui->pushButton_send_pan_stop, SIGNAL(clicked()),this,SLOT(send_pan_stop()));
    connect(ui->pushButton_send_tilt_up, SIGNAL(clicked()),this,SLOT(send_tilt_up()));
    connect(ui->pushButton_send_tilt_down, SIGNAL(clicked()),this,SLOT(send_tilt_down()));
    connect(ui->pushButton_send_tilt_stop, SIGNAL(clicked()),this,SLOT(send_tilt_stop()));

    connect(ui->pushButton_pos_pan_left, SIGNAL(clicked()),this,SLOT(pos_pan_left()));
    connect(ui->pushButton_pos_pan_right, SIGNAL(clicked()),this,SLOT(pos_pan_right()));
    connect(ui->pushButton_pos_pan_stop, SIGNAL(clicked()),this,SLOT(send_pan_stop()));
    connect(ui->pushButton_pos_tilt_up, SIGNAL(clicked()),this,SLOT(pos_tilt_up()));
    connect(ui->pushButton_pos_tilt_down, SIGNAL(clicked()),this,SLOT(pos_tilt_down()));
    connect(ui->pushButton_pos_tilt_stop, SIGNAL(clicked()),this,SLOT(send_tilt_stop()));

    connect(ui->pushButton_send_max_speed_pan, SIGNAL(clicked()),this,SLOT(send_max_speed_pan()));
    connect(ui->pushButton_send_max_speed_tilt, SIGNAL(clicked()),this,SLOT(send_max_speed_tilt()));

    connect(ui->pushButton_toggle_relay, SIGNAL(clicked()),this,SLOT(toggle_relay()));

    ui->pushButton_send_pan_left->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_left.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_send_pan_right->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_right.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_send_tilt_up->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_up.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_send_tilt_down->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_down.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_pos_pan_left->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_left.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_pos_pan_right->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_right.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_pos_tilt_up->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_up.jpg);"
                                                "border-width: 0px ;");
    ui->pushButton_pos_tilt_down->setStyleSheet("min-width: 80px; min-height: 80px;"
                                                "border-image: url(:sarı_down.jpg);"
                                                "border-width: 0px ;");

}
void MainWindow::send_pan_left(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'R';
    data[1] = 'U';
    data[2] = 'N';
    data[3] = 'X';
    data[4] = '0';
    data[5] = ((ui->spinBox_speed_pan->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_speed_pan->value() / (256)) % 256);
    data[7] = ((ui->spinBox_speed_pan->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_pan_right(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'R';
    data[1] = 'U';
    data[2] = 'N';
    data[3] = 'X';
    data[4] = '1';
    data[5] = ((ui->spinBox_speed_pan->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_speed_pan->value() / (256)) % 256);
    data[7] = ((ui->spinBox_speed_pan->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_pan_stop(void){
    QByteArray data;
    data.resize(6);

    data[0] = 'D';
    data[1] = 'U';
    data[2] = 'R';
    data[3] = 'X';
    EOL(data.data(),4);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_tilt_up(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'R';
    data[1] = 'U';
    data[2] = 'N';
    data[3] = 'Z';
    data[4] = '0';
    data[5] = ((ui->spinBox_speed_tilt->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_speed_tilt->value() / (256)) % 256);
    data[7] = ((ui->spinBox_speed_tilt->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_tilt_down(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'R';
    data[1] = 'U';
    data[2] = 'N';
    data[3] = 'Z';
    data[4] = '1';
    data[5] = ((ui->spinBox_speed_tilt->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_speed_tilt->value() / (256)) % 256);
    data[7] = ((ui->spinBox_speed_tilt->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_tilt_stop(void){
    QByteArray data;
    data.resize(6);

    data[0] = 'D';
    data[1] = 'U';
    data[2] = 'R';
    data[3] = 'Z';
    EOL(data.data(),4);

    serial.write(data);

    qDebug(__FUNCTION__);
}

void MainWindow::pos_pan_left(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'P';
    data[1] = 'O';
    data[2] = 'S';
    data[3] = 'X';
    data[4] = '0';
    data[5] = ((ui->spinBox_pos_pan->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_pos_pan->value() / (256)) % 256);
    data[7] = ((ui->spinBox_pos_pan->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::pos_pan_right(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'P';
    data[1] = 'O';
    data[2] = 'S';
    data[3] = 'X';
    data[4] = '1';
    data[5] = ((ui->spinBox_pos_pan->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_pos_pan->value() / (256)) % 256);
    data[7] = ((ui->spinBox_pos_pan->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::pos_tilt_up(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'P';
    data[1] = 'O';
    data[2] = 'S';
    data[3] = 'Z';
    data[4] = '0';
    data[5] = ((ui->spinBox_pos_tilt->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_pos_tilt->value() / (256)) % 256);
    data[7] = ((ui->spinBox_pos_tilt->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::pos_tilt_down(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'P';
    data[1] = 'O';
    data[2] = 'S';
    data[3] = 'Z';
    data[4] = '1';
    data[5] = ((ui->spinBox_pos_tilt->value() / (256*256)) % 256);
    data[6] = ((ui->spinBox_pos_tilt->value() / (256)) % 256);
    data[7] = ((ui->spinBox_pos_tilt->value()) % 256);
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}

void MainWindow::send_max_speed_tilt(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'S';
    data[1] = 'P';
    data[2] = 'D';
    data[3] = 'Z';
    data[4] = 'Z';
    data[5] = 0;
    data[6] = 0;
    data[7] = ui->spinBox_max_speed_tilt->value();
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}
void MainWindow::send_max_speed_pan(void){
    QByteArray data;
    data.resize(10);

    data[0] = 'S';
    data[1] = 'P';
    data[2] = 'D';
    data[3] = 'X';
    data[4] = 'X';
    data[5] = 0;
    data[6] = 0;
    data[7] = ui->spinBox_max_speed_pan->value();
    EOL(data.data(),8);

    serial.write(data);

    qDebug(__FUNCTION__);
}

void MainWindow::toggle_relay(void){
    QByteArray data;
    data.resize(7);

    data[0] = 'R';
    data[1] = 'E';
    data[2] = 'L';
    data[3] = 'A';
    data[4] = 'Y';
    EOL(data.data(),5);

    serial.write(data);

    qDebug(__FUNCTION__);
}


MainWindow::~MainWindow()
{
    delete ui;
}
