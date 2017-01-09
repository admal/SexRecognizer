#pragma once
#include "../SexRecognizer.Common/IStrategy.h"

namespace Context 
{


class NeuralNetContext : public Common::IStrategy
{
public:
	void Execute(Common::IApplicationContext* context) override;
	void Execute(Common::IApplicationContext* context, SexRecognizer::Logger *logger) override;
	NeuralNetContext(){};
	~NeuralNetContext(){};
};

}