#pragma once
class CTriangle : public CSceneObject
{
public:
	CTriangle(void);
	~CTriangle(void);

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;

	float intersect(CRay &ray);
	bool isIntersected(CRay &ray);
};

