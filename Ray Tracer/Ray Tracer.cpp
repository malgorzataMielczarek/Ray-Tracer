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
	 //wczytywanie sceny: kamery, obiekty, œwiat³a
	CScene scene;
	/*scene.cam.mWidth = 1000;
	scene.cam.mHeight = 800;
	scene.cam.fov = 50;
	scene.cam.pos = vec3(0, 0, -10);
	scene.cam.target = vec3(0, 0, 0);
	scene.cam.up = vec3(0, 1, 0);
	CSphere* sphere = new CSphere;
	sphere->r = 2;
	sphere->o = vec3(0, 0, 0);
	scene.mObjects.push_back(sphere);*/
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
	vec3 dir = normalize(scene->cam.target - scene->cam.pos);
	vec3 u = normalize(cross(scene->cam.up, dir));
	vec3 v = normalize(cross(u, dir));
	vec3 o = dir * (scene->cam.mWidth / (2.0f * tan(radians(scene->cam.fov) / 2.0f))) - u * (scene->cam.mWidth / 2.0f) - v * (scene->cam.mHeight / 2.0f);
	mat3 uvo = mat3(u, v, o);
	for( int j = 0; j < scene->cam.mHeight; j++ ) {
		for( int i = 0; i < scene->cam.mWidth; i++ ) {
			CRay primaryRay;
			primaryRay.pos = scene->cam.pos;
			primaryRay.dir = normalize(uvo * vec3(j + 0.5, i + 0.5, 1.0));
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
