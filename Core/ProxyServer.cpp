//
// Created by ippan on 17/11/17.
//

#include "ProxyServer.h"
#include "Pipe.h"
#include "PACParser.h"

ProxyServer::ProxyServer(QObject *parent) : QTcpServer(parent) {
}

ProxyServer::~ProxyServer() {

}

void ProxyServer::incomingConnection(qintptr handle) {
    QTcpServer::incomingConnection(handle);
    qDebug()<<"======incomming "<<handle<<QThread::currentThreadId();

    QThread *thread = new QThread();
    Pipe *pipe = new Pipe(handle);
    pipe->moveToThread(thread);
    connect(
            pipe, &Pipe::onPipeCreated,
            [=]( PipeData_ptr data ) {
                emit onPipeCreated(pipe,data);
                qDebug()<<"======onPipeCreted..."<<QThread::currentThreadId();
            }
    );
    thread->start();

}