#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "recognizer.h"
#include "guilogger.h"
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
	SexRecognizer::GUILogger *logger;
private Q_SLOTS:
    void handleLoadFile();
    void handleProcess();
};

#endif // MAINWINDOW_H
