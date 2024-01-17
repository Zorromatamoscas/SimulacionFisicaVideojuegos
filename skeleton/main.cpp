#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include<vector>
#include "ParticleSystem.h"
#include "RigidSystem.h"
using namespace std;

vector<string> texts = {
	"[ CHOQUES DE COCHES ]",
	"Controles jugador 1: wasd",
	"Controles jugador 2: uhjk",
	"Rafael Vilches Hernandez"
	""
};

std::vector<pair<float, float>> textPositions = {
	{180, 450},
	{0, 400},
	{270, 400},
	{10, 10},
	{250,250}
};


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

std::vector<Particle*> myBullets;
ParticleSystem* myParticles=nullptr;
RigidSystem* myRigids=nullptr;
bool endgame = false;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.0f, 0.0f, 0.0f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());

	sceneDesc.gravity = PxVec3(0.0f, -20.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100), gPhysics->createMaterial(0.3f, 0.3f, 0.0f));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	RenderItem* mySuelo = new RenderItem(shape, suelo, Vector4(0.2,0.2,1,1));

	//myParticles = new ParticleSystem();
	myRigids = new RigidSystem(gPhysics, gScene, 100);
	myParticles = new ParticleSystem(myRigids,10);

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	//Se actualizan las balas
	if(myParticles!=nullptr)myParticles->update(t);
	if (myRigids != nullptr)myRigids->update(t);
	if (myRigids->getPlayer1()->getPos().y < -5 && !endgame)
	{
		texts[0] = "PLAYER 2 GANA";
		endgame = true;
		myParticles->celebrate();
	}
	if (myRigids->getPlayer2()->getPos().y < -5 && !endgame)
	{
		texts[0] = "PLAYER 1 GANA";
		endgame = true;
		myParticles->celebrate();
	}

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	//Borra las particulas
	//for (Particle* p : myBullets) delete p;
	if (myParticles != nullptr) delete myParticles;
	if (myRigids != nullptr) delete myRigids;

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	//PX_UNUSED(camera);


	switch(toupper(key))
	{
	case 'W':
		myRigids->getPlayer1()->accelerate();
		break;
	case 'S':
		myRigids->getPlayer1()->deccelerate();
		break;
	case 'D':
		myRigids->getPlayer1()->rotate(true);
		break;
	case 'A':
		myRigids->getPlayer1()->rotate(false);
		break;
	case 'J':
		myRigids->getPlayer2()->accelerate();
		break;
	case 'U':
		myRigids->getPlayer2()->deccelerate();
		break;
	case 'K':
		myRigids->getPlayer2()->rotate(true);
		break;
	case 'H':
		myRigids->getPlayer2()->rotate(false);
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}