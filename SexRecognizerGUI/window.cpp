#include "window.h"

SexRecognizer::Window::Window(QWidget *parent) : QWidget(parent)
{
    m_button = new QPushButton("super button", this);
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
}

void SexRecognizer::Window::handleClick(){
    // change the text
   m_button->setText("Example");
   // resize button
   m_button->resize(100,100);
}
