TEMPLATE = app 
TARGET = hyperloopUI
QT = core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG +=console

SOURCES +=  gui.cpp