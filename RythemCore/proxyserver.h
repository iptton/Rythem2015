#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QSslSocket>

class ProxyServer:QTcpServer{
public:
    ProxyServer();

    virtual void incomingConnection(qintptr handle);

};

#endif // PROXYSERVER_H
