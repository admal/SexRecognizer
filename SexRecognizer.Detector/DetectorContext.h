#pragma once
#include <string>
#include "../SexRecognizer.Common/IStrategy.h"
#include "../SexRecognizer.Common/ImageHelper.h"
#include "../SexRecognizerGUI/recognizer.h"

class Logger;
using namespace Common;
using namespace SexRecognizer;

class DetectorContext : public IStrategy
{
public:
	void Execute(IApplicationContext* context) override;
	void Execute(IApplicationContext* context, SexRecognizer::Logger *logger) override;
	DetectorContext();
	~DetectorContext();
};

