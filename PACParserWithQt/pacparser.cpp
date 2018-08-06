#include "pacparser.h"

#include <QMetaObject>
#include <QtNetwork>

PacParser::PacParser(QObject *parent,const QString& url):
    QObject(parent),
    engine(new QJSEngine(this)){

    QString contentOfScript = getContent(url);
    engine->evaluate(contentOfScript);
    JSExtension extension(this);
    QJSValue extValue = engine->newQObject(&extension);


    const QMetaObject *metaobj = extension.metaObject();
    int count = metaobj->methodCount();
    for(int i=0;i<count;++i){
        QMetaMethod method = metaobj->method(i);
        if(method.methodType() == QMetaMethod::Method){
            QString name = method.name();
            engine->globalObject().setProperty(name,extValue.property(name));
        }
    }

}

QString PacParser::findProxyByURL(const QString& url,const QString& host){

    QJSValue global = engine->globalObject();
    QJSValue fun = global.property("FindProxyForURL");
    if ( !fun.isCallable() ) {
        return QString("DIRECT");
    }

    QJSValueList args;
    args << engine->toScriptValue( url ) << engine->toScriptValue( host );
    QJSValue val = fun.call( args );

    return val.toString();
}
QString PacParser::getContent(const QString& url){

    QNetworkAccessManager manager;
    qDebug()<<"url"<<url;
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
