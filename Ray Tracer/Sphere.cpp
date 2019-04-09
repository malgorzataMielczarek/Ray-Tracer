#include "StdAfx.h"
#include "Sphere.h"


CSphere::CSphere(void)
{
}


CSphere::~CSphere(void)
{
}

float CSphere::intersect(CRay &ray)
{
	float zero = 1E-5;
	float A, B, C, delta, t;
	A = 1;
	glm::vec3 v = ray.pos - this->o;
	B = glm::dot(v * 2.0f, ray.dir);
	C = glm::dot(v, v) - this->r*this->r;
	delta = B * B - 4.0f*A*C;
	if (delta > 0)
	{
		float t1 = (-B - glm::sqrt(delta)) / (2.0f*A);
		float t2 = (-B + glm::sqrt(delta)) / (2.0f*A);
		if (t1 < t2 && t1 >= zero)
		{
			t = t1;
		}
		else if (t2 >= zero)
		{
			t = t2;
		}
		else
		{
			t = -1;
		}
	}
	else if (delta < 0)
	{
		t = -1;
	}
	else
	{
		float t1 = (-B - glm::sqrt(delta)) / (2.0f*A);
		if (t1 >= zero)
		{
			t = t1;
		}
		else
		{
			t = -1;
		}
	}
	this->t = t;
	return t;
}

bool CSphere::isIntersected(CRay &ray)
{
	int t = intersect(ray);
	if (t > 0)
		return true;
	else
		return false;
}

void CSphere::countNVector()
{
	glm::vec3 nvector = this->pointOnSurface - this->o;
	this->nVector = normalize(nvector);
}
