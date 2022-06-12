#pragma once

#include "CGhost.h"

class CCyanGhost : public CGhost {
public:
	CCyanGhost();

	//Update
	void UpdateTarget(const float&, const float&) override;
private:

	//Initalization Functions;
	void InitVariables() override;
	void InitSprite() override;

	//Update

	void UpdateDirTexture() override;
};

