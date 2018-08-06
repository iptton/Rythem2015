#ifndef PACPARSER_H
#define PACPARSER_H

#include <QObject>
#include <QtCore>
#include <QJSEngine>
#include <QJSValue>
#include "jsextension.h"

class PacParser : public QObject{
public:
    PacParser(QObject *parent,const QString& url);

    QString findProxyByURL(const QString& url,const QString& host);

private:
    QJSEngine *engine;

    QString getContent(const QString& url);
};

#endif // PACPARSER_H
