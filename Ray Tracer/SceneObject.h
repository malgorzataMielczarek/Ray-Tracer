#pragma once
class CSceneObject
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float reflect;
	float shininess;
	CSceneObject(void);
	~CSceneObject(void);

	virtual float intersect( CRay* ray ) = 0;
};

