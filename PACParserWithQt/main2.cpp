//#include <QCoreApplication>


//#include "pacparser.h"
//#include <QNetworkAccessManager>
//#include <QtNetwork>
//#include <QTimer>

//QString getContent2(const QString& url){

//    QNetworkAccessManager manager;
//    qDebug()<<"url"<<url;
//    QTimer timer;
//    QEventLoop _loop;
//    timer.singleShot(10000,&_loop,SLOT(quit()));//5秒内
//    QNetworkProxyFactory::setUseSystemConfiguration(true);
//    manager.connect(&manager,SIGNAL(finished(QNetworkReply*)),&_loop,SLOT(quit()));
//    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
//    _loop.exec();
//    QString script = QString(reply->readAll());

//    return script;
//}


//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    QString content = getContent2("http://pac.webdefence.global.blackspider.com:8082/proxy.pac");
//    qDebug()<<content;
//    PacParser parser(nullptr,content);

//    qDebug()<<parser.findProxyByURL("http://qq.com","qq.com");
//    qDebug()<<parser.findProxyByURL("http://google.com/","google.com");


//    return a.exec();
//}
