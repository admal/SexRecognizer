#pragma once
#include "../SexRecognizer.Common/IStrategy.h"

namespace Context 
{


class NeuralNetContext : public Common::IStrategy
{
public:
	void Execute(Common::IApplicationContext* context) override;
	NeuralNetContext(){};
	~NeuralNetContext(){};
};

}