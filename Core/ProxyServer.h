//
// Created by ippan on 17/11/17.
//

#ifndef QTINCLION_PROXYSERVER_H
#define QTINCLION_PROXYSERVER_H

#include <QTcpServer>
#include "Pipe.h"

class ProxyServer : public QTcpServer{
    Q_OBJECT
public:
    explicit ProxyServer(QObject *parent);
    ~ProxyServer();
signals:
    void onPipeCreated(Pipe* pipe,PipeData_ptr);

protected:
    void incomingConnection(qintptr handle) override ;

};


#endif //QTINCLION_PROXYSERVER_H
