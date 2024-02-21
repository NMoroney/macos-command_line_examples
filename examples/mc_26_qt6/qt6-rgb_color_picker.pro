# © 2024 : github.com/NMoroney
# MIT License 
#

TEMPLATE = app
TARGET = qt6-rgb_color_picker

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  qt6-rgb_color_picker.cc
