#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
	bool isInside(double x1, double x2) const override;
	uint16_t GetScore() const override { return score; }
	void Draw() const override;

private:
	const uint16_t score = 40;
};
