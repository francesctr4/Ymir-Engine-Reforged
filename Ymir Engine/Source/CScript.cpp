#include "CScript.h"
#include "External/ImGui/imgui.h"

#include "ModuleEditor.h"
#include "ModuleScene.h"

#include "GameObject.h"
#include "Application.h"
#include "CTransform.h"

//#include "DEJsonSupport.h"		//TODO: IDK si necesitaremos esto
#include <mono/metadata/class.h>
#include <mono/metadata/object.h>
#include <mono/metadata/debug-helpers.h>
#include <filesystem>

#include "External/mmgr/mmgr.h"

CScript* CScript::runningScript = nullptr;
CScript::CScript(GameObject* _gm, const char* scriptName) : Component(_gm, ComponentType::SCRIPT), noGCobject(0), updateMethod(nullptr), startMethod(nullptr), onClickButtonMethod(nullptr), onHoverButtonMethod(nullptr), isStarting(true)
, onCollisionEnterMethod(nullptr), onCollisionExitMethod(nullptr), onCollisionStayMethod(nullptr)
{
	name = scriptName;
	//strcpy(name, scriptName);

	/*External->moduleMono->DebugAllMethods(YMIR_SCRIPTS_NAMESPACE, "GameObject", methods);*/
	LoadScriptData(name);
}

CScript::~CScript()
{
	if (CScript::runningScript == this)
		CScript::runningScript = nullptr;

	mono_gchandle_free(noGCobject);

	for (unsigned int i = 0; i < fields.size(); i++)
	{
		if (fields[i].type == MonoTypeEnum::MONO_TYPE_CLASS && fields[i].fiValue.goValue != nullptr && fields[i].fiValue.goValue->csReferences.size() != 0)
		{
			std::vector<SerializedField*>::iterator ptr = std::find(fields[i].fiValue.goValue->csReferences.begin(), fields[i].fiValue.goValue->csReferences.end(), &fields[i]);
			if (ptr != fields[i].fiValue.goValue->csReferences.end())
				fields[i].fiValue.goValue->csReferences.erase(ptr);

		}
	}

	methods.clear();
	fields.clear();
	name.clear();

}

void CScript::Update()
{
	if (TimeManager::gameTimer.GetState() == TimerState::STOPPED || TimeManager::gameTimer.GetState() == TimerState::PAUSED || updateMethod == nullptr)
		return;

	CScript::runningScript = this; // I really think this is the peak of stupid code, but hey, it works, slow as hell but works.
	MonoObject* exec2 = nullptr;

	if (startMethod && isStarting) {
		mono_runtime_invoke(startMethod, mono_gchandle_get_target(noGCobject), NULL, &exec2);
		isStarting = false;
	}

	MonoObject* exec = nullptr;
	
	mono_runtime_invoke(updateMethod, mono_gchandle_get_target(noGCobject), NULL, &exec);
	
	if (exec != nullptr)
	{
		mono_print_unhandled_exception(exec);
		LOG("[ERROR] Exception detected at Script %s: '%s'", name.c_str(), mono_class_get_name(mono_object_get_class(exec)));
	}

}

void CScript::ReloadComponent() {

	LoadScriptData(name);

}

void CScript::OnRecursiveUIDChange(std::map<uint, GameObject*> gameObjects)
{
	for (size_t i = 0; i < fields.size(); i++)
	{
		if (fields[i].type == MonoTypeEnum::MONO_TYPE_CLASS && strcmp(mono_type_get_name(mono_field_get_type(fields[i].field)), "YmirEngine.GameObject") == 0)
		{
			std::map<uint, GameObject*>::iterator gameObjectIt = gameObjects.find(fields[i].goUID);

			if (gameObjectIt != gameObjects.end())
			{
				if (External->scene->referenceMap.size() > 0)
					External->scene->referenceMap.erase(gameObjectIt->first);

				External->scene->AddToReferenceMap((uint)gameObjectIt->second->UID, &fields[i]);

				fields[i].fiValue.goValue = gameObjectIt->second;
				fields[i].goUID = (uint)gameObjectIt->second->UID;
			}
		}
	}
}

void CScript::OnInspector()
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	bool exists = true;

	ImGui::Checkbox(("##" + std::to_string(UID)).c_str(), &active);
	ImGui::SameLine();

	if (ImGui::CollapsingHeader(("Script##" + std::to_string(UID)).c_str(), &exists, flags))
	{
		ImGui::Text("Script name: %s", name.c_str());
		if (!active) { ImGui::BeginDisabled(); }

		ImGui::Text("Scripting things");

		for (int i = 0; i < fields.size(); i++)
		{
			DropField(fields[i], "GameObject");
		}

		ImGui::Separator();

		for (int i = 0; i < methods.size(); i++)
		{
			ImGui::Text(methods[i].c_str());
		}

		if (!active) { ImGui::EndDisabled(); }
	}

	if (!exists) { mOwner->RemoveComponent(this); }
}

