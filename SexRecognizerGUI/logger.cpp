#include "logger.h"

SexRecognizer::Logger::Logger(QTextEdit *textEdit)
{
    this->logger = textEdit;
}
void SexRecognizer::Logger::log(QString message){
    logger->append(message);
}
void SexRecognizer::Logger::error(QString errorMessage){
    logger->setTextColor(QColor::fromRgb(220, 0, 0));
    logger->append("ERROR:");
    logger->append(errorMessage);
    logger->setTextColor(QColor::fromRgb(0, 0, 0));
}

void SexRecognizer::Logger::clear()
{
    logger->setText("");
}
