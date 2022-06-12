#pragma once

#include "CGhost.h"

class CPinkGhost : public CGhost {
public:
	CPinkGhost();

	//Update
	void UpdateTarget(const float&, const float&) override;
private:

	//Initalization Functions;
	void InitVariables() override;
	void InitSprite() override;

	//Update

	void UpdateDirTexture() override;
};

