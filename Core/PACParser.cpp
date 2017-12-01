//
// Created by ippan on 1/12/17.
//

#include <QUrl>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkProxyFactory>
#include <QNetworkReply>
#include <QHostInfo>
#include "PACParser.h"
#include "PACExtObject.h"


QString PACParser::getContentByUrl(QString &url) {
    qDebug()<<"url"<<url;
    if(!QUrl(url).isValid()){
        return "";
    }

    QNetworkAccessManager manager;
    QTimer timer;
    QEventLoop _loop;
    timer.singleShot(10000,&_loop,SLOT(quit()));//5秒内
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    manager.connect(&manager,SIGNAL(finished(QNetworkReply*)),&_loop,SLOT(quit()));
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
    _loop.exec();
    QString script = QString(reply->readAll());
    return script;
}

PACParser::PACParser(QString backPACUrl) {
    engine = new QJSEngine();


    // inject all script needed to pac parser into object
    QJSValue extObj = engine->newQObject(new PACExtObject());
    QStringList initFunctions = {"dnsResolve","isInNet","shExpMatch","myIpAddress","debug"};
    for(int i=0;i<initFunctions.size();++i){
        qDebug()<<initFunctions[i];
        engine->globalObject().setProperty(initFunctions[i],extObj.property(initFunctions[i]));
    }

    backScript = getContentByUrl(backPACUrl);
    engine->evaluate(backScript);

    // 去掉所有注释，通常注释里含有非法字符...
//    QRegExp reg1("/\\*[^\\*/]*\\*/");// /* */
//    QRegExp reg2("//[^\r\n]*\r\n");  //  //
//    qDebug()<<reg2.pattern()<<reg2.isValid();
//    backScript = backScript.replace(reg1,"");
//    backScript = backScript.replace(reg2,"");
}

QString PACParser::findProxyForUrl(QString url,PROXY_TYPE *type ) {
    QUrl theUrl(url);
//    qDebug()<<theUrl.host();

    QString result = engine->evaluate(";debug(myIpAddress());FindProxyForURL('"+url+"','"+theUrl.host()+"');").toString();
    if(result == "DIRECT"){
        if(type) *type = DIRECT;
        return "";
    } else if(result.startsWith("PROXY ")){ // TODO use const string
        if(type) *type = PROXY;
        return result.mid(5).trimmed();// TODO remove magic number
    }

    if(type)*type = INVALID;
    return "";
}

