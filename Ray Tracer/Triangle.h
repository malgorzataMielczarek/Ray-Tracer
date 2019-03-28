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

private:
	glm::vec3 countPlaneNormalVector();

	glm::vec3 countIntersectionPoint(CRay & ray, float t);

	bool isPoinInsideTriangle(glm::vec3 point);

public:
	bool isIntersected(CRay &ray);
};

