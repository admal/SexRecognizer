#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
namespace SexRecognizer {
    class Window : public QWidget
    {
        Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
    private slots:
        void handleClick();
    private:
        QPushButton *m_button;
    signals:

    public slots:
    };
}
#endif // WINDOW_H
