//
// Created by ippan on 21/11/17.
//

#include "PipeData.h"

PipeData::PipeData(QByteArray &requestInitialData) {
    requestDataOri.append(requestInitialData);
    parseRequest();

    qDebug()<<"PipeData CREATED=========="<<host;
}

bool PipeData::requestValid() {
    return _isRequestOk;
}

void PipeData::parseRequest() {

    // 检测请求头是否已经完整
    int deviderSize=4;
    int deviderIndex = requestDataOri.indexOf("\r\n\r\n");
    if(deviderIndex==-1){
        deviderSize = 2;
        deviderIndex =requestDataOri.indexOf("\n\n");
    }
    if(deviderIndex == -1){// no devider
        _isRequestOk = false;
        return;
    }

    // 解析 header
    QByteArray headerData = requestDataOri.left(deviderIndex);
    _isRequestOk = parseHeader(headerData); // TODO 如果此时请求不合法，则此请求都应该直接断掉，isRequestOK 应该分两种情况，非法 和 未完整
    if(!_isRequestOk)return;

    // 头已完整，判断 body 是否完整 TODO 是否仅当存在 Content-legnth 才需要判断?
    qulonglong currentBodySize = requestDataOri.size() - deviderIndex - deviderSize;
    qulonglong contentLength = currentBodySize;
    if(requestHeaders.contains("CONTENT-LENGTH")){
        bool isDataOk = false;
        contentLength = requestHeaders["CONTENT-LENGTH"].toULongLong(&isDataOk);
//        if(!isDataOk){
//            contentLength = currentBodySize;
//        }
    }
    requestBodyRemain = contentLength - currentBodySize;

    requestBody = requestDataOri.right(currentBodySize);
    requestDataToSend.append(sigsToSend).append(requestHeaderByteArray).append(requestBody);

    _isRequestOk = true;
}


QStringList PipeData::_acceptedMethods = {
        "OPTION",
        "GET",
        "POST",
        "HEAD",
        "PUT",
        "DELETE",
        "TRACE",
        "CONNECT"
};// see http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html

bool PipeData::parseHeader(QByteArray headerData) {

    // 为方便，将所有 \r\n 换为 \n
    QByteArray tmp = headerData;
    tmp.replace("\r\n","\n");
    QList<QByteArray> headerLines = tmp.split('\n');
    if(headerLines.length() == 0){
        return false;
    }

    // 解析 "GET / HTTP/1.1" 或 "Connect http://xxxx:443 "
    QByteArray firstLine = headerLines.takeAt(0);
    firstLine = firstLine.simplified();
    QList<QByteArray> sigs = firstLine.split(' ');
    if(sigs.length()<2){// 有可能为 "CONNECT github.com:443"
        return false;
    }
    method = sigs[0].toUpper();
    fullUrl = sigs[1];
    if(sigs.length()>2){
        httpVersion = sigs[2];
    }

    // 检查 Method
    if(!_acceptedMethods.contains(method,Qt::CaseInsensitive)){
        return false;
    }

    path = "/";
    port = 80;

    QString withoutProtocol = fullUrl;
    int indexOfHost = fullUrl.indexOf("://");
    if(indexOfHost!=-1){
        withoutProtocol = fullUrl.mid(indexOfHost+3);
    }

    if(indexOfHost==-1){
        // request after CONNECT tunnel
        path = fullUrl;
    }
    QString hostAndPort = withoutProtocol;
    int indexOfPath = withoutProtocol.indexOf("/");
    if(indexOfPath!=-1){
        hostAndPort = withoutProtocol.left(indexOfPath);
        path = withoutProtocol.mid(indexOfPath);
    }
    int indexOfPort = hostAndPort.indexOf(":");
    host = hostAndPort;
    realConnectHost = host;
    if(indexOfPort!=-1){
        host = hostAndPort.left(indexOfPort);
        port = hostAndPort.mid(indexOfPort+1).toInt();
    }
    if(method == "CONNECT"){
        isConnectTunnel = true;
        fullUrl.prepend("http://");
    }else if(host == hostAndPort){
        host = "";
    }

    //qDebug()<<"host="<<host<<port;

    sigsToSend = method+" "+path+" "+httpVersion+"\r\n";
    //qDebug()<<"sigs:"<<sigsToSend;



    requestHeaderByteArray = headerLines.join("\r\n");
    //qDebug()<<"headers:"<<requestHeaderByteArray;


    while(!headerLines.empty()){
        QByteArray line = headerLines.takeAt(0);
        QList<QByteArray> tmp = line.split(':');
        requestHeaders[tmp[0].trimmed().toUpper()]=tmp[1].trimmed();
    }
    if(requestHeaders.contains("HOST")){
        host = requestHeaders["HOST"];
    }

    return true;
}

void PipeData::parseResponse(QByteArray &array) {

}
