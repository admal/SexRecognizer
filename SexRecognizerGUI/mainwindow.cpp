#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

using namespace std;
using namespace SexRecognizer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->textLog->setEnabled(false);
    this->logger = new Logger(ui->textLog);
    recognizer = new SexRecognizer::Recognizer(logger);
    connect(ui->loadFileButton, SIGNAL (released()), this, SLOT (handleLoadFile()));
    connect(ui->processButton, SIGNAL (released()), this, SLOT (handleProcess()));
}

void MainWindow::handleLoadFile(){
	logger->log("opening file dialog window.");
    //open file chooser
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    if(fileName != nullptr){
        logger->clear();
        int fileLoaded = 1;
        fileLoaded = recognizer->loadImages(fileName);
        if(fileLoaded == 0){
          logger->error("File did not load, possible solutions:\n"
                 "  make sure there is enough frames (over 25)\n"
                 "  the frames have to follow the naming convention:\n"
                 "      they have to start from 000.jpg, 001.jpg, ...");

        }else{
            logger->log("File loaded successfully!");
            recognizer->process();
        }
    }
}

void MainWindow::handleProcess(){
    logger->log("something should happen");
}


MainWindow::~MainWindow()
{
    delete ui;
}
