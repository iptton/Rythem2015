//
// Created by ippan on 20/11/17.
//

#include <QCoreApplication>
#include "Pipe.h"
#include "RuleManager.h"

Pipe::Pipe(qintptr socketHandle) :
    QObject(),
    socketHandle(socketHandle),
localSocket(NULL),
remoteSocket(NULL),
data(NULL){

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

void Pipe::parseReqeust(const QByteArray request,bool *isRequestOk) {
    data = new PipeData(request);
    if(!data->requestValid()){
        *isRequestOk = false;
        qDebug()<<"wrong request";
        return;
    }else{


        qDebug()<<"request ok:"<<data->requestDataToSend;
        QString response="<h1>hello world<h1>";


        if(data->isLocalRequest &&
                data->port == 8889){ // Rythem rule page request
            QString basePath = QCoreApplication::applicationDirPath()+"/../Resources/";
            QString fullPath = basePath+data->path;


            emit onPipeCreated(PipeData_ptr(data));
            QByteArray byteArray = RuleManager::getLocalContent(fullPath);
            parseResponse(byteArray);



        }else {

            // TODO RuleChecker
            bool changeReq;
            bool changeRes;
            QByteArray replacementRes = RuleManager::checkRule(data,&changeReq,&changeRes);

            if(!changeRes){
                remoteSocket = new QTcpSocket(this);
                connect(remoteSocket,&QTcpSocket::connected,[=]{
                    emit onPipeCreated(PipeData_ptr(data));

                    remoteSocket->write(data->requestDataToSend);
                    remoteSocket->flush();
                    localSocket->waitForBytesWritten(10);
                });
                connect(remoteSocket,&QTcpSocket::readyRead,[=]{
                    QByteArray byteArray = remoteSocket->readAll();
                    localSocket->write(byteArray);
                    localSocket->waitForBytesWritten(10);
                    localSocket->flush();
                    parseResponse(byteArray);
                });
                connect(remoteSocket,&QTcpSocket::bytesWritten,[=](qint64){
                    //TODO check if all done.
                });
                remoteSocket->connectToHost(data->host,data->port);
            }else{
                emit onPipeCreated(PipeData_ptr(data));
                localSocket->write(replacementRes);
//                localSocket->waitForBytesWritten(10);
                localSocket->flush();
                parseResponse(replacementRes);
            }
        }
    }
}

void Pipe::parseResponse(QByteArray byteArray){
    if(!data)return;


    bool isResponseCompleted = data->parseResponse(&byteArray);
    if(isResponseCompleted){
//        localSocket->close();
//        remoteSocket->close();
    }
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


