//
// Created by ippan on 1/12/17.
//

#ifndef QTINCLION_PACEXTOBJECT_H
#define QTINCLION_PACEXTOBJECT_H


#include <QObject>
#include <QHostInfo>
#include <QJSValue>
#include <QNetworkInterface>

class PACExtObject : public QObject {
    Q_OBJECT
public:
    PACExtObject(QObject *parent = 0):QObject(parent){

    }

    Q_INVOKABLE QJSValue dnsResolve(QString name){
        QHostInfo info = QHostInfo::fromName( name );
        QList<QHostAddress> addresses = info.addresses();
        if ( addresses.isEmpty() )
            return QJSValue::NullValue; // TODO: Should this be undefined or an exception? check other implementations

        return addresses.first().toString();
    }

    Q_INVOKABLE QJSValue debug(QString str){
        qDebug()<<str;
        return QJSValue::UndefinedValue;
    }

    Q_INVOKABLE QJSValue myIpAddress(){// myIpAddress  有多个值 ，如何取？
        QString result="";
        foreach( QHostAddress address, QNetworkInterface::allAddresses() ) {
                if ( address != QHostAddress::LocalHost
                     && address != QHostAddress::LocalHostIPv6 )
                    // how to remove fe80::1%lo0 ?
//                    qDebug()<<address;
                    result =  address.toString();
        }
        return result;
//        return QJSValue::UndefinedValue;
    }

    Q_INVOKABLE QJSValue isInNet(QString _addr,QString _netAddress,QString _netMask){

        QHostAddress addr( _addr );
        QHostAddress netaddr( _netAddress );
        QHostAddress netmask( _netMask);

        if ( (netaddr.toIPv4Address() & netmask.toIPv4Address()) == (addr.toIPv4Address() & netmask.toIPv4Address()) )
            return true;

        return false;
    }

    Q_INVOKABLE QJSValue shExpMatch(QString src,QString pattern){
//        qDebug()<<src<<pattern;
        QRegExp re( pattern, Qt::CaseInsensitive, QRegExp::Wildcard );
        return re.exactMatch( src);
    }

};


#endif //QTINCLION_PACEXTOBJECT_H
