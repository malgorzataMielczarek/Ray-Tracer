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
	glm::mat3 uvo;

	CCamera(void);
	~CCamera(void);
	void countUvo();

private:
	glm::vec3 countDir();
	glm::vec3 countU(glm::vec3 dir);
	glm::vec3 countV(glm::vec3 dir, glm::vec3 u);
	glm::vec3 countO(glm::vec3 dir, glm::vec3 u, glm::vec3 v);
};

