//
// Created by ippan on 20/11/17.
//

#include "Pipe.h"
#include "RuleManager.h"

Pipe::Pipe(qintptr socketHandle) :
    QObject(),
    socketHandle(socketHandle),
localSocket(NULL),
remoteSocket(NULL){

    // TODO 任务保存下来，要考虑复用里面的socket。

    localSocket = new QTcpSocket();
    localSocket->setSocketDescriptor(socketHandle);
    connect(localSocket,&QTcpSocket::readyRead,this,&Pipe::localReadyRead);

    qDebug()<<"======Pipe Handle "<<socketHandle;
}


QTcpSocket* Pipe::getTcpSocket(QHostAddress &address) {
    return new QTcpSocket();
}

void Pipe::localReadyRead() {
    QByteArray byteArray = localSocket->readAll();
//    qDebug()<<"ready to read\n"<<socketHandle<<byteArray;
    bool isRequestOK = false;
    parseReqeust(byteArray,&isRequestOK);
}

void Pipe::parseReqeust(QByteArray &request,bool *isRequestOk) {
    data = new PipeData(request);
    if(!data->requestValid()){
        *isRequestOk = false;
        qDebug()<<"wrong request";
        data->deleteLater();
        return;
    }else{


        qDebug()<<"request ok:"<<data->requestDataToSend;
        QString response="<h1>hello world<h1>";


        QByteArray byteArray = RuleManager::getRule(data);
        if(byteArray.isEmpty()){
            byteArray = QByteArray("HTTP/1.1 200 OK\r\n"
                                           "Connection: Close\r\nContent-Length: ").append(QByteArray::number(response.size())).append("\r\n\r\n").append(response);
        }

        localSocket->write(byteArray);
        localSocket->flush();
        localSocket->waitForBytesWritten(10);
        localSocket->close();

        QSharedPointer<PipeData> data_ptr = QSharedPointer<PipeData>(data);
        emit onPipeCreated(data_ptr);

        QThread *thread = QThread::currentThread();
        QThread::currentThread()->quit();
        connect(thread,&QThread::finished,[=](){
            QThread::currentThread()->deleteLater();
        });
    }
}

void Pipe::parseResponse(QByteArray &byteArray){
    if(!data)return;
    data->parseResponse(byteArray);
}

void Pipe::moveToThread(QThread *thread) {
    QObject::moveToThread(thread);
    if(localSocket){
        localSocket->moveToThread(thread);
    }
    if(remoteSocket){
        remoteSocket->moveToThread(thread);
    }
}


