//
// Created by ippan on 30/11/17.
//

#include "RythemWindow.h"
#include "ui_mainwindow.h"


RythemWindow::RythemWindow(ProxyServer* _server, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(new QSettings("iptton","Rythem2015")),
    server(_server){

    ui->setupUi(this);

    connect(ui->mainToolBar,&QToolBar::actionTriggered,this,&RythemWindow::onActionTriggered);
}

void RythemWindow::onActionTriggered(QAction *action) {
    QString name = action->objectName();
    if(name == "actionSetting"){
        qDebug()<<"setting..";
    }else if(name=="ActionCapture"){
        if(action->isChecked()) {
            server->listen(QHostAddress("127.0.0.1"), 8889);
        }else{
            server->close();
        }
    }

    qDebug()<<name;
    qDebug()<<"idealThreadCount="<<QThread::idealThreadCount();

}


void RythemWindow::onPipeCreated(Pipe *pipe,PipeData_ptr data) {
    qDebug()<<"Got a pipe "<<data->fullUrl<<QThread::currentThreadId();
}