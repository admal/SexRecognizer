#pragma once
#include <string>
#include "../SexRecognizer.Common/IStrategy.h"
#include "../SexRecognizer.Common/ImageHelper.h"


using namespace Common;

class DetectorContext : public IStrategy
{
public:
	void Execute(IApplicationContext* context) override;
	DetectorContext();
	~DetectorContext();

};

