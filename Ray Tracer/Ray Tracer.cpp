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
int rayTrace( CRay &ray, CScene* scene, Output* res );

using namespace glm;

int main(int argc, char** argv)
{
	 //wczytywanie sceny: kamery, obiekty, œwiat³a
	CScene scene;
	scene.cam.mWidth = 1000;
	scene.cam.mHeight = 1000;

	CBitmap img;
	img.init(scene.cam.mWidth, scene.cam.mHeight);
	run(&scene, img);

	vec3 v1 = vec3(20, 30, 40);
	vec3 v2 = vec3(50, 60, 70);
	vec3 v3 = glm::cross(v1, v2);

	printf("%f %f %f\n", v3.x, v3.y, v3.z);

	img.save("../output.bmp");

	return 0;
}

// G³ówna pêtla ray tracer'a
int run( CScene* scene, CBitmap& img ) {
		
	for( int y = 0; y < scene->cam.mHeight; y++ ) {
		for( int x = 0; x < scene->cam.mWidth; x++ ) {
			vec3 color;
			color.x = float(x) / scene->cam.mWidth;
			color.y = float(y) / scene->cam.mHeight;
			//color.z = abs(sin(float(y) / scene->cam.mHeight * 20));
			img.setPixel(x, y, color);
        }
	}
			
	return 0;
}

// Sledzenie pojedynczego promienia
int rayTrace( CRay &ray, CScene* scene, Output* res ) 
{
	return 0;
}