#pragma once
#include "glm/glm.hpp"
#include "Camera.h"

class CRay
{
public:
	glm::vec3 pos;
	glm::vec3 dir;

	CRay(void);
	~CRay(void);
	void generatePrimaryRay(int x, int y, CCamera &camera);
};

