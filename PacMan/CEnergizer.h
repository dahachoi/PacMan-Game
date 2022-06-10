#pragma once
#include "SFML/Graphics.hpp"

#include "CCoin.h"
class CEnergizer : public CCoin
{
public:
	//CEnergizer() = default;
	CEnergizer(const float&, const float&);
private:
	void InitCoin() override;
};

