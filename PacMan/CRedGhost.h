#pragma once

#include "CGhost.h"

class CRedGhost : public CGhost {
public:
	CRedGhost();
private:
	void ScatterState() override;
	void ChaseState() override;

	//Initalization Functions;
	void InitVariables() override;
	void InitSprite() override;

	//Update
	void UpdateDirTexture() override;
};

