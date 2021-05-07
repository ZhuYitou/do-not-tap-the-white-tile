#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qpainter>
#include <QTimer>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isRun(false)
{
    ui->setupUi(this);
    pal.setColor(QPalette::Background,Qt::gray);
    setAutoFillBackground(true);
    setPalette(pal);

    this->setGeometry(QRect(300,200,480,1050));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //背景
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(60,225,360,800);

    //生死线
    painter.setPen(Qt::red);
    painter.drawLine(60,1024,420,1024);
    painter.drawLine(60,1025,420,1025);
    painter.drawLine(60,1026,420,1026);

if(!isRun){
    InitMainWindow();
}

if(frameNum==0){
    createRect();
}

if(isClickRight()==2){
    qRects.dequeue();
}

//画块
painter.setPen(Qt::black);
painter.setBrush(Qt::black);
for (int i=0; i<qRects.size(); i++) {
    painter.drawRect(qRects[i]);
}

//挡板
painter.setPen(Qt::gray);
painter.setBrush(Qt::gray);
painter.drawRect(0,0,480,225);

if (isDie()){
    timer->stop();
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    if(isClickWrongFlag){
        painter.drawRect(QRect(60+90*nPosition,qRects.head().top(),90,200));
    }else{
        painter.drawRect(qRects.head());
    }
}

}



void MainWindow::InitMainWindow(){
    isRun=true;
    frameNum=1;
    frameSpeed = 10;//帧速，10ms一帧
    moveSpeed = 4;//移速，一帧动2个长度,须被200整除

    qRects.clear();
    for(int i=0;i<3;i++){
        int position=qrand()%4;
        qRects.enqueue(QRect(60+90*position,425-200*i+moveSpeed,90,200));
    }



    timer=new QTimer(this);//设定定时器
    timer->start(frameSpeed);//设定帧速
    connect(timer,SIGNAL(timeout()),SLOT(MainWindow_update()));



}



void MainWindow::MainWindow_update(){
    frameNum++;
    frameNum = frameNum%(200/moveSpeed);

    rectsDown();

    update();//更新

}



void MainWindow::keyPressEvent(QKeyEvent *event){
     QKeyEvent *key=(QKeyEvent*) event;
     switch(key->key())
   {
    case Qt::Key_C:nPosition=0;
      break;
    case Qt::Key_V:nPosition=1;
      break;
    case Qt::Key_N:nPosition=2;
      break;
    case Qt::Key_M:nPosition=3;
      break;
    default:;
   }
}


void MainWindow::createRect(){
    int position=qrand()%4;
    qRects.enqueue(QRect(60+90*position,25,90,200));

}

int MainWindow::isClickRight(){//未点击返回1，击中返回2，击错返回3
    if(nPosition==-1){
        return 1;
    }else if(!qRects.empty()&&qRects.head().left()==60+90*nPosition){
        nPosition=-1;
        return 2;
    }else{
        isClickWrongFlag=true;
        return 3;
    }
}

bool MainWindow::isDie(){
    if(isClickWrongFlag)
        return true;
    if(!qRects.empty()&&qRects.head().top() > 825)
        return true;
}

void MainWindow::rectsDown(){
    for (int i=0; i<qRects.size(); i++) {
        qRects[i].setRect(qRects[i].left(),qRects[i].top()+moveSpeed,90,200);
    }
}





