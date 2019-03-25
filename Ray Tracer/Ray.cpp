#include "StdAfx.h"
#include "Ray.h"


CRay::CRay(void)
{
}


CRay::~CRay(void)
{
}

void CRay::generatePrimaryRay(int x, int y, CCamera &camera)
{
	this->pos = camera.pos;
	this->dir = normalize(camera.uvo * glm::vec3(x + 0.5, y + 0.5, 1.0));
}