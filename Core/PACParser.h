//
// Created by ippan on 1/12/17.
//

#ifndef QTINCLION_PACPARSER_H
#define QTINCLION_PACPARSER_H


#include <QJSEngine>

class PACParser {
    Q_DISABLE_COPY(PACParser)
public:

    enum PROXY_TYPE{
        DIRECT = 0,
        PROXY = 1,
        INVALID = 9
    };

public:
    explicit PACParser(QString backPACUrl);
    QString findProxyForUrl(QString url,PROXY_TYPE *type=0);


private:
    QString getContentByUrl(QString &url);

private:
    QJSEngine *engine;
    QString backScript;

};


#endif //QTINCLION_PACPARSER_H
