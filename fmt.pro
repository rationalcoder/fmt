TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wno-missing-field-initializers -Winline -fno-rtti -fno-exceptions

SOURCES += tests/basic.cpp

INCLUDEPATH += include
