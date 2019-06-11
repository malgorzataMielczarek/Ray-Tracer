#include "StdAfx.h"
#include "SceneObject.h"


float CSceneObject::getT()
{
	return this->t;
}

CSceneObject::CSceneObject(void)
{
}


CSceneObject::~CSceneObject(void)
{
}

glm::vec3 CSceneObject::countColorAmbientForAllLights(std::vector<CLight*> &mLights)
{
	glm::vec3 amb = glm::vec3(0, 0, 0);
	for (int i = 0; i < mLights.size(); i++)
	{
		CLight* light = mLights[i];
		amb += countColorAmbientForOneLight(light);
	}
	return amb;
}

glm::vec3 CSceneObject::countColorForAllLights(std::vector<CLight*> &mLights, CRay &ray, CCamera* camera)
{
	countPointOnSurface(ray);
	countNVector();
	countVVector(camera);
	glm::vec3 color = glm::vec3(0, 0, 0);
	for (int i = 0; i < mLights.size(); i++)
	{
		CLight* light = mLights[i];
		countLVector(light);
		countHVector();
		color = color + countColorAmbientForOneLight(light);
		color = color + countColorDiffuseForOneLight(light);
		color = color + countColorSpecularForOneLight(light);
	}
	return color;
}

glm::vec3 CSceneObject::countColorForOneLight(CLight * light, CRay & ray, CCamera * camera)
{
	countNVector();
	countVVector(camera);
	glm::vec3 color = glm::vec3(0, 0, 0);
	countLVector(light);
	countHVector();
	color = color + countColorAmbientForOneLight(light);
	color = color + countColorDiffuseForOneLight(light);
	color = color + countColorSpecularForOneLight(light);
	return color;
}

CRay CSceneObject::generateSecondaryRay()
{
	CRay ray;
	ray.pos = this->pointOnSurface;
	ray.dir = this->vVector - (2 * glm::dot(this->vVector, this->nVector)) * this->nVector;
	return ray;
}

glm::vec3 CSceneObject::countColorAmbientForOneLight(CLight * light)
{
	double red, green, blue;
	red = countColorAmbientComponent(light, 0);
	green = countColorAmbientComponent(light, 1);
	blue = countColorAmbientComponent(light, 2);
	return glm::vec3(red, green, blue);
}

glm::vec3 CSceneObject::countColorDiffuseForOneLight(CLight * light)
{
	double red, green, blue;
	red = countColorDiffuseComponent(light, 0);
	green = countColorDiffuseComponent(light, 1);
	blue = countColorDiffuseComponent(light, 2);
	return glm::vec3(red, green, blue);
}

glm::vec3 CSceneObject::countColorSpecularForOneLight(CLight * light)
{
	double red, green, blue;
	red = countColorSpecularComponent(light, 0);
	green = countColorSpecularComponent(light, 1);
	blue = countColorSpecularComponent(light, 2);
	return glm::vec3(red, green, blue);
}

double CSceneObject::countColorAmbientComponent(CLight * light, int numberOfComponent)
{
	double colorAmbientComponent;
	colorAmbientComponent = this->ambient[numberOfComponent] * light->ambient[numberOfComponent];
	return colorAmbientComponent;
}

double CSceneObject::countColorDiffuseComponent(CLight * light, int numberOfComponent)
{
	double colorDiffuseComponent = glm::dot(this->lVector, this->nVector);
	colorDiffuseComponent = this->diffuse[numberOfComponent]*light->diffuse[numberOfComponent] * colorDiffuseComponent;
	return colorDiffuseComponent;
}

double CSceneObject::countColorSpecularComponent(CLight * light, int numberOfComponent)
{
	double colorSpecularComponent = pow(glm::dot(this->nVector, this->hVector), this->shininess);
	colorSpecularComponent = this->specular[numberOfComponent]*light->specular[numberOfComponent] * colorSpecularComponent;
	return colorSpecularComponent;
}

void CSceneObject::countPointOnSurface(CRay & ray)
{
	glm::vec3 point = ray.pos + this->t * ray.dir;
	this->pointOnSurface = point;
}

void CSceneObject::countLVector(CLight * light)
{
	glm::vec3 lvector = light->pos - this->pointOnSurface;
	this->lVector = normalize(lvector);
}

void CSceneObject::countVVector(CCamera * camera)
{
	glm::vec3 vvector = camera->pos - this->pointOnSurface;
	this->vVector = normalize(vvector);
}

void CSceneObject::countHVector()
{
	glm::vec3 hvector = this->lVector + this->vVector;
	this->hVector = normalize(hvector);
}
