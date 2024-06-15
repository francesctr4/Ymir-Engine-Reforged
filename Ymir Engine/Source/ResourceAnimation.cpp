#include "ResourceAnimation.h"
#include "ImporterAnimation.h"

#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/Importer.hpp"
#include <functional>
#include "log.h"

#include "External/mmgr/mmgr.h"

ResourceAnimation::ResourceAnimation(uint UID) : Resource(UID, ResourceType::ANIMATION) {
	
	name = "";

	isPlaying = false;
	loop = false;
	pingPong = false;
	backwards = false;
	easeIn = false;
	easeOut = false;
	speed = 1;

	currentTime = 0.0f;

	resetToZero = true;

	backwardsAux = true;
	pingPongAux = true;
	pingPongBackwardsAux = true;
	easeInSpeed = 1;
	easeOutSpeed = 1;
	easeInMultiplier = 1.025f;
	easeOutMultiplier = 0.995f;
	duration = 0.0f;
	ticksPerSecond = 0.0f;

}

ResourceAnimation::~ResourceAnimation()
{
	
}

bool ResourceAnimation::LoadInMemory()
{
	ImporterAnimation::Load(this->GetLibraryFilePath().c_str(), this);
	LOG("Loaded Animation %s succesfully", name.c_str());

	return true;
}

bool ResourceAnimation::UnloadFromMemory()
{
	blendMap.clear();
	boneInfoMap.clear();
	ClearVec(bones);
	rootNode.CleanUp();

	return true;
}

Bone* ResourceAnimation::FindBone(std::string& name)
{
	// iterator 
	std::_Vector_iterator iter = std::find_if(bones.begin(), bones.end(),
		[&](Bone& bone) {
			return bone.GetName() == name;
		});

	if (iter == bones.end()) {
		return nullptr;
	}
	else {
		return &(*iter);
	}
}

void AssimpNodeData::CleanUp()
{
	for (int i = 0; i < childrenCount; i++) {
		children[i].CleanUp();
	}
	ClearVec(children);
}
