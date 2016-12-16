#pragma once
#include "../SexRecognizer.Common/IStrategy.h"

class NeuralNetContext : public Common::IStrategy
{
public:
	void Execute(Common::IApplicationContext* context) override;
	NeuralNetContext(){};
	~NeuralNetContext(){};
};

