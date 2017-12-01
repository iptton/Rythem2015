//
// Created by ippan on 1/12/17.
//

#ifndef QTINCLION_RULE_H
#define QTINCLION_RULE_H


class Rule {
public:
    typedef enum RuleType{
        ReplaceContentLocal,
        ReplaceContentRemote,
        ReplaceHost,
        Block
    } RuleType;
};


#endif //QTINCLION_RULE_H
