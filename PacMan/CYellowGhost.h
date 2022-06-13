#pragma once

#include "CGhost.h"

class CYellowGhost : public CGhost{
public:
	CYellowGhost();

	//Update
	void UpdateTarget(const float&, const float&, const DIRECTION&, const float&, const float&) override;
private:

	//Initalization Functions;
	void InitVariables() override;
	void InitSprite() override;

	//Update
	void CalculateTarget(const float&, const float&, const DIRECTION&, const float&, const float&) override;
	void UpdateDirTexture() override;
};

