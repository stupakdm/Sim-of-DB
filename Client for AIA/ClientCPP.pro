TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        exec_commands.cpp \
        main.cpp \
        network_communicate.cpp \
        special_functions.cpp \
        terminal.cpp

HEADERS += \
    exec_commands.h \
    network_communicate.h \
    special_functions.h \
    structures.h \
    terminal.h
