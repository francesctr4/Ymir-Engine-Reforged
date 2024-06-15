#include "Particle.h"

#include "External/mmgr/mmgr.h"

Particle::Particle()
{
	position = { 0,0,0 };
	worldRotation = { 0,0,0,0 };
	directionRotation = Quat::identity;
	size = { 1,1,1 };
	velocity = { 0,0,0,0 };

	lifetime = 0.0f;
	oneOverMaxLifetime = 1.0f / 60;

	diesByDistance = false;
	initialPosition = {0,0,0}; //This is for killing by distance
	distanceLimit = 0.0f;
	
	color = { 255,255,255,255 };
	pTexture = nullptr;
}

Particle::~Particle()
{
	//if (pTexture != nullptr) { pTexture->UnloadFromMemory(); }
	if (pTexture != nullptr) 
	{
		//RELEASE(pTexture); //Hacer esto peta.
		pTexture = nullptr;
	}
}
