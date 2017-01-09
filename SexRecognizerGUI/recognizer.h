#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#include "logger.h"
#include "../SexRecognizer.Client/ApplicationContext.h"

namespace SexRecognizer{
    class Recognizer
    {
    public:
        Recognizer(Logger* logger);
        int loadImages(QString filePath);
        int process();
        ~Recognizer();
    private:
        Logger *logger;
		std::string videoPath;
	    Common::IApplicationContext *app;
    };
}
#endif // RECOGNIZER_H
