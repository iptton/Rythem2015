#include <iostream>
#include <QApplication>
#include <GUI/RythemWindow.h>
#include "Rythem.h"


int main(int argc,char **argv) {

    Rythem application(argc,argv);

    std::cout << "Hello, Rythem!" << std::endl;


    return application.exec();
}