//
// Created by ippan on 27/11/17.
//

#include "RuleManager.h"
#include <QJSEngine>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QByteArray RuleManager::getRule(PipeData *) {
    QJSEngine engine;
    QFile file(QCoreApplication::applicationDirPath()+"/Resources/rule.js");
//    file.open(QIODevice::ReadOnly);


    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug()<<"fail";
    }else{
        qDebug()<<"success";
    }

    QTextStream ts(&file);
    QByteArray ba;
    ba.append(ts.readAll());
    engine.evaluate(ba);
    qDebug()<<ba;


    QJSValue ret = engine.evaluate("getMatchRule('qq.com','/')");
    QString str = ret.toString();
    return str.toUtf8();
}