//
// Created by ippan on 20/11/17.
//

#include <GUI/RythemWindow.h>
#include "Rythem.h"

quint16 Rythem::DEFAULT_PORT = 8889;

const QString Rythem::CompanyName = "iptton";
const QString Rythem::AppName = "Rythem2015";

const QString Rythem::SETTING_AUTO_LISTEN = "AUTO_LISTEN";

Rythem::Rythem(int &argc, char **argv) : QApplication(argc, argv){

    // metaType regist
    qRegisterMetaType<PipeData_ptr>("PipeData_ptr");

    server = new ProxyServer(this);
    window = new RythemWindow(server);

    connect(server,&ProxyServer::onPipeCreated,window,&RythemWindow::onPipeCreated);


    // check settings whether setting auto listening
    QSettings settings(CompanyName,AppName);
    bool autoListen = settings.value(SETTING_AUTO_LISTEN,false).toBool();
    if(autoListen){
        bool listened = server->listen(QHostAddress::Any,DEFAULT_PORT);
        if(listened){
            qDebug()<<"listening...";
        }else{
            qDebug()<<"fail to listen";
        }
    }



    window->show();
}