void CScript::DropField(SerializedField& field, const char* dropType)
{
	const char* fieldName = mono_field_get_name(field.field);
	ImGui::PushID(fieldName);

	ImGui::Text(fieldName);
	ImGui::SameLine();

	switch (field.type)
	{
	case MonoTypeEnum::MONO_TYPE_BOOLEAN:
		mono_field_get_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.bValue);
		if (ImGui::Checkbox(field.displayName.c_str(), &field.fiValue.bValue))
			mono_field_set_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.bValue);
		break;

	case MonoTypeEnum::MONO_TYPE_I4:
		mono_field_get_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.iValue);
		if (ImGui::InputInt(field.displayName.c_str(), &field.fiValue.iValue, 1, 10))
			mono_field_set_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.iValue);
		break;

	case MonoTypeEnum::MONO_TYPE_CLASS:

		if (strcmp(mono_type_get_name(mono_field_get_type(field.field)), "YmirEngine.GameObject") != 0)
		{
			ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "The class %s can't be serialized yet", mono_type_get_name(mono_field_get_type(field.field)));
			break;
		}

		ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), (field.fiValue.goValue != nullptr) ? field.fiValue.goValue->name.c_str() : "this");


		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(dropType))
			{
				if (field.fiValue.goValue != nullptr)
					field.fiValue.goValue->RemoveCSReference(&field);

				GameObject* draggedObject = External->editor->draggedGO;
				field.fiValue.goValue = draggedObject;
				field.goUID = draggedObject->UID;

				SetField(field.field, field.fiValue.goValue);
			}
			ImGui::EndDragDropTarget();
		}

		//Hardcodeado para que asigne el GO del objeto del script a todos los campos

		//field.fiValue.goValue = mOwner;
		//SetField(field.field, field.fiValue.goValue);

		//if (ImGui::BeginDragDropTarget())				//TODO: Esto se encarga de hager Drag & Drop el elemento reference
		//{
		///*	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(dropType))
		//	{
		//		field.fiValue.goValue = External->editor->hoveredGO;
		//		SetField(field.field, field.fiValue.goValue);
		//	}*/
		//	ImGui::EndDragDropTarget();
		//}
		break;

	case MonoTypeEnum::MONO_TYPE_R4: {
		//float test = 0.f;
		mono_field_get_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.fValue);
		if (ImGui::InputFloat(field.displayName.c_str(), &field.fiValue.fValue, 0.1f))
			mono_field_set_value(mono_gchandle_get_target(noGCobject), field.field, &field.fiValue.fValue);
		break;
	}

	case MonoTypeEnum::MONO_TYPE_SZARRAY:
	{
		MonoArray* arr = nullptr;
		mono_field_get_value(mono_gchandle_get_target(noGCobject), field.field, &arr);

		MonoClass* arrClass = mono_class_from_name(External->moduleMono->image, YMIR_SCRIPTS_NAMESPACE, field.displayName.c_str());

		
		int arrayLength = mono_array_length(arr);


		for (int i = 0; i < arrayLength; ++i) {
			
			int element = mono_array_get(arr, int, i);

			field.fiValue.arrValue[i] = element;

			if (ImGui::InputInt(field.displayName.c_str(), &element, 1 , 10)) {
				mono_array_set(arr, int, i, element);
				mono_field_set_value(mono_gchandle_get_target(noGCobject), field.field, arr);
			}
		}
		break;
	}
	case MonoTypeEnum::MONO_TYPE_STRING:
	{
		MonoString* str = nullptr;
		mono_field_get_value(mono_gchandle_get_target(noGCobject), field.field, &str);

		char* value = mono_string_to_utf8(str);
		strcpy(field.fiValue.strValue, value);
		mono_free(value);

		if (ImGui::InputText(field.displayName.c_str(), &field.fiValue.strValue[0], 500))
		{
			str = mono_string_new(External->moduleMono->domain, field.fiValue.strValue);
			mono_field_set_value(mono_gchandle_get_target(noGCobject), field.field, str);
			//mono_free(str);
		}
		break;
	}

	default:
		ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), mono_type_get_name(mono_field_get_type(field.field)));
		break;
	}
	//TODO: Update C# field value
	//ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), mono_type_get_name(mono_field_get_type(field.field)));
	ImGui::PopID();
}

