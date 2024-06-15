#pragma once

#include <string>
#include <fstream>

#include "External/Parson/parson.h"

#include "External/MathGeoLib/include/Math/float2.h"
#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/float4.h"

#include "External/MathGeoLib/include/Math/float3x3.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

#include "External/MathGeoLib/include/Math/Quat.h"

#include "ResourceMesh.h"

class GameObject;
class Component;
class G_UI;

class JsonFile {
public:

    JsonFile();
    JsonFile(std::string route, std::string fileName);

    virtual ~JsonFile();

    void CreateJSON(std::string route, std::string fileName);
    void ModifyJSON(std::string route, std::string fileName);

    static std::unique_ptr<JsonFile> GetJSON(const std::string& route);
    static void DeleteJSON(const std::string& route);

    // -------------------------- Support functions --------------------------------
    void UpdateJSON_File(const char* key);

    void SetInt(const char* key, int value);
    int GetInt(const char* key) const;

    void SetFloat(const char* key, float value);
    float GetFloat(const char* key) const;

    void SetDouble(const char* key, double value);
    double GetDouble(const char* key) const;

    void SetBoolean(const char* key, bool value);
    bool GetBoolean(const char* key) const;

    void SetString(const char* key, const char* string);
    std::string GetString(const char* key) const;

    void SetIntArray(const char* key, const int* array, size_t size);
    std::unique_ptr<int[]> GetIntArray(const char* key) const;

    void SetFloatArray(const char* key, const float* array, size_t size);
    float* GetFloatArray(const char* key) const;

    void SetDoubleArray(const char* key, const double* array, size_t size);
    double* GetDoubleArray(const char* key) const;

    // -------------------------- MathGeoLib functions --------------------------------

    void SetFloat2(const char* key, const float2& value);
    float2 GetFloat2(const char* key) const;

    void SetFloat3(const char* key, const float3& value);
    float3 GetFloat3(const char* key) const;

    void SetFloat4(const char* key, const float4& value);
    float4 GetFloat4(const char* key) const;

    void SetMatrix3x3(const char* key, const float3x3& matrix);
    float3x3 GetMatrix3x3(const char* key) const;

    void SetMatrix4x4(const char* key, const float4x4& matrix);
    float4x4 GetMatrix4x4(const char* key) const;

    void SetQuat(const char* key, const Quat& quaternion);
    Quat GetQuat(const char* key) const;

    // -------------------------- Scene Serialization functions --------------------------------

    // ---------- Individual Elements

    void SetComponent(const char* key, const Component& component);
    Component* GetComponent(const char* key) const;

    void SetGameObject(const char* key, const GameObject& gameObject);
    GameObject* GetGameObject(const char* key) const;
    
    // ---------- Save Scene 

    void SetHierarchy(const char* key, const std::vector<GameObject*>& gameObjects);
    void SetGameObject(JSON_Array* value, const GameObject& gameObject);
    void SetComponent(JSON_Object* componentObject, const Component& component);
    void SetColor(JSON_Object* componentObject, const Component& component);

    void SetReference(JSON_Object* componentObject, GameObject& pointer, const char* name);
    // ---------- Load Scene

    void GetHierarchyNoMemoryLeaks(const char* key) const;
    std::vector<GameObject*> GetHierarchy(const char* key) const;

    const char* GetNavMeshPath(const char* key) const;
    void GetGameObject(const std::vector<GameObject*>& gameObjects, const JSON_Object* gameObjectObject, G_UI& gameObject) const;
    void GetComponent(const JSON_Object* componentObject, G_UI* gameObject) const;

    // Use "push" only the first time in each component
    int GetReference(const JSON_Object* componentObject, Component& comp, const char* name, bool push = false) const;

    // ---------- Save/Load Prefabs 

    void SetPrefab(const char* key, const GameObject& gameObject);

//private:

    JSON_Value* rootValue; // Private member to store JSON value
    JSON_Object* rootObject; // Private member to store JSON object

    void InitializeJSON(); // Helper function to initialize JSON object and value.
    void DeinitializeJSON(); // Helper function to deinitialize JSON object and value.

};