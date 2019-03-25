#pragma once
#include "glm/glm.hpp"

class CCamera
{
public:

	int mWidth;
	int mHeight;
	glm::vec3 pos;
	float fov;
	glm::vec3 up;
	glm::vec3 target;

	CCamera(void);
	~CCamera(void);
};

