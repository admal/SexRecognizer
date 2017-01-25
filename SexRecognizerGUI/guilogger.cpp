#include "guilogger.h"

SexRecognizer::GUILogger::GUILogger(QTextEdit *textEdit)
{
    this->logger = textEdit;
}


void SexRecognizer::GUILogger::log(QString message){
    logger->append(message);
}
void SexRecognizer::GUILogger::error(QString errorMessage){
    logger->setTextColor(QColor::fromRgb(220, 0, 0));
    logger->append("ERROR:");
    logger->append(errorMessage);
    logger->setTextColor(QColor::fromRgb(0, 0, 0));
}

void SexRecognizer::GUILogger::clear()
{
    logger->setText("");
}


