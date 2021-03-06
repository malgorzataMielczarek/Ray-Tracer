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

void CRay::generateShadowRay(glm::vec3 intersectionPoint, glm::vec3 directory)
{
	this->pos = intersectionPoint+directory*0.1f;
	this->dir = directory;
}

void CRay::generateSecondaryRay(glm::vec3 intersectionPoint, glm::vec3 primaryRaydirectory, glm::vec3 n)
{
	this->dir = primaryRaydirectory - (2.0f*glm::dot(primaryRaydirectory,n))*n;
	this->dir = glm::normalize(this->dir);
	this->pos = intersectionPoint;// +this->dir * 0.1f;
}

void CRay::generateRefractedRay(glm::vec3 nVector,glm::vec3 P,float objectRefractionFactor, CRay* ray)
{
	float alfa = acos(glm::dot(-ray->dir,nVector));
	float beta = asin(sin(alfa)*ray->refractionFactor / objectRefractionFactor);
	this->dir = nVector / cos(beta);
	this->pos = P;
	this->refractionFactor = objectRefractionFactor;
}
