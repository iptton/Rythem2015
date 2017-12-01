//
// Created by ippan on 21/11/17.
//

#ifndef QTINCLION_PIPEDATA_H
#define QTINCLION_PIPEDATA_H


#include <QObject>
#include <QMap>
#include <QVector>
#include <QDebug>

class PipeData : public QObject {

    Q_OBJECT
    Q_DISABLE_COPY(PipeData)

public:
    PipeData(QByteArray& requestInitialData);



    bool requestValid();

private:
    bool _isRequestOk = true;

    static QStringList _acceptedMethods;

    void parseRequest();
    bool parseHeader(QByteArray array);
    bool appendRequestData(QByteArray);
    bool appendResponseData(QByteArray);


public:
    QString method;
    QString httpVersion;
    QString path;
    QString fullUrl;
    int port;
    QString host;
    QString realConnectHost;

    bool isLocalRequest;

    QByteArray requestDataOri;    // 请求侧原始数据
    qulonglong requestBodyRemain = 0;



    QByteArray requestDataToSend; // 处理过后的请求数据

    QMap<QString,QString> requestHeaders;
    QByteArray requestBody;
    QByteArray requestHeaderByteArray;
    QMap<QString,QString> responseHeaders;

    bool isConnectTunnel;
    QString sigsToSend;

    void parseResponse(QByteArray &array);
};


typedef  QSharedPointer<PipeData> PipeData_ptr;

#endif //QTINCLION_PIPEDATA_H
