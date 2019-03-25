#include "StdAfx.h"
#include "Scene.h"
#include <fstream>
#include <sstream>

CScene::CScene(void)
{
}


CScene::~CScene(void)
{
}

bool CScene::parse(std::string fname)
{
	std::ifstream file;
	file.open(fname.c_str(), std::ios::in);
	if (file.fail())
	{
		return false;
	}
	std::string line;
	while (getline(file, line))
	{
		std::istringstream iss(line);
		std::string type;
		iss >> type;
		if (type.compare("cam_width") == 0)
		{
			loadCamWidth(iss);
		}
		else if (type.compare("cam_height") == 0)
		{
			loadCamHeight(iss);
		}
		else if (type.compare("cam_FOV") == 0)
		{
			loadCamFOV(iss);
		}
		else if (type.compare("cam_eyep") == 0)
		{
			loadCamPos(iss);
		}
		else if (type.compare("cam_lookp") == 0)
		{
			loadCamTarget(iss);
		}
		else if (type.compare("cam_up") == 0)
		{
			loadCamUp(iss);
		}
		else if (type.compare("sphere") == 0)
		{
			loadSphere(iss);
		}
		else if (type.compare("triangle") == 0)
		{
			loadTriangle(iss);
		}
		else if (type.compare("light") == 0)
		{
			loadLight(iss);
		}
	}
	return true;
}

void CScene::loadCamWidth(std::istringstream &iss)
{
	int cam_width;
	iss >> cam_width;
	this->cam.mWidth = cam_width;
}

void CScene::loadCamHeight(std::istringstream &iss)
{
	int cam_height;
	iss >> cam_height;
	this->cam.mHeight = cam_height;
}

void CScene::loadCamFOV(std::istringstream &iss)
{
	float cam_FOV;
	iss >> cam_FOV;
	this->cam.fov = cam_FOV;
}

void CScene::loadCamPos(std::istringstream &iss)
{
	float x, y, z;
	iss >> x >> y >> z;
	this->cam.pos = glm::vec3(x, y, z);
}

void CScene::loadCamTarget(std::istringstream &iss)
{
	float x, y, z;
	iss >> x >> y >> z;
	this->cam.target = glm::vec3(x, y, z);
}

void CScene::loadCamUp(std::istringstream &iss)
{
	float x, y, z;
	iss >> x >> y >> z;
	this->cam.up = glm::vec3(x, y, z);
}

void CScene::loadSphere(std::istringstream &iss)
{
	float r, o_x, o_y, o_z, reflect, amb_r, amb_g, amb_b, diff_r, diff_g, diff_b, spec_r, spec_g, spec_b, shininess;
	iss >> r >> o_x >> o_y >> o_z >> reflect >> amb_r >> amb_g >> amb_b >> diff_r >> diff_g >> diff_b >> spec_r >> spec_g >> spec_b >> shininess;
	CSphere *sphere = new CSphere;
	sphere->r = r;
	sphere->o = glm::vec3(o_x, o_y, o_z);
	sphere->reflect = reflect;
	sphere->ambient = glm::vec3(amb_r, amb_g, amb_b);
	sphere->diffuse = glm::vec3(diff_r, diff_g, diff_b);
	sphere->specular = glm::vec3(spec_r, spec_g, spec_b);
	sphere->shininess = shininess;
	this->mObjects.push_back(sphere);
}

void CScene::loadTriangle(std::istringstream &iss)
{
	float p0_x, p0_y, p0_z, p1_x, p1_y, p1_z, p2_x, p2_y, p2_z, reflect, amb_r, amb_g, amb_b, diff_r, diff_g, diff_b, spec_r, spec_g, spec_b, shininess;
	iss >> p0_x >> p0_y >> p0_z >> p1_x >> p1_y >> p1_z >> p2_x >> p2_y >> p2_z >> reflect >> amb_r >> amb_g >> amb_b >> diff_r >> diff_g >> diff_b >> spec_r >> spec_g >> spec_b >> shininess;
	CTriangle *triangle = new CTriangle;
	triangle->p1 = glm::vec3(p0_x, p0_y, p0_z);
	triangle->p2 = glm::vec3(p1_x, p1_y, p1_z);
	triangle->p3 = glm::vec3(p2_x, p2_y, p2_z);
	triangle->reflect = reflect;
	triangle->ambient = glm::vec3(amb_r, amb_g, amb_b);
	triangle->diffuse = glm::vec3(diff_r, diff_g, diff_b);
	triangle->specular = glm::vec3(spec_r, spec_g, spec_b);
	triangle->shininess = shininess;
	this->mObjects.push_back(triangle);
}

void CScene::loadLight(std::istringstream &iss)
{
	float pos_x, pos_y, pos_z, amb_r, amb_g, amb_b, diff_r, diff_g, diff_b, spec_r, spec_g, spec_b;
	iss >> pos_x >> pos_y >> pos_z >> amb_r >> amb_g >> amb_b >> diff_r >> diff_g >> diff_b >> spec_r >> spec_g >> spec_b;
	CLight *light = new CLight;
	light->pos = glm::vec3(pos_x, pos_y, pos_z);
	light->ambient = glm::vec3(amb_r, amb_g, amb_b);
	light->diffuse = glm::vec3(diff_r, diff_g, diff_b);
	light->specular = glm::vec3(spec_r, spec_g, spec_b);
	this->mLights.push_back(light);
}