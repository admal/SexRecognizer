#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "recognizer.h"
#include "logger.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    SexRecognizer::Recognizer *recognizer;
    Ui::MainWindow *ui;
    SexRecognizer::Logger *logger;
private slots:
    void handleLoadFile();
    void handleProcess();

};

#endif // MAINWINDOW_H
