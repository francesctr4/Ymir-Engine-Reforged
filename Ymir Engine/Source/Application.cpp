#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleResourceManager.h"
#include "ModuleFileSystem.h"
#include "ModuleMonoManager.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleLightManager.h"
#include "ModulePathfinding.h"

#include "Log.h"

#include "External/Optick/include/optick.h"

#include "Tracy.h"

#include "External/mmgr/mmgr.h"

extern Application* External = nullptr;

Application::Application()
{
	targetFPS = 60.0f;

	External = this;

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleEditor(this);
	scene = new ModuleScene(this);
	resourceManager = new ModuleResourceManager(this);
	fileSystem = new ModuleFileSystem(this);
	moduleMono = new ModuleMonoManager(this);
	audio = new ModuleAudio(this);
	physics = new ModulePhysics(this);
	lightManager = new ModuleLightManager(this);
	pathFinding = new ModulePathFinding(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);

	// Physics
	AddModule(physics);

	// Utility Modules
	AddModule(fileSystem);
	AddModule(resourceManager);
	AddModule(moduleMono);
	AddModule(pathFinding);
	AddModule(scene);
	AddModule(lightManager);

	// Renderer last, and then editor!
	AddModule(renderer3D);
	AddModule(editor);
}

Application::~Application()
{
	for (std::vector<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
	{
		delete (*it);
		(*it) = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (std::vector<Module*>::const_iterator it = list_modules.cbegin(); it != list_modules.cend() && ret; ++it)
	{
		(*it)->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	for (std::vector<Module*>::const_iterator it = list_modules.cbegin(); it != list_modules.cend() && ret; ++it)
	{
		(*it)->Start();
	}
	
	ms_timer.Start();

	TimeManager::FrameCount = 0;
	TimeManager::graphicsTimer.Start();

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	OPTICK_EVENT();

	// Measure the time elapsed since the last frame
	dt = (float)ms_timer.ReadMS() / 1000.0f;
	ms_timer.Start();

	const float targetFrameTime = 1.0f / targetFPS;

	if (dt < targetFrameTime) {

		/* If the time elapsed since the last frame is less than the target frame time,
		introduce a delay to ensure we wait until the target frame time has elapsed. */

		Sleep((targetFrameTime - dt) * 1000); // Convert to milliseconds

		dt = targetFrameTime; // Update dt to match the target frame time.
	}

	TimeManager::DeltaTime = dt;
	TimeManager::FrameCount++;
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	OPTICK_EVENT();
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	OPTICK_EVENT();

	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (std::vector<Module*>::const_iterator it = list_modules.cbegin(); it != list_modules.cend() && ret == UPDATE_CONTINUE; ++it)
	{
		ret = (*it)->PreUpdate(dt);
	}

	for (std::vector<Module*>::const_iterator it = list_modules.cbegin(); it != list_modules.cend() && ret == UPDATE_CONTINUE; ++it)
	{
		ret = (*it)->Update(dt);
	}

	for (std::vector<Module*>::const_iterator it = list_modules.cbegin(); it != list_modules.cend() && ret == UPDATE_CONTINUE; ++it)
	{
		ret = (*it)->PostUpdate(dt);
	}

	FinishUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (std::vector<Module*>::reverse_iterator it = list_modules.rbegin(); it != list_modules.rend() && ret; ++it)
	{
		ret = (*it)->CleanUp();
	}
	return ret;
}

void Application::SetTargetFPS(float FPS)
{
	targetFPS = FPS;
}

float Application::GetTargetFPS()
{
	return targetFPS;
}

float Application::GetFPS()
{
	return 1 / dt;
}

float Application::GetDT()
{
	return dt;
}

float Application::GetMS()
{
	return dt * 1000;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}