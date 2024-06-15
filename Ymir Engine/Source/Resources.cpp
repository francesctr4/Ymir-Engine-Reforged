#include "Resources.h"
#include "ModuleResourceManager.h"

#include "External/mmgr/mmgr.h"

Resource::Resource()
{
	this->type = ResourceType::UNKNOWN;
	this->UID = 0;

	this->referenceCount = 0;

	this->isLoaded = false;
}

Resource::Resource(uint UID, ResourceType type)
{
	this->type = type;
	this->UID = UID;

	this->referenceCount = 0;

	this->isLoaded = false;
}

Resource::~Resource()
{
	this->assetsFilePath.clear();
	this->libraryFilePath.clear();

	this->type = ResourceType::UNKNOWN;
	this->UID = 0;

	this->referenceCount = 0;

	this->isLoaded = false;
}

ResourceType Resource::GetType() const
{
	return this->type;
}

uint Resource::GetUID() const
{
	return this->UID;
}

void Resource::SetAssetsFilePath(const std::string& newPath)
{
	this->assetsFilePath = newPath;
}

void Resource::SetLibraryFilePath(const std::string& newPath)
{
	this->libraryFilePath = newPath;
}

std::string Resource::GetAssetsFilePath() const
{
	return this->assetsFilePath;
}

std::string Resource::GetLibraryFilePath() const
{
	return this->libraryFilePath;
}

uint Resource::GetReferenceCount() const
{
	return this->referenceCount;
}

void Resource::IncreaseReferenceCount()
{
	this->referenceCount++;
}

void Resource::DecreaseReferenceCount()
{
	this->referenceCount--;
}

bool Resource::IsLoadedInMemory() const
{
	return isLoaded;
}