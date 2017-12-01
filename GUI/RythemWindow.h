//
// Created by ippan on 30/11/17.
//

#ifndef QTINCLION_RYTHEMWINDOW_H
#define QTINCLION_RYTHEMWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <Core/Pipe.h>
#include <QSettings>
#include <Core/ProxyServer.h>

namespace Ui{
    class MainWindow;
};

class RythemWindow : public QMainWindow{
    Q_OBJECT


public:
    explicit RythemWindow(ProxyServer *_Server,QWidget *parent=0);

public slots:
    void onPipeCreated(Pipe* pipe,PipeData_ptr);

    void onActionTriggered(QAction *action);

private:
    Ui::MainWindow *ui;

    QSettings *settings;
    ProxyServer *server;

};


#endif //QTINCLION_RYTHEMWINDOW_H
