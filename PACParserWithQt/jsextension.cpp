#include "jsextension.h"



#include <QtNetwork>

JSExtension::JSExtension(QObject *parent) : QObject(parent)
{

}


QJSValue JSExtension::isPlainHostName(QString host){
    return host.indexOf(".") == -1;
}

QJSValue JSExtension::debug( QString str )
{
    qDebug() << str;
    return QJSValue::UndefinedValue;
}


/* String myIpAddress */
QJSValue JSExtension::myIpAddress(  )
{

    foreach( QHostAddress address, QNetworkInterface::allAddresses() ) {
    if ( address != QHostAddress::LocalHost
         && address != QHostAddress::LocalHostIPv6 )
        return QJSValue( address.toString() );
    }

    return QJSValue::UndefinedValue;
}

/* bool isInNet ipaddress, netaddress, netmask */
QJSValue JSExtension::isInNet( QString arg0,QString arg1,QString arg2 )
{
    QHostAddress addr( arg0 );
    QHostAddress netaddr( arg1 );
    QHostAddress netmask( arg2 );

    if ( (netaddr.toIPv4Address() & netmask.toIPv4Address()) == (addr.toIPv4Address() & netmask.toIPv4Address()) )
        return QJSValue( true );

    return QJSValue( false );
}

/* bool shExpMatch url, glob */
QJSValue JSExtension::shExpMatch( QString arg0,QString arg1 )
{

    QRegExp re( arg1, Qt::CaseSensitive, QRegExp::Wildcard );
    return re.exactMatch( arg0);
}

/* string dnsResolve hostname */
QJSValue JSExtension::dnsResolve( QString arg0 )
{

    QHostInfo info = QHostInfo::fromName( arg0 );
    QList<QHostAddress> addresses = info.addresses();
    if ( addresses.isEmpty() )
        return QJSValue::NullValue; // TODO: Should this be undefined or an exception? check other implementations

    return QJSValue( addresses.first().toString() );
}

QJSValue JSExtension::dnsDomainIs(QString host,QString target){
    return host.indexOf(target) != -1; // TODO
}

QJSValue JSExtension::isResolvable(QString host){
    Q_UNUSED(host)
    return true;// TODO
}
