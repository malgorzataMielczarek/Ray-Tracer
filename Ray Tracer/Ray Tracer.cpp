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
	bool isread = scene.parse("../scene_simple.txt");
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
			CRay primaryRay;
			primaryRay.generatePrimaryRay(j, i, scene->cam);
			vec3 color = trace_ray(*scene, primaryRay);
			img.setPixel(i, j, color);
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
		float t = object->intersect(&ray);
		if(t>0)
		{
			return vec3(1, 0, 0);
		}
	}
	return vec3(0, 0, 0);
}
// Sledzenie pojedynczego promienia
int rayTrace( CRay &ray, CScene* scene, Output* res ) 
{
	return 0;
}
