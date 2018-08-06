#include <QCoreApplication>


#include <stdlib.h>
#include <QtCore>
#include <QtNetwork>

#include "pacparser.h"
#include "proxyserver.h"

using namespace std;
bool test();

void testPAC(){

    qDebug()<<"helo world!======";
    QString content = getContent("http://pac.webdefence.global.blackspider.com:8082/proxy.pac");
    //qDebug()<<content;
    PacParser parser(nullptr,content);

    qDebug()<<parser.findProxyByURL("http://qq.com","qq.com");
    qDebug()<<parser.findProxyByURL("http://google.com/","google.com");
}

void testServer(){
    ProxyServer server();
    server.listen();
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testPAC();
    testServer();


    return a.exec();
}



void privileged_server(){

}

void unprivileged_client(){

}

