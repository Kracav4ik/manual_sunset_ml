#pragma once

#include <QMainWindow>

#include "ui_ml_gui.h"


class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
public:
    MainWindow();

public slots:
    void on_browseButton_clicked();
    void on_processButton_clicked();
};

