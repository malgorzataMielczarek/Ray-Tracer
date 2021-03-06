// Ray Tracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "glm/glm.hpp"
#include "FreeImage.h"

struct Output {
	float energy;
	int tree;
	float color[3];
};

using namespace glm;

int run( CScene* scene, CBitmap& img );
glm::vec3 trace_ray(CScene scene, CRay ray, float energy);
int rayTrace( CRay &ray, CScene* scene, Output* res );
vec3 gammaCorrectRBG(vec3 color);
double gammaCorrect(double color);

int main(int argc, char** argv)
{
	CScene scene;
	bool isread = scene.parse("../scene_final.txt");
	printf("%s", isread ? "true" : "false");
	CBitmap img;
	img.init(scene.cam.mWidth, scene.cam.mHeight);
	run(&scene, img);
	img.save("../output.bmp");

	return 0;
}

// G³ówna pêtla ray tracer'a
int run( CScene* scene, CBitmap& img ) {
	scene->cam.countUvo();
	for( int j = 0; j < scene->cam.mHeight; j++ ) {
		for( int i = 0; i < scene->cam.mWidth; i++ ) {
			float energy = 1.0;
			CRay primaryRay;
			primaryRay.generatePrimaryRay(i, j, scene->cam);
			vec3 basicColor = trace_ray(*scene, primaryRay,energy);
			vec3 correctedColor = gammaCorrectRBG(basicColor);
			img.setPixel(i, scene->cam.mHeight - j - 1, correctedColor);
        }
	}
			
	return 0;
}

vec3 trace_ray(CScene scene, CRay ray, float energy)
{
	glm::vec3 color = vec3(0, 0, 0);
	CSceneObject *object;
	float distance = std::numeric_limits<float>::infinity();
	for (int i = 0; i < scene.mObjects.size(); i++)
	{

		object=scene.mObjects[i];
		if(object->isIntersected(ray))
		{
			float t = abs(object->getT());
			if (t < distance)
			{
				distance = t;
				object->countPointOnSurface(ray);

				for (int L = 0; L < scene.mLights.size(); L++)
				{
					CLight *light = scene.mLights[L];
					bool isShadow = false;
					object->countLVector(light);
					CRay shadowRay;
					shadowRay.generateShadowRay(object->pointOnSurface, object->lVector);
					for (int j = 0; j < scene.mObjects.size(); j++)
					{
						CSceneObject *object1 = scene.mObjects[j];
						if (object1->isIntersected(shadowRay))
						{
							isShadow = true;
						}
					}
					if (!isShadow)
					{
						color = color + energy*object->countColorForOneLight(light, ray, &scene.cam);
					}
				}
			}
		}
	}
	energy = energy*0.5;
	if (energy < 0.00001)
	{
		return color;
	}
	CRay secondaryRay;
	secondaryRay.generateSecondaryRay(object->pointOnSurface, ray.dir, object->nVector);
	color = color + energy * trace_ray(scene, secondaryRay, energy);
	//CRay refractedRay;
	//if (ray.refractionFactor != object->objectRefractionFactor)
	//{
		//refractedRay.generateRefractedRay(object->nVector, object->pointOnSurface, object->objectRefractionFactor, &ray);
	//}
	//color = color + energy * trace_ray(scene, refractedRay, energy);
	return color;
}

vec3 gammaCorrectRBG(vec3 color)
{
	float R = gammaCorrect(color.x);
	float G = gammaCorrect(color.y);
	float B = gammaCorrect(color.z);
	R = glm::clamp(R, 0.0f, 1.0f);
	G = glm::clamp(G, 0.0f, 1.0f);
	B = glm::clamp(B, 0.0f, 1.0f);
	return vec3(R, G, B);
}

double gammaCorrect(double color)
{
	double newColor;
	if (color < 0.00304)
	{
		newColor = color * 12.92;
	}
	else
	{
		newColor = 1.55 * pow(color, 1 / 2.4) - 0.055;
	}
	return newColor;
}

/*
CSceneObject* findIntersection(CScene scene, CRay ray, bool closestIntersection)
{
	CSceneObject* intersectedObject = NULL;
	for (int i = 0; i < scene.mObjects.size(); i++)
	{
		CSceneObject *object = scene.mObjects[i];
		bool intersection = object->isIntersected(ray);
		if (intersection)
		{
			if (closestIntersection)
			{

			}
		}
	}
}
*/
// Sledzenie pojedynczego promienia
int rayTrace( CRay &ray, CScene* scene, Output* res ) 
{
	return 0;
}
