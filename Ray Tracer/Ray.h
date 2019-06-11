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
	void generateShadowRay(glm::vec3 intersectionPoint, glm::vec3 directory);
	void generateSecondaryRay(glm::vec3 intersectionPoint, glm::vec3 primaryRaydirectory,glm::vec3 n);
};

