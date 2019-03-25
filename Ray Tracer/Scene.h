#pragma once
class CScene
{
public:

	CCamera cam;

	std::vector<CSceneObject*> mObjects;

	std::vector<CLight*> mLights;

	CScene(void);
	~CScene(void);

	bool parse(std::string fname);

private:
	void loadCamWidth(std::istringstream & iss);
	void loadCamHeight(std::istringstream & iss);
	void loadCamFOV(std::istringstream & iss);
	void loadCamPos(std::istringstream & iss);
	void loadCamTarget(std::istringstream & iss);
	void loadCamUp(std::istringstream & iss);
	void loadSphere(std::istringstream &iss);
	void loadTriangle(std::istringstream & iss);
	void loadLight(std::istringstream & iss);
};

