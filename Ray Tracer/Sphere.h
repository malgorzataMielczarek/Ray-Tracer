#pragma once
#include "glm/glm.hpp"
class CSphere : public CSceneObject
{
public:
	CSphere(void);
	~CSphere(void);
	float r;//Promien
	glm::vec3 o;//Srodek
	float intersect(CRay* ray);
};

