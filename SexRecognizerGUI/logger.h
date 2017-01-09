#ifndef LOGGER_H
#define LOGGER_H
#include "QtCore/QString.h"
#include "QtWidgets/QTextEdit.h"

namespace SexRecognizer{
	class Logger
	{
	public:
		Logger(QTextEdit *textEdit);
		void error(QString errorMessage);
		void log(QString message);
		void clear();
	private:
		QTextEdit *logger;
	};
}
#endif // LOGGER_H
