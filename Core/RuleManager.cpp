//
// Created by ippan on 27/11/17.
//

#include "RuleManager.h"
#include <QJSEngine>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



QByteArray RuleManager::getRule(PipeData *data) {
    QJSEngine engine;
    QFile file(QCoreApplication::applicationDirPath()+"/../Resources/rule.js");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    engine.evaluate(file.readAll());
    QFile file2(QCoreApplication::applicationDirPath()+"/../Resources/common.js");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    engine.evaluate(file2.readAll());



    QJSValue ret = engine.evaluate("getMatchRule('"+data->host+"','"+data->path+"')");


    int type = ret.property("type").toInt();
    QString replacement = ret.property("replacement").toString();
    QString customHeaders = ret.property("customHeadres").toString();
    switch(type){
        case 0:// local content replacement

            break;
        case 1:// remote content replacement

            break;


        case 1200:// default 200 hello world
            break;
        case 1404:// default 404 not found
            break;
        case 1504:// default 504 bad gatway
            break;
        case 9999:// Rythem local request

            break;
    }
    return QByteArray();

}

QString RuleManager::DEFAULT_200_HEADER = "HTTP/1.1 200 OK\r\nServer:Rythem2015\r\nContent-Length:%1\r\n\r\n%2";
QString RuleManager::DEFAULT_404_HEADER = "HTTP/1.1 404 NOT FOUND\r\nServer:Rythem2015\r\nContent-Length:%1\r\n\r\n%2";

QByteArray RuleManager::getLocalContent(QString fullPath){
    QByteArray result;



    QFile file(fullPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray body = file.readAll();


        QString length = QString::number(body.length());

        result = QString(RuleManager::DEFAULT_200_HEADER)
                .arg(length)
                .arg(QString(body)).toUtf8();
    }else{
        QByteArray body;
        body.append(QString("file: "+fullPath+" not found"));
        result = QString(DEFAULT_404_HEADER)
                .arg(QString::number(body.length()))
                .arg(QString(body))
                .toUtf8();
    }
    return result;

}


QJSEngine *RuleManager::engine = 0;
bool isEngineInited = false;

QByteArray RuleManager::checkRule(PipeData *data, bool *changeReq, bool *changeRes) {
    if(!isEngineInited){
        isEngineInited = true;
        engine = new QJSEngine();
        QFile file(QCoreApplication::applicationDirPath()+"/../Resources/rule.js");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        engine->evaluate(file.readAll());
        QFile file2(QCoreApplication::applicationDirPath()+"/../Resources/common.js") ;
        file2.open(QIODevice::ReadOnly | QIODevice::Text);
        engine->evaluate(file2.readAll());
    }
    //qDebug()<<ba;


    QJSValue ret = engine->evaluate("getMatchRule('"+data->host+"','"+data->path+"')");
    qDebug()<<"getMatchRule('"+data->host+"','"+data->path+"')";
    int type = ret.property("type").toInt();
    QString replacement = ret.property("replacement").toString();
    QString customHeaders = ret.property("customHeadres").toString();
    qDebug()<<ret.toString()<<type<<replacement;

    *changeRes = true;
    switch(type){
        case 0: {// local content replacement
            return getLocalContent(replacement);

        }
        case 1:{// remote content replacement
            return getRemoteContent(replacement);
        }
        case 1200: {// default 200 hello world
            QString response = "DEFAULT 200 OK....";
            QByteArray byteArray = QByteArray("HTTP/1.1 200 OK\r\n"
                                           "Connection: Close\r\nContent-Length: ").append(
                    QByteArray::number(response.size())).append("\r\n\r\n").append(response);
            return byteArray;
        }
        case 1404:// default 404 not found
            break;
        case 1504:// default 504 bad gatway
            break;
        case 9999:// Rythem local request

            break;
        default:
            *changeRes = false;
            *changeReq = false;
            break;
    }

    QByteArray ba;
    return ba;
}

QByteArray RuleManager::getRemoteContent(QString url) {
    QByteArray ba;
    return ba;
}
