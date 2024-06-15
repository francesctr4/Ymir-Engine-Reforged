#pragma once

#include "Component.h"
#include "CMesh.h"
#include "ResourceMesh.h"

#include "External/MathGeoLib/include/Math/float3.h"
#include "External/MathGeoLib/include/Math/Quat.h"
#include "External/MathGeoLib/include/Math/float4x4.h"

class btQuaternion;

class CTransform : public Component {
public:

	//MYTODO: Prueba
	CTransform();

	CTransform(GameObject* owner);
	CTransform(GameObject* g, float3 pos, Quat rot, float3 sc, bool start_enabled = true);

	virtual ~CTransform();

	void Update() override;
	void OnInspector() override;

	void SetTransform(float3 pos = float3(0, 0, 0), float3 rot = float3(0, 0, 0), float3 scale = float3(0, 0, 0));
	void SetTransform(CTransform& t);
	void SetTransformFromMatrix(const float* matrix);
	void CalculateMatrix();
	void SetPosition(float3 vec = float3(0, 0, 0));
	void SetRotation(float3 vec = float3(0, 0, 0));
	void SetRotation(Quat vec);
	void SetOrientation(btQuaternion bulletQuat);
	void SetScale(float3 vec = float3(0, 0, 0));

	float4x4 GetGlobalTransform() const;
	float4x4 GetLocalTransform() const;
	float3 GetGlobalPosition() const;
	Quat GetLocalRotation() const;
	Quat GetGlobalRotation() const;


	void UpdateTransformsChilds();
	void UpdateGlobalMatrix();
	void UpdateLocalMatrix();

	void ReparentTransform(float4x4 matrix);

	void UpdateBoundingBoxes();

	void UpdateTransformGuizmo(float4x4 matrix);

	float3 GetForward();
	float3 GetUp();
	float3 GetRight();

	float3 GetLocalForward();
	float3 GetLocalUp();
	float3 GetLocalRight();

	float3 GetNormalizeAxis(int i);
	float3 GetNormalizeLocalAxis(int i);

public:

	// local
	float3 translation;
	Quat rotation; // Quaternion rotation
	float3 eulerRot;
	float3 scale;
	//float3* translationPtr;
	//float3* rotationPtr;
	//float3* scalePtr;

	float4x4 mLocalMatrix;

	// global
	float4x4 mGlobalMatrix;

	// Flag to update game object transform
	bool dirty_;

	bool resetPressed;
};