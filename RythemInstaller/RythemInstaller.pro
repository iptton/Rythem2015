TEMPLATE = aux

INSTALLER = installer
QIF = /Users/ippan/Qt/QtIFW-3.0.1

INPUT = $$PWD/config/config.xml $$PWD/packages
example.input = INPUT
example.output = $$INSTALLER
example.commands = $$QIF/bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
example.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += example

OTHER_FILES = README

OUTPUT = $$PWD/../


