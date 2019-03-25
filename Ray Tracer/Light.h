#pragma once
class CLight
{
public:
	glm::vec3 pos;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	CLight(void);
	~CLight(void);
};

