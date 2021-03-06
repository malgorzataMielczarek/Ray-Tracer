#pragma once
#include "Light.h"
class CSceneObject
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float reflect;
	float shininess;
	glm::vec3 pointOnSurface;
	glm::vec3 lVector;
	glm::vec3 nVector;
	float getT();
	float objectRefractionFactor;

protected:
	float t;
	glm::vec3 vVector;
	glm::vec3 hVector;

public:
	CSceneObject(void);
	~CSceneObject(void);

	virtual float intersect(CRay &ray) = 0;
	virtual bool isIntersected(CRay &ray) = 0;
	glm::vec3 countColorAmbientForAllLights(std::vector<CLight*> &mLights);
	glm::vec3 countColorForAllLights(std::vector<CLight*> &mLights, CRay &ray, CCamera* camera);
	glm::vec3 countColorForOneLight(CLight *light, CRay &ray, CCamera* camera);
	CRay generateSecondaryRay();
	void countPointOnSurface(CRay &ray);
	void countLVector(CLight* light);
private:
	glm::vec3 countColorAmbientForOneLight(CLight* light);
	glm::vec3 countColorDiffuseForOneLight(CLight* light);
	glm::vec3 countColorSpecularForOneLight(CLight* light);
	double countColorAmbientComponent(CLight* light, int numberOfComponent);
	double countColorDiffuseComponent(CLight* light, int numberOfComponent);
	double countColorSpecularComponent(CLight* light, int numberOfComponent);
	void countVVector(CCamera* camera);
	void countHVector();
protected:
	virtual void countNVector() = 0;
};

