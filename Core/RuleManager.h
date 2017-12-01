//
// Created by ippan on 27/11/17.
//

#ifndef QTINCLION_RULEMANAGER_H
#define QTINCLION_RULEMANAGER_H


#include <QObject>
#include "PipeData.h"
#include "PACParser.h"

class RuleManager : public QObject{
    Q_OBJECT
public:
    static QByteArray getRule(PipeData*);

private:
    PACParser *pacParser;
};


#endif //QTINCLION_RULEMANAGER_H
