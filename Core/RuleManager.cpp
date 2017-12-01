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
    QFile file(QCoreApplication::applicationDirPath()+"/../Resources/rule.js");
//    file.open(QIODevice::ReadOnly);


    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
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
    QString str = ret.property("replacement").call().toString();
    qDebug()<<"response = =====:"<<str;
    return str.toUtf8();
}