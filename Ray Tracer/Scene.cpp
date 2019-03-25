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
			int cam_width;
			iss >> cam_width;
			this->cam.mWidth = cam_width;
		}
		else if (type.compare("cam_height") == 0)
		{
			int cam_height;
			iss >> cam_height;
			this->cam.mHeight = cam_height;
		}
		else if (type.compare("cam_FOV") == 0)
		{
			float cam_FOV;
			iss >> cam_FOV;
			this->cam.fov = cam_FOV;
		}
		else if (type.compare("cam_eyep") == 0)
		{
			float x, y, z;
			iss >> x >> y >> z;
			this->cam.pos = glm::vec3(x, y, z);
		}
		else if (type.compare("cam_lookp") == 0)
		{
			float x, y, z;
			iss >> x >> y >> z;
			this->cam.target = glm::vec3(x, y, z);
		}
		else if (type.compare("cam_up") == 0)
		{
			float x, y, z;
			iss >> x >> y >> z;
			this->cam.up = glm::vec3(x, y, z);
		}
		else if (type.compare("sphere") == 0)
		{
			float r, o_x, o_y, o_z, reflect, amb_x, amb_y, amb_z, diff_x, diff_y, diff_z, spec_x, spec_y, spec_z, shininess;
			iss >> r >> o_x >> o_y >> o_z >> reflect >> amb_x >> amb_y >> amb_z >> diff_x >> diff_y >> diff_z >> spec_x >> spec_y >> spec_z >> shininess;
			CSphere *sphere = new CSphere;
			sphere->r = r;
			sphere->o = glm::vec3(o_x, o_y, o_z);
			sphere->reflect = reflect;
			sphere->ambient = glm::vec3(amb_x, amb_y, amb_z);
			sphere->diffuse = glm::vec3(diff_x, diff_y, diff_z);
			sphere->specular = glm::vec3(spec_x, spec_y, spec_z);
			sphere->shininess = shininess;
			this->mObjects.push_back(sphere);
		}
	}
	return true;
}