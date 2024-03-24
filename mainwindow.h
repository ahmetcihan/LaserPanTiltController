#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QProcess>

typedef char s8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void EOL(char *base_array, u8 i);
    void serial_port_setup(void);
    u32 crc_chk(u8* data, u8 length);

    QSerialPort serial;
    QTimer *_100_msec_timer;
    QTimer *read_timer;


public slots:
    void serial_request_sender(void);
    void serial_response_handler(void);

    void send_max_speed_tilt(void);
    void send_max_speed_pan(void);

    void send_pan_left(void);
    void send_pan_right(void);
    void send_pan_stop(void);
    void send_tilt_up(void);
    void send_tilt_down(void);
    void send_tilt_stop(void);

    void pos_pan_left(void);
    void pos_pan_right(void);
    void pos_tilt_up(void);
    void pos_tilt_down(void);

    void toggle_relay(void);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
