#include "ModuleLightManager.h"

#include "ModuleScene.h"

#include "External/mmgr/mmgr.h"

ModuleLightManager::ModuleLightManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    LOG("Creating ModuleLightManager");

    debuglightsEnabled = true;

}

ModuleLightManager::~ModuleLightManager()
{

}

bool ModuleLightManager::Init()
{
    bool ret = true;

    return ret;
}

update_status ModuleLightManager::PreUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

update_status ModuleLightManager::Update(float dt)
{
    return UPDATE_CONTINUE;
}

update_status ModuleLightManager::PostUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

bool ModuleLightManager::CleanUp()
{
    bool ret = true;

    ClearLights();

    return ret;
}

void ModuleLightManager::EnableLightDebug(bool enable)
{
    debuglightsEnabled = enable;
}

bool ModuleLightManager::IsLightDebugEnabled()
{
    return debuglightsEnabled;
}

Light* ModuleLightManager::CreateLight(LightType type)
{
    switch (type) {

        case LightType::POINT_LIGHT:
        {
            PointLight* tmpLight = new PointLight();
            tmpLight->lightGO = App->scene->CreateGameObject("Point Light", App->scene->mRootNode);

            CLight* tmpComponentLight = new CLight(tmpLight->lightGO, tmpLight);
            tmpLight->lightGO->AddComponent(tmpComponentLight);

            lights.push_back(tmpLight);

            return tmpLight;

            break;
        }
        case LightType::DIRECTIONAL_LIGHT:
        {
            DirectionalLight* tmpLight = new DirectionalLight();
            tmpLight->lightGO = App->scene->CreateGameObject("Directional Light", App->scene->mRootNode);

            CLight* tmpComponentLight = new CLight(tmpLight->lightGO, tmpLight);
            tmpLight->lightGO->AddComponent(tmpComponentLight);

            lights.push_back(tmpLight);

            return tmpLight;

            break;
        }
        case LightType::SPOT_LIGHT:
        {
            SpotLight* tmpLight = new SpotLight();
            tmpLight->lightGO = App->scene->CreateGameObject("Spot Light", App->scene->mRootNode);

            CLight* tmpComponentLight = new CLight(tmpLight->lightGO, tmpLight);
            tmpLight->lightGO->AddComponent(tmpComponentLight);

            lights.push_back(tmpLight);

            return tmpLight;
         
            break;
        }
        case LightType::AREA_LIGHT:
        {
            AreaLight* tmpLight = new AreaLight();
            tmpLight->lightGO = App->scene->CreateGameObject("Area Light", App->scene->mRootNode);

            CLight* tmpComponentLight = new CLight(tmpLight->lightGO, tmpLight);
            tmpLight->lightGO->AddComponent(tmpComponentLight);

            lights.push_back(tmpLight);

            return tmpLight;

            break;
        }

    }

}

void ModuleLightManager::ClearLights()
{
    for (std::vector<Light*>::iterator itr = lights.begin(); itr != lights.end(); ++itr)
    {
        delete (*itr);
        (*itr) = nullptr;
    }

    lights.clear();
    lights.shrink_to_fit();
}
