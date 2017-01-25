#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#include "guilogger.h"
#include "../SexRecognizer.Client/ApplicationContext.h"

namespace SexRecognizer{
    class Recognizer
    {
    public:
		Recognizer(GUILogger* logger);
        int loadImages(QString filePath);
        int process();
        ~Recognizer();
    private:
		GUILogger *logger;
		std::string videoPath;
	    Common::IApplicationContext *app;
    };
}
#endif // RECOGNIZER_H
