#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QListIterator>
#include <QPalette>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void InitMainWindow();
    void keyPressEvent(QKeyEvent *event);

    void createRect();
    void rectsDown();

    int isClickRight();
    bool isDie();

private slots:
     void MainWindow_update();

private:
    Ui::MainWindow *ui;
    QPalette pal;

    QQueue<QRect> qRects;

    QTimer *timer;//定时器
    int frameSpeed = 25;//帧速，25ms一帧
    int moveSpeed = 20;//移速，一帧动20个长度,须被200整除
    int frameNum =0;//第几帧
    int nPosition=-1;//按键位置
    bool isRun;
    bool isClickWrongFlag=false;
};

#endif // MAINWINDOW_H
