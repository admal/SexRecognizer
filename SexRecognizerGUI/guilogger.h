#ifndef GUILOGGER_H
#define GUILOGGER_H

#include "QTextEdit.h"

namespace SexRecognizer{
class GUILogger
{
public:
    GUILogger(QTextEdit *textEdit);
    void error(QString errorMessage);
    void log(QString message);
    void clear();
private:
    QTextEdit *logger;
};
}
#endif // GUILOGGER_H
