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
glm::vec3 trace_ray(CScene scene, CRay ray);
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
			vec3 basicColor = trace_ray(*scene, primaryRay);
			vec3 correctedColor = gammaCorrectRBG(basicColor);
			img.setPixel(i, scene->cam.mHeight - j - 1, basicColor);
        }
	}
			
	return 0;
}

vec3 trace_ray(CScene scene, CRay ray)
{
	for (int i = 0; i < scene.mObjects.size(); i++)
	{
		CSceneObject *object=scene.mObjects[i];
		if(object->isIntersected(ray))
		{
			return vec3(1, 0, 0);
		}
	}
	return vec3(0, 0, 0);
}

vec3 gammaCorrectRBG(vec3 color)
{
	double R = gammaCorrect(color.x);
	double G = gammaCorrect(color.y);
	double B = gammaCorrect(color.z);

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
