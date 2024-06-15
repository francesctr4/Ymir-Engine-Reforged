#pragma once

#include "Globals.h"
#include "Timer.h"
#include "TimeManager.h"

#include<vector>

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModuleEditor;
class ModuleScene;
class ModuleResourceManager;
class ModuleFileSystem;
class ModuleMonoManager;
class ModuleAudio;
class ModulePhysics;
class ModuleLightManager;
class ModulePathFinding;

class Application
{
public:

	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;
	ModuleScene* scene;
	ModuleResourceManager* resourceManager;
	ModuleFileSystem* fileSystem;
	ModuleMonoManager* moduleMono;
	ModuleAudio* audio;
	ModulePhysics* physics;
	ModuleLightManager* lightManager;
	ModulePathFinding* pathFinding;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

	float targetFPS;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void SetTargetFPS(float FPS);
	float GetTargetFPS();

	float GetFPS();
	float GetDT();
	float GetMS();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* External;