//
// Created by ippan on 27/11/17.
//

#ifndef QTINCLION_RULEMANAGER_H
#define QTINCLION_RULEMANAGER_H


#include <QObject>
#include <QTcpSocket>
#include "PipeData.h"
#include "PACParser.h"

class RuleManager : public QObject{
    Q_OBJECT



    Q_DISABLE_COPY(RuleManager)
    RuleManager();
public:
    static RuleManager* instance(){
        static RuleManager * _instance = 0;
        if ( _instance == 0 ) {
            _instance = new RuleManager();
        }
        return _instance;
    }

    /**
     *
     * @return replacement
     */
    QString checkMatch(PipeData* data,bool *needChangeRequest,bool *needChagneResponse,bool *needChangeHost);

    QByteArray getRequestData(QString replacement,PipeData *data);
    QByteArray getResponseData(QString replacement,PipeData *data);
    QTcpSocket getRemoteSocket(QString replacement,PipeData *data);


    QByteArray getLocalContent(QString fullPath);
    QByteArray getRemoteContent(QString url);


    QString DEFAULT_200_HEADER;
    QString DEFAULT_404_HEADER;
    QJSEngine *engine;

private:
    PACParser *pacParser;

};


#endif //QTINCLION_RULEMANAGER_H
