//
// Created by ippan on 20/11/17.
//

#ifndef QTINCLION_RYTHEM_H
#define QTINCLION_RYTHEM_H


#include <QApplication>
#include "Core/ProxyServer.h"

class Rythem : public QApplication {
public:
    Rythem(int &argc, char **argv);

    static quint16 DEFAULT_PORT;

private:
    ProxyServer *server;
    RythemWindow *window;

    static const QString CompanyName;
    static const QString AppName;
    static const QString SETTING_AUTO_LISTEN;
};


#endif //QTINCLION_RYTHEM_H
