#include "StdAfx.h"
#include "Camera.h"


CCamera::CCamera(void)
{
}


CCamera::~CCamera(void)
{
}

glm::vec3 CCamera::countDir()
{
	glm::vec3 dir = normalize(this->target - this->pos);
	return dir;
}

glm::vec3 CCamera::countU(glm::vec3 dir)
{
	glm::vec3 u = normalize(cross(this->up, dir));
	return u;
}

glm::vec3 CCamera::countV(glm::vec3 dir, glm::vec3 u)
{
	glm::vec3 v = normalize(cross(u, dir));
	return glm::vec3();
}

glm::vec3 CCamera::countO(glm::vec3 dir, glm::vec3 u, glm::vec3 v)
{
	glm::vec3 o = dir * (this->mWidth / (2.0f * tan(glm::radians(this->fov) / 2.0f))) - u * (this->mWidth / 2.0f) - v * (this->mHeight / 2.0f);
	return glm::vec3();
}

void CCamera::countUvo()
{
	glm::vec3 dir = countDir();
	glm::vec3 u = countU(dir);
	glm::vec3 v = countV(dir, u);
	glm::vec3 o = countO(dir, u, v);
	this->uvo = glm::mat3(u, v, o);
}