void CScript::LoadScriptData(std::string scriptName)
{
	methods.clear();
	fields.clear();

	scriptName.find_first_of('.');
	size_t pos = scriptName.find_last_of('.');

	if (pos != std::string::npos) {
		scriptName = scriptName.substr(0, pos);
	}

	MonoClass* klass = mono_class_from_name(External->moduleMono->image, USER_SCRIPTS_NAMESPACE, scriptName.c_str());

	if (klass == nullptr)
	{
		LOG("Script %s was deleted and can't be loaded", scriptName);
		name = "Missing script reference";
		return;
	}

	External->moduleMono->DebugAllMethods(USER_SCRIPTS_NAMESPACE, scriptName.c_str(), methods);

	noGCobject = mono_gchandle_new(mono_object_new(External->moduleMono->domain, klass), false);
	mono_runtime_object_init(mono_gchandle_get_target(noGCobject));

	MonoClass* goClass = mono_object_get_class(mono_gchandle_get_target(noGCobject));
	uintptr_t ptr = reinterpret_cast<uintptr_t>(this);
	mono_field_set_value(mono_gchandle_get_target(noGCobject), mono_class_get_field_from_name(goClass, "pointer"), &ptr);

	MonoMethodDesc* mdesc = mono_method_desc_new(":Update", false);
	updateMethod = mono_method_desc_search_in_class(mdesc, klass);
	mono_method_desc_free(mdesc);

	MonoMethodDesc* oncDesc = mono_method_desc_new(":OnCollisionStay", false);
	onCollisionStayMethod = mono_method_desc_search_in_class(oncDesc, klass);
	mono_method_desc_free(oncDesc);

	oncDesc = mono_method_desc_new(":OnCollisionEnter", false);
	onCollisionEnterMethod = mono_method_desc_search_in_class(oncDesc, klass);
	mono_method_desc_free(oncDesc);

	oncDesc = mono_method_desc_new(":OnCollisionExit", false);
	onCollisionExitMethod = mono_method_desc_search_in_class(oncDesc, klass);
	mono_method_desc_free(oncDesc);

	oncDesc = mono_method_desc_new(":Start", false);
	startMethod = mono_method_desc_search_in_class(oncDesc, klass);
	mono_method_desc_free(oncDesc);

	MonoMethodDesc* oncBut = mono_method_desc_new(":OnClickButton", false);
	onClickButtonMethod = mono_method_desc_search_in_class(oncBut, klass);
	mono_method_desc_free(oncBut);


	MonoMethodDesc* onhBut = mono_method_desc_new(":OnHoverButton", false);
	onHoverButtonMethod = mono_method_desc_search_in_class(onhBut, klass);
	mono_method_desc_free(onhBut);




	MonoClass* baseClass = mono_class_get_parent(klass);
	if (baseClass != nullptr)
		External->moduleMono->DebugAllFields(mono_class_get_name(baseClass), fields, mono_gchandle_get_target(noGCobject), this, mono_class_get_namespace(baseClass));

	External->moduleMono->DebugAllFields(scriptName.c_str(), fields, mono_gchandle_get_target(noGCobject), this, mono_class_get_namespace(goClass));
}

void CScript::CollisionStayCallback(bool isTrigger, GameObject* collidedGameObject)
{
	void* params[1];

	if (collidedGameObject != nullptr)
	{
		params[0] = External->moduleMono->GoToCSGO(collidedGameObject);

		if (onCollisionStayMethod != nullptr)
			mono_runtime_invoke(onCollisionStayMethod, mono_gchandle_get_target(noGCobject), params, NULL);

		if (isTrigger)
		{
			if (onTriggerEnterMethod != nullptr)
				mono_runtime_invoke(onCollisionStayMethod, mono_gchandle_get_target(noGCobject), params, NULL);
		}
	}
}

void CScript::CollisionEnterCallback(bool isTrigger, GameObject* collidedGameObject)
{
	void* params[1];
	if (collidedGameObject != nullptr)
	{
		params[0] = External->moduleMono->GoToCSGO(collidedGameObject);

		if (onCollisionEnterMethod != nullptr)
			mono_runtime_invoke(onCollisionEnterMethod, mono_gchandle_get_target(noGCobject), params, NULL);

		if (isTrigger)
		{
			if (onTriggerEnterMethod != nullptr)
				mono_runtime_invoke(onCollisionEnterMethod, mono_gchandle_get_target(noGCobject), params, NULL);
		}
	}
}

void CScript::CollisionExitCallback(bool isTrigger, GameObject* collidedGameObject)
{
	void* params[1];
	if (collidedGameObject != nullptr)
	{
		params[0] = External->moduleMono->GoToCSGO(collidedGameObject);

		if (onCollisionExitMethod != nullptr)
		{
			mono_runtime_invoke(onCollisionExitMethod, mono_gchandle_get_target(noGCobject), params, NULL);
			// Restablecer firstCollision aqui despues de salir de la colision
		}

		if (isTrigger)
		{
			if (onCollisionExitMethod != nullptr)
				mono_runtime_invoke(onCollisionExitMethod, mono_gchandle_get_target(noGCobject), params, NULL);
		}


	}
}

void CScript::OnClickButton() {

	if (onClickButtonMethod != nullptr) {

		mono_runtime_invoke(onClickButtonMethod, mono_gchandle_get_target(noGCobject), NULL, NULL);
	}
}

void CScript::OnHoverButton() {

	if (onHoverButtonMethod != nullptr) {

		mono_runtime_invoke(onHoverButtonMethod, mono_gchandle_get_target(noGCobject), NULL, NULL);
	}
}

void CScript::SetField(MonoClassField* field, GameObject* value)
{
	mono_field_set_value(mono_gchandle_get_target(noGCobject), field, External->moduleMono->GoToCSGO(value));
}