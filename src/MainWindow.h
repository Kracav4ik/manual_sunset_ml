#pragma once

#include <QMainWindow>

#include "ui_ml_gui.h"


class MainWindow : public QMainWindow, private Ui::MainWindow {
public:
    MainWindow();

};

