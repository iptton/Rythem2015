#ifndef JSEXTENSION_H
#define JSEXTENSION_H

#include <QtCore>
#include <QObject>
#include <QJSValue>

class JSExtension : public QObject
{
    Q_OBJECT
public:
    explicit JSExtension(QObject *parent = nullptr);
    Q_INVOKABLE QJSValue debug( QString str );

    /* String myIpAddress */
    Q_INVOKABLE QJSValue myIpAddress(  );

    /* bool isInNet ipaddress, netaddress, netmask */
    Q_INVOKABLE QJSValue isInNet( QString arg0,QString arg1,QString arg2 );

    /* bool shExpMatch url, glob */
    Q_INVOKABLE QJSValue shExpMatch( QString arg0,QString arg1 );

    /* string dnsResolve hostname */
    Q_INVOKABLE QJSValue dnsResolve(QString arg0  );

    Q_INVOKABLE QJSValue isPlainHostName(QString host);

    Q_INVOKABLE QJSValue dnsDomainIs(QString host,QString target);
    Q_INVOKABLE QJSValue isResolvable(QString host);
};

#endif // JSEXTENSION_H
