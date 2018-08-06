//
// Created by ippan on 20/11/17.
//

#ifndef QTINCLION_PIPE_H
#define QTINCLION_PIPE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThreadPool>
#include "PipeData.h"

/***
 *
 * Pipe ，管道。
 * 每个管道负责一个代理请求
 *
 *
 * 管道需管理 socket （可能为SSL，也可能为非SSL)
 *
 */

class Pipe : public QObject {
    Q_OBJECT
public:
    Pipe(qintptr socketHandle);
    static QTcpSocket* getTcpSocket(QHostAddress &address);

    qintptr socketHandle;
    void moveToThread(QThread *thread);


signals:
    void onPipeCreated(PipeData_ptr);
    void onPipeComplete(PipeData_ptr);


protected slots:
    void localReadyRead();

    void parseReqeust(const QByteArray,bool *isRequestOk);
    void parseResponse(const QByteArray);

private:
    QTcpSocket *localSocket;
    QTcpSocket *remoteSocket; // 有可能为 QSslSocket,是否有需要单独一个变量？

    PipeData *data;
};


#endif //QTINCLION_PIPE_H
