TEMPLATE = subdirs

SUBDIRS = \
    PACParserWithQt \
    RythemCore \
    RythemUI \
    RythemInstaller

CONFIG += ordered

RythemCore.depends = PACParserWithQt
RythemUI.depends = RythemCore
RythemInstaller.depends = RythemUI
