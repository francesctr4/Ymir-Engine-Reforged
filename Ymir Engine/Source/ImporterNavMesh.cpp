#include "ImporterNavMesh.h"
#include "Globals.h"
#include "Application.h"
#include "RecastNavigation/InputGeom.h"
#include "ModuleFileSystem.h"

#include <vcruntime_string.h>

#include "External/mmgr/mmgr.h"

const char* ImporterNavMesh::Save(const char* assets_path, dtNavMesh* navMesh, BuildSettings& buildSettings, uint UID)
{
	const char* path = assets_path;
	if (!navMesh)
		return "";

	FILE* fp = fopen(assets_path, "wb");
	if (!fp)
		return "";

	//Store all geometry data
	fwrite(&buildSettings, sizeof(BuildSettings), 1, fp);

	// Store header.
	NavMeshSetHeader header;
	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < navMesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = navMesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.params, navMesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < navMesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = navMesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = navMesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);

		fwrite(tile->data, tile->dataSize, 1, fp);
	}

	fclose(fp);

	return path;
}

dtNavMesh* ImporterNavMesh::Load(const char* path, BuildSettings& buildSettings)
{
	FILE* fp = fopen(path, "rb");
	if (!fp)
		return nullptr;

	//Read Geometry Data
	fread(&buildSettings, sizeof(BuildSettings), 1, fp);

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		return nullptr;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return nullptr;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return nullptr;
	}

	dtNavMesh* navMesh = dtAllocNavMesh();
	if (!navMesh)
	{
		fclose(fp);
		return nullptr;
	}
	dtStatus status = navMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return nullptr;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
			return nullptr;

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
			return nullptr;

		navMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return navMesh;
}

GeometryData::GeometryData()
{
}

GeometryData::GeometryData(InputGeom* geometry)
{
	bMin[0] = geometry->m_meshBMin[0];
	bMin[1] = geometry->m_meshBMin[1];
	bMin[2] = geometry->m_meshBMin[2];

	bMax[0] = geometry->m_meshBMax[0];
	bMax[1] = geometry->m_meshBMax[1];
	bMax[2] = geometry->m_meshBMax[2];
}
