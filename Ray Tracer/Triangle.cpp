#include "StdAfx.h"
#include "Triangle.h"


CTriangle::CTriangle(void)
{
}


CTriangle::~CTriangle(void)
{
}

float CTriangle::intersect(CRay &ray)
{
	float t;
	glm::vec3 vector = countPlane();
	t = -(vector.x*ray.pos.x + vector.y*ray.pos.y + vector.z*ray.pos.z) / (vector.x*ray.dir.x + vector.y*ray.dir.y + vector.z*ray.dir.z);
	return t;
}

glm::vec3 CTriangle::countPlane()
{
	glm::vec3 u,v,w;
	u = glm::normalize(this->p3 - this->p2);
	v = glm::normalize(this->p1 - this->p2);
	w = glm::normalize(glm::cross(u, v));
	return w;
}

glm::vec3 CTriangle::countIntersectionPoint(CRay &ray, float t)
{
	glm::vec3 P = ray.pos + t * ray.dir;
	return P;
}

bool CTriangle::isPoinInsideTriangle(glm::vec3 point)
{
	glm::vec3 v0, v1, v2;
	v0 = glm::normalize(this->p3 - this->p1);
	v1 = glm::normalize(this->p2 - this->p1);
	v2 = glm::normalize(point - this->p1);
	float dot00 = glm::dot(v0, v0);
	float dot01 = glm::dot(v0, v1);
	float dot02 = glm::dot(v0, v2);
	float dot11 = glm::dot(v1, v1);
	float dot12 = glm::dot(v1, v2);
	float invDenom = 1.0f / (dot00*dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool CTriangle::isIntersected(CRay & ray)
{
	float t = intersect(ray);
	glm::vec3 point = countIntersectionPoint(ray, t);
	return false;//isPoinInsideTriangle(point);
}
