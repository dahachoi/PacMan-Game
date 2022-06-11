#pragma once

#include "CGhost.h"

class CRedGhost : public CGhost {
public:
	CRedGhost();

	//Update
	void UpdateTarget(const float&, const float&) override;
private:
	void ScatterState() override;
	void ChaseState() override;

	//Initalization Functions;
	void InitVariables() override;
	void InitSprite() override;

	//Update

	void UpdateDirTexture() override;
};

