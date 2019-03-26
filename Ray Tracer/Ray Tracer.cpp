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


int run( CScene* scene, CBitmap& img );
glm::vec3 trace_ray(CScene scene, CRay ray);
int rayTrace( CRay &ray, CScene* scene, Output* res );

using namespace glm;

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
			vec3 color = trace_ray(*scene, primaryRay);
			img.setPixel(i, scene->cam.mHeight - j - 1, color);
			/*vec3 color;
			color.x = float(x) / scene->cam.mWidth;
			color.y = float(y) / scene->cam.mHeight;
			//color.z = abs(sin(float(y) / scene->cam.mHeight * 20));
			img.setPixel(x, y, color);*/
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
