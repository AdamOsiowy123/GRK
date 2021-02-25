#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <cstdio>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Sun.h"
#include "Ship.h"
#include "Skybox.h"
#include "Ufo.h"
#include "ParticleEffect.h"
#include <memory>
#include "Physics.h"
#include "Object.h"

/// PHYSICS SHIP
Ship* ship;
PxRigidDynamic* shipBody = nullptr;
PxMaterial* shipMaterial = nullptr;
float F_front = 0.0f;
float F_side = 0.0f;
float F_qe = 0.0f;
float F_zc = 0.0f;

Ship* rocket;
PxRigidDynamic* rocketBody = nullptr;
PxMaterial* rocketMaterial = nullptr;
bool isRocketDestroyed = false;
PxFixedJoint* joint;
/// PHYSICS SHIP

std::vector<physx::PxActor*> actorsToRemove;

/// PHYSICS ASTEROIDs
std::vector<Asteroid*> asteroids;
std::vector<PxRigidDynamic*> asteroidsBody;
PxMaterial* asteroidMaterial = nullptr;
/// PHYSICS ASTEROIDs

/// PHYSICS SUN
Sun* sun1;
Sun* sun2;
PxRigidDynamic* sun1Body = nullptr;
PxRigidDynamic* sun2Body = nullptr;
PxMaterial* sunMaterial = nullptr;
/// PHYSICS SUN

/// PHYSICS PLANETs
Planet* mercury;
PxRigidDynamic* mercuryBody;
Planet* mercury2;
PxRigidDynamic* mercuryBody2;
Planet* venus;
PxRigidDynamic* venusBody;
Planet* venus2;
PxRigidDynamic* venusBody2;
Planet* earth;
PxRigidDynamic* earthBody;
Planet* earth2;
PxRigidDynamic* earthBody2;
Planet* mars;
PxRigidDynamic* marsBody;
Planet* mars2;
PxRigidDynamic* marsBody2;
Planet* jupiter;
PxRigidDynamic* jupiterBody;
Planet* jupiter2;
PxRigidDynamic* jupiterBody2;
Planet* saturn;
PxRigidDynamic* saturnBody;
Planet* saturn2;
PxRigidDynamic* saturnBody2;
Planet* uranus;
PxRigidDynamic* uranusBody;
Planet* uranus2;
PxRigidDynamic* uranusBody2;
Planet* neptune;
PxRigidDynamic* neptuneBody;
Planet* neptune2;
PxRigidDynamic* neptuneBody2;
Planet* moon;
PxRigidDynamic* moonBody;
Planet* moon2;
PxRigidDynamic* moonBody2;
PxMaterial* planetMaterial = nullptr;
/// PHYSICS PLANETs

/// PHYSICS UFO
Ufo* ufo;
PxRigidDynamic* ufoBody = nullptr;
PxMaterial* ufoMaterial = nullptr;
/// PHYSICS UFO

std::vector<PxRigidDynamic*> notDestroyable;

GLuint programParticle;
GLuint programSkybox;
GLuint programColor;
GLuint programTexture;
GLuint programSun;
GLuint programSight;
GLuint programBump;
GLuint programUfo;

Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
obj::Model saturnModel;
obj::Model planeModel;
obj::Model ufoModel;
obj::Model rocketModel;

glm::vec3 cameraPos;
glm::vec3 cameraDir; // Wektor "do przodu" kamery
glm::vec3 cameraSide; // Wektor "w bok" kamery
float cameraAngle = 0;

glm::mat4 cameraMatrix, perspectiveMatrix, rocketMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

glm::vec3 sunPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 sunPos2 = glm::vec3(1000.0f, -800.0f, -500.0f);
glm::vec3 sunColor = glm::vec3(1.0f, 0.5f, 0.2f);

glm::quat rotation = glm::quat(0, 0, 0, 0);
float shipAngle = glm::radians(180.0f);
float frustumScale = 1.0f;

glm::vec3 collisionCoords;

GLuint textureAsteroid;
GLuint textureAsteroid_normals;
GLuint textureJupiter;
GLuint textureMars;
GLuint textureVenus;
GLuint textureMercury;
GLuint textureEarth;
GLuint textureSaturn;
GLuint textureUranus;
GLuint textureNeptune;
GLuint textureSun;
GLuint textureUfo;
std::vector<GLuint> textureParticle;

glm::vec3 mercuryTranslate = glm::vec3(2000.0f);
glm::vec3 mercury2Translate = glm::vec3(200.0f);
glm::vec3 venusTranslate = glm::vec3(300.0f);
glm::vec3 venus2Translate = glm::vec3(400.0f);
glm::vec3 earthTranslate = glm::vec3(500.0f);
glm::vec3 earth2Translate = glm::vec3(600.0f);
glm::vec3 marsTranslate = glm::vec3(700.0f);
glm::vec3 mars2Translate = glm::vec3(800.0f);
glm::vec3 jupiterTranslate = glm::vec3(900.0f);
glm::vec3 jupiter2Translate = glm::vec3(1000.0f);
glm::vec3 saturnTranslate = glm::vec3(1100.0f);
glm::vec3 saturn2Translate = glm::vec3(1200.0f);
glm::vec3 uranusTranslate = glm::vec3(1300.0f);
glm::vec3 uranus2Translate = glm::vec3(1400.0f);
glm::vec3 neptuneTranslate = glm::vec3(1500.0f);
glm::vec3 neptune2Translate = glm::vec3(1600.0f);
glm::vec3 moonTranslate = glm::vec3(1700.0f);
glm::vec3 moon2Translate = glm::vec3(1800.0f);

GLuint textureId;

glm::vec3 wspolrzedne[400];
glm::vec3 wspolrzedneUfo[4] = {
	glm::vec3(120.0f), glm::vec3(125.0f), glm::vec3(130.0f), glm::vec3(135.0f)
};
glm::vec3 wektor[4] = {
	glm::vec3(120.0f), glm::vec3(125.0f), glm::vec3(130.0f), glm::vec3(135.0f)
};

float roznicaX, roznicaY, roznicaZ;
float ostatniX = 300;
float ostatniY = 300;
float ostatniZ = 0;
int counter = 0;
float lastTimeF = -1.0f;
glm::quat lastRotation;
glm::mat4 lastCameraMatrix;
glm::mat4 particleMatrix;

bool mouseKeyDown = false;
bool freeLook = false;

float appLoadingTime;
float timeF;
float whenShot = 0.0f;

std::vector<ParticleEffect*> particleEffects;

float swidth = 650.0f, sheight = 650.0f;

bool isObjectDestroyable(PxRigidActor& actor) {
	bool result = std::binary_search(notDestroyable.begin(), notDestroyable.end(), &actor);
	return !result;
}

//COLLISIONS
static PxFilterFlags simulationFilterShader(PxFilterObjectAttributes attributes0,
	PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	pairFlags =
		PxPairFlag::eCONTACT_DEFAULT | // default contact processing
		PxPairFlag::eNOTIFY_CONTACT_POINTS | // contact points will be available in onContact callback
		PxPairFlag::eNOTIFY_TOUCH_FOUND |
		PxPairFlag::eNOTIFY_TOUCH_PERSISTS;// onContact callback will be called for this pair

	return physx::PxFilterFlag::eDEFAULT;
}
class SimulationEventCallback : public PxSimulationEventCallback
{
public:
	void onContact(const PxContactPairHeader& pairHeader,
		const PxContactPair* pairs, PxU32 nbPairs)
	{
		for (PxU32 i = 0; i < nbPairs; i++) {
			const PxContactPair& cp = pairs[i];
			PxContactPairPoint* v;
			v = new PxContactPairPoint[sizeof(PxContactPairPoint)];
			for (PxU32 j = 0; j < cp.extractContacts(v, sizeof(v)); j++) {
				std::cout << "QQQQQQQQQQQ" << std::endl;
				std::cout << "x:" << v[j].position.x << " y:" << v[j].position.y << " z:" << v[j].position.z << std::endl;
				collisionCoords.x = v[j].position.x + 8.f;
				collisionCoords.y = v[j].position.y - 15.0f;
				collisionCoords.z = v[j].position.z + 3.f;
				particleMatrix = ship->getMatrix();
				particleMatrix[3][0] = collisionCoords.x;
				particleMatrix[3][1] = collisionCoords.y;
				particleMatrix[3][2] = collisionCoords.z;
				if (pairHeader.actors[0] == rocketBody || pairHeader.actors[1] == rocketBody) {
					std::cout << "RAKIETA UDERZYLA" << std::endl;
					if (isObjectDestroyable(*pairHeader.actors[0])) {
						actorsToRemove.emplace_back(pairHeader.actors[0]);
					}
					if (isObjectDestroyable(*pairHeader.actors[1])) {
						actorsToRemove.emplace_back(pairHeader.actors[1]);
					}
					isRocketDestroyed = true;
				}
				particleEffects.emplace_back(new ParticleEffect(programParticle, 1, 0.0015625f, textureParticle, glm::vec3(0, 0, 0), glm::vec3((rand() % 10 - 5) * 100.0f, (rand() % 10 - 5) * 100.0f, 0.0f)));
				std::cout << pairHeader.actors[0] << "  " << pairHeader.actors[1] << std::endl;
				std::cout << "QQQQQQQQQQQ" << std::endl;
			}
			delete [] v;
		}
	}

	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {}
	virtual void onWake(PxActor** actors, PxU32 count) {}
	virtual void onSleep(PxActor** actors, PxU32 count) {}
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) {}
	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {}
};
SimulationEventCallback simulationEventCallback;
//COLLISIONS

/// SCENE
Physics scene(0 /* gravity (m/s^2) */, simulationFilterShader,
	&simulationEventCallback);
const double physicsStepTime = 1.f / 60.f;
double physicsTimeToProcess = 0;
/// SCENE

void initPhysicsScene()
{
	shipBody = scene.physics->createRigidDynamic(PxTransform(300,2,300));
	shipMaterial = scene.physics->createMaterial(1, 1, 0.6);
	PxShape* shipShape = scene.physics->createShape(PxBoxGeometry(0.5, 0.5, 0.5), *shipMaterial);
	shipBody->attachShape(*shipShape);
	shipShape->release();
	shipBody->userData = ship;
	scene.scene->addActor(*shipBody);
	notDestroyable.emplace_back(shipBody);

	for (int i=0; i < 280; i++) {
		asteroidsBody.emplace_back(scene.physics->createRigidDynamic(PxTransform(wspolrzedne[i].x,wspolrzedne[i].y,wspolrzedne[i].z)));
		asteroidMaterial = scene.physics->createMaterial(1, 1, 0.6);
		PxShape* asteroidShape = scene.physics->createShape(PxSphereGeometry(1), *asteroidMaterial);
		asteroidsBody[i]->attachShape(*asteroidShape);
		asteroidShape->release();
		asteroidsBody[i]->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		asteroidsBody[i]->userData = asteroids[i];
		scene.scene->addActor(*asteroidsBody[i]);
	}

	sun1Body = scene.physics->createRigidDynamic(PxTransform(sunPos.x, sunPos.y, sunPos.z));
	sunMaterial = scene.physics->createMaterial(1, 1, 0.6);
	PxShape* sun1Shape = scene.physics->createShape(PxSphereGeometry(117), *sunMaterial);
	sun1Body->attachShape(*sun1Shape);
	sun1Shape->release();
	sun1Body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	sun1Body->userData = sun1;
	scene.scene->addActor(*sun1Body);
	notDestroyable.emplace_back(sun1Body);
	sun2Body = scene.physics->createRigidDynamic(PxTransform(sunPos2.x, sunPos2.y, sunPos2.z));
	PxShape* sun2Shape = scene.physics->createShape(PxSphereGeometry(117), *sunMaterial);
	sun2Body->attachShape(*sun2Shape);
	sun2Shape->release();
	sun2Body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	sun2Body->userData = sun2;
	scene.scene->addActor(*sun2Body);
	notDestroyable.emplace_back(sun2Body);

	mercuryBody = scene.physics->createRigidDynamic(PxTransform(mercuryTranslate.x, mercuryTranslate.y, mercuryTranslate.z));
	planetMaterial = scene.physics->createMaterial(1, 1, 0.6);
	PxShape* mercuryShape = scene.physics->createShape(PxSphereGeometry(9.6), *planetMaterial);
	mercuryBody->attachShape(*mercuryShape);
	mercuryShape->release();
	mercuryBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	mercuryBody->userData = mercury;
	scene.scene->addActor(*mercuryBody);
	notDestroyable.emplace_back(mercuryBody);

	mercuryBody2 = scene.physics->createRigidDynamic(PxTransform(mercury2Translate.x, mercury2Translate.y, mercury2Translate.z));
	PxShape* mercury2Shape = scene.physics->createShape(PxSphereGeometry(9.6), *planetMaterial);
	mercuryBody2->attachShape(*mercury2Shape);
	mercury2Shape->release();
	mercuryBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	mercuryBody2->userData = mercury2;
	scene.scene->addActor(*mercuryBody2);
	notDestroyable.emplace_back(mercuryBody2);

	venusBody = scene.physics->createRigidDynamic(PxTransform(venusTranslate.x, venusTranslate.y, venusTranslate.z));
	PxShape* venusShape = scene.physics->createShape(PxSphereGeometry(18.15), *planetMaterial);
	venusBody->attachShape(*venusShape);
	venusShape->release();
	venusBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	venusBody->userData = venus;
	scene.scene->addActor(*venusBody);
	notDestroyable.emplace_back(venusBody);

	venusBody2 = scene.physics->createRigidDynamic(PxTransform(venus2Translate.x, venus2Translate.y, venus2Translate.z));
	PxShape* venus2Shape = scene.physics->createShape(PxSphereGeometry(18.15), *planetMaterial);
	venusBody2->attachShape(*venus2Shape);
	venus2Shape->release();
	venusBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	venusBody2->userData = venus2;
	scene.scene->addActor(*venusBody2);
	notDestroyable.emplace_back(venusBody2);

	earthBody = scene.physics->createRigidDynamic(PxTransform(earthTranslate.x, earthTranslate.y, earthTranslate.z));
	PxShape* earthShape = scene.physics->createShape(PxSphereGeometry(19.05), *planetMaterial);
	earthBody->attachShape(*earthShape);
	earthShape->release();
	earthBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	earthBody->userData = earth;
	scene.scene->addActor(*earthBody);
	notDestroyable.emplace_back(earthBody);

	earthBody2 = scene.physics->createRigidDynamic(PxTransform(earth2Translate.x, earth2Translate.y, earth2Translate.z));
	PxShape* earth2Shape = scene.physics->createShape(PxSphereGeometry(19.05), *planetMaterial);
	earthBody2->attachShape(*earth2Shape);
	earth2Shape->release();
	earthBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	earthBody2->userData = earth2;
	scene.scene->addActor(*earthBody2);
	notDestroyable.emplace_back(earthBody2);

	marsBody = scene.physics->createRigidDynamic(PxTransform(marsTranslate.x, marsTranslate.y, marsTranslate.z));
	PxShape* marsShape = scene.physics->createShape(PxSphereGeometry(13.6), *planetMaterial);
	marsBody->attachShape(*marsShape);
	marsShape->release();
	marsBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	marsBody->userData = mars;
	scene.scene->addActor(*marsBody);
	notDestroyable.emplace_back(marsBody);

	marsBody2 = scene.physics->createRigidDynamic(PxTransform(mars2Translate.x, mars2Translate.y, mars2Translate.z));
	PxShape* mars2Shape = scene.physics->createShape(PxSphereGeometry(13.6), *planetMaterial);
	marsBody2->attachShape(*mars2Shape);
	mars2Shape->release();
	marsBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	marsBody2->userData = mars2;
	scene.scene->addActor(*marsBody2);
	notDestroyable.emplace_back(marsBody2);

	jupiterBody = scene.physics->createRigidDynamic(PxTransform(jupiterTranslate.x, jupiterTranslate.y, jupiterTranslate.z));
	PxShape* jupiterShape = scene.physics->createShape(PxSphereGeometry(49.7), *planetMaterial);
	jupiterBody->attachShape(*jupiterShape);
	jupiterShape->release();
	jupiterBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	jupiterBody->userData = jupiter;
	scene.scene->addActor(*jupiterBody);
	notDestroyable.emplace_back(jupiterBody);

	jupiterBody2 = scene.physics->createRigidDynamic(PxTransform(jupiter2Translate.x, jupiter2Translate.y, jupiter2Translate.z));
	PxShape* jupiter2Shape = scene.physics->createShape(PxSphereGeometry(49.7), *planetMaterial);
	jupiterBody2->attachShape(*jupiter2Shape);
	jupiter2Shape->release();
	jupiterBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	jupiterBody2->userData = jupiter2;
	scene.scene->addActor(*jupiterBody2);
	notDestroyable.emplace_back(jupiterBody2);

	saturnBody = scene.physics->createRigidDynamic(PxTransform(saturnTranslate.x, saturnTranslate.y, saturnTranslate.z));
	PxShape* saturnShape = scene.physics->createShape(PxSphereGeometry(85.0), *planetMaterial);
	saturnBody->attachShape(*saturnShape);
	saturnShape->release();
	saturnBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	saturnBody->userData = saturn;
	scene.scene->addActor(*saturnBody);
	notDestroyable.emplace_back(saturnBody);

	saturnBody2 = scene.physics->createRigidDynamic(PxTransform(saturn2Translate.x, saturn2Translate.y, saturn2Translate.z));
	PxShape* saturn2Shape = scene.physics->createShape(PxSphereGeometry(85.0), *planetMaterial);
	saturnBody2->attachShape(*saturn2Shape);
	saturn2Shape->release();
	saturnBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	saturnBody2->userData = saturn2;
	scene.scene->addActor(*saturnBody2);
	notDestroyable.emplace_back(saturnBody2);

	uranusBody = scene.physics->createRigidDynamic(PxTransform(uranusTranslate.x, uranusTranslate.y, uranusTranslate.z));
	PxShape* uranusShape = scene.physics->createShape(PxSphereGeometry(40.0), *planetMaterial);
	uranusBody->attachShape(*uranusShape);
	uranusShape->release();
	uranusBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	uranusBody->userData = uranus;
	scene.scene->addActor(*uranusBody);
	notDestroyable.emplace_back(uranusBody);

	uranusBody2 = scene.physics->createRigidDynamic(PxTransform(uranus2Translate.x, uranus2Translate.y, uranus2Translate.z));
	PxShape* uranus2Shape = scene.physics->createShape(PxSphereGeometry(40.0), *planetMaterial);
	uranusBody2->attachShape(*uranus2Shape);
	uranus2Shape->release();
	uranusBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	uranusBody2->userData = uranus2;
	scene.scene->addActor(*uranusBody2);
	notDestroyable.emplace_back(uranusBody2);

	neptuneBody = scene.physics->createRigidDynamic(PxTransform(neptuneTranslate.x, neptuneTranslate.y, neptuneTranslate.z));
	PxShape* neptuneShape = scene.physics->createShape(PxSphereGeometry(39.0), *planetMaterial);
	neptuneBody->attachShape(*neptuneShape);
	neptuneShape->release();
	neptuneBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	neptuneBody->userData = neptune;
	scene.scene->addActor(*neptuneBody);
	notDestroyable.emplace_back(neptuneBody);

	neptuneBody2 = scene.physics->createRigidDynamic(PxTransform(neptune2Translate.x, neptune2Translate.y, neptune2Translate.z));
	PxShape* neptune2Shape = scene.physics->createShape(PxSphereGeometry(39.0), *planetMaterial);
	neptuneBody2->attachShape(*neptune2Shape);
	neptune2Shape->release();
	neptuneBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	neptuneBody2->userData = neptune2;
	scene.scene->addActor(*neptuneBody2);
	notDestroyable.emplace_back(neptuneBody2);

	moonBody = scene.physics->createRigidDynamic(PxTransform(moonTranslate.x, moonTranslate.y, moonTranslate.z));
	PxShape* moonShape = scene.physics->createShape(PxSphereGeometry(4.75), *planetMaterial);
	moonBody->attachShape(*moonShape);
	moonShape->release();
	moonBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	moonBody->userData = moon;
	scene.scene->addActor(*moonBody);
	notDestroyable.emplace_back(moonBody);

	moonBody2 = scene.physics->createRigidDynamic(PxTransform(moon2Translate.x, moon2Translate.y, moon2Translate.z));
	PxShape* moon2Shape = scene.physics->createShape(PxSphereGeometry(4.75), *planetMaterial);
	moonBody2->attachShape(*moon2Shape);
	moon2Shape->release();
	moonBody2->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	moonBody2->userData = moon2;
	scene.scene->addActor(*moonBody2);
	notDestroyable.emplace_back(moonBody2);

	ufoBody = scene.physics->createRigidDynamic(PxTransform(10000,10000,10000));
	ufoMaterial = scene.physics->createMaterial(1, 1, 0.6);
	PxShape* ufoShape = scene.physics->createShape(PxSphereGeometry(5), *ufoMaterial);
	ufoBody->attachShape(*ufoShape);
	ufoShape->release();
	ufoBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	ufoBody->userData = ufo;
	scene.scene->addActor(*ufoBody);

	rocketBody = scene.physics->createRigidDynamic(PxTransform(300,1,300));
	rocketMaterial = scene.physics->createMaterial(1, 1, 0.6);
	PxShape* rocketShape = scene.physics->createShape(PxCapsuleGeometry(0.1, 0.2), *rocketMaterial);
	rocketBody->attachShape(*rocketShape);
	rocketShape->release();
	rocketBody->userData = rocket;
	PxRigidBodyExt::updateMassAndInertia(*rocketBody, 0.1);
	scene.scene->addActor(*rocketBody);

	joint = PxFixedJointCreate(*scene.physics, shipBody, PxTransform(0, -0.005, 0), rocketBody, PxTransform(0, 0.005, 0));
}

void updateTransforms()
{
	// Here we retrieve the current transforms of the objects from the physical simulation.
	auto actorFlags = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC;
	PxU32 nbActors = scene.scene->getNbActors(actorFlags);
	if (nbActors)
	{
		std::vector<PxRigidActor*> actors(nbActors);
		scene.scene->getActors(actorFlags, (PxActor**)&actors[0], nbActors);
		for (auto actor : actors)
		{
			// We use the userData of the objects to set up the model matrices
			// of proper renderables.
			if (!actor->userData) continue;
			Object* obj = (Object*)actor->userData;

			// get world matrix of the object (actor)
			PxMat44 transform = actor->getGlobalPose();
			auto& c0 = transform.column0;
			auto& c1 = transform.column1;
			auto& c2 = transform.column2;
			auto& c3 = transform.column3;

			// set up the model matrix used for the rendering
			obj->setMatrix(glm::mat4(
				c0.x, c0.y, c0.z, c0.w,
				c1.x, c1.y, c1.z, c1.w,
				c2.x, c2.y, c2.z, c2.w,
				c3.x, c3.y, c3.z, c3.w));
		}
	}
}

void removeInActiveActors(){
	for (auto actor : actorsToRemove) {
		Object* obj = (Object*)actor->userData;
		obj->setMatrix(glm::mat4(0));
		scene.scene->removeActor(*actor);
	}
	actorsToRemove.clear();
}

void text(int x, int y, std::string text, int size)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, swidth, 0, sheight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	void* siz = GLUT_BITMAP_HELVETICA_18;
	if (size == 18) siz = GLUT_BITMAP_HELVETICA_18;
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(siz, text[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void shoot() {
	if (joint) {
		whenShot = timeF;
		joint->release();
		PxRigidBodyExt::addLocalForceAtLocalPos(*rocketBody, PxVec3(0, 0, -10.0), PxVec3(0, 0, 0));
		PxRigidBodyExt::addLocalForceAtLocalPos(*rocketBody, PxVec3(0, -1.0, 0), PxVec3(0, 0, -0.1));
		joint = nullptr;
	}
}

void reloadRocket(){
	if (isRocketDestroyed || (timeF-whenShot>5 && whenShot > 0)) {
		rocketBody = scene.physics->createRigidDynamic(PxTransform(shipBody->getGlobalPose()));
		rocketMaterial = scene.physics->createMaterial(1, 1, 0.6);
		PxShape* rocketShape = scene.physics->createShape(PxCapsuleGeometry(0.1, 0.2), *rocketMaterial);
		rocketBody->attachShape(*rocketShape);
		rocketShape->release();
		rocketBody->userData = rocket;
		PxRigidBodyExt::updateMassAndInertia(*rocketBody, 0.1);
		scene.scene->addActor(*rocketBody);

		joint = PxFixedJointCreate(*scene.physics, shipBody, PxTransform(0, -0.005, 0), rocketBody, PxTransform(0, 0.005, 0));
		isRocketDestroyed = false;
		whenShot = 0;
	}
}

void lowerForces() {
	F_side = round(F_side * 100.0f) / 100.0f;
	F_zc = round(F_zc * 100.0f) / 100.0f;
	if (F_front > 0) {
		F_front -= 0.5f;
	}
	else if (F_front == 0) {
	}
	else {
		F_front += 0.5f;
	}
	if (F_side > 0) {
		F_side -= 0.1f;
	}
	else if (F_side == 0) {
	}
	else if (F_side < 0) {
		F_side += 0.1f;
	}
	if (F_qe > 0) {
		F_qe -= 0.5f;
	}
	else if (F_qe == 0) {
	}
	else {
		F_qe += 0.5f;
	}
	if (F_zc > 0) {
		F_zc -= 0.05f;
	}
	else if (F_zc == 0) {
	}
	else {
		F_zc += 0.05f;
	}
}

glm::vec3 predictMove() {
	PxTransform pxtr = shipBody->getGlobalPose();
	glm::vec3 ship_pos = glm::vec3(pxtr.p.x, pxtr.p.y, pxtr.p.z);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - appLoadingTime;
	int sekundaRuchu = int(floorf(time));
	float u³amekSekundy = time - sekundaRuchu;
	wektor[0] = wspolrzedneUfo[(sekundaRuchu - 1) % 4];
	wektor[1] = wspolrzedneUfo[(sekundaRuchu) % 4];
	wektor[2] = wspolrzedneUfo[(sekundaRuchu + 1) % 4];
	wektor[3] = wspolrzedneUfo[(sekundaRuchu + 2) % 4];
	glm::vec3 catmull = glm::catmullRom(wektor[0], wektor[1], wektor[2], wektor[3], u³amekSekundy);
	wspolrzedneUfo[0] = wspolrzedneUfo[1];
	wspolrzedneUfo[1] = wspolrzedneUfo[2];
	wspolrzedneUfo[2] = wspolrzedneUfo[3];
	glm::vec3 newUfo3 = wspolrzedneUfo[3] + glm::sphericalRand(0.7f);
	bool isCloser = glm::length(newUfo3 - (ship_pos)) < glm::length(wspolrzedneUfo[3] - (ship_pos));
	bool isSun = glm::length(newUfo3 - sunPos) < 140.0f || glm::length(newUfo3 - sunPos2) < 140.0f;
	bool isPlanet = glm::length(newUfo3 - mercuryTranslate) < 19.2f || glm::length(newUfo3 - mercury2Translate) < 19.2f || glm::length(newUfo3 - venusTranslate) < 36.3f
		|| glm::length(newUfo3 - venus2Translate) < 36.3f || glm::length(newUfo3 - earthTranslate) < 78.1f || glm::length(newUfo3 - earth2Translate) < 78.1f
		|| glm::length(newUfo3 - marsTranslate) < 27.2f || glm::length(newUfo3 - mars2Translate) < 38.1f || glm::length(newUfo3 - jupiterTranslate) < 100.0f
		|| glm::length(newUfo3 - jupiter2Translate) < 100.0f || glm::length(newUfo3 - saturnTranslate) < 150.0f || glm::length(newUfo3 - saturn2Translate) < 150.0f
		|| glm::length(newUfo3 - uranusTranslate) < 80.0f || glm::length(newUfo3 - uranus2Translate) < 80.0f || glm::length(newUfo3 - neptuneTranslate) < 78.0f
		|| glm::length(newUfo3 - neptune2Translate) < 78.0f;
	bool isAsteroid = false;
	for (auto i : wspolrzedne) {
		if (glm::length(newUfo3 - i) < 2.0f) {
			isAsteroid = true;
			break;
		}
	}
	while (isCloser || isSun || isPlanet || isAsteroid) {
		newUfo3 = wspolrzedneUfo[3] + glm::sphericalRand(0.7f);
		isCloser = glm::length(newUfo3 - (ship_pos)) < glm::length(wspolrzedneUfo[3] - (ship_pos));
		isSun = isSun = glm::length(newUfo3 - sunPos) < 140.0f || glm::length(newUfo3 - sunPos2) < 140.0f;
		isPlanet = glm::length(newUfo3 - mercuryTranslate) < 19.2f || glm::length(newUfo3 - mercury2Translate) < 19.2f || glm::length(newUfo3 - venusTranslate) < 36.3f
			|| glm::length(newUfo3 - venus2Translate) < 36.3f || glm::length(newUfo3 - earthTranslate) < 78.1f || glm::length(newUfo3 - earth2Translate) < 78.1f
			|| glm::length(newUfo3 - marsTranslate) < 27.2f || glm::length(newUfo3 - mars2Translate) < 38.1f || glm::length(newUfo3 - jupiterTranslate) < 100.0f
			|| glm::length(newUfo3 - jupiter2Translate) < 100.0f || glm::length(newUfo3 - saturnTranslate) < 150.0f || glm::length(newUfo3 - saturn2Translate) < 150.0f
			|| glm::length(newUfo3 - uranusTranslate) < 80.0f || glm::length(newUfo3 - uranus2Translate) < 80.0f || glm::length(newUfo3 - neptuneTranslate) < 78.0f
			|| glm::length(newUfo3 - neptune2Translate) < 78.0f;
		isAsteroid = false;
		for (auto i : wspolrzedne) {
			if (glm::length(newUfo3 - i) < 2.0f) {
				isAsteroid = true;
				break;
			}
		}
	}
	bool isTooFar = glm::length(newUfo3 - (ship_pos)) > 500.0f;
	if (!isTooFar) {
		wspolrzedneUfo[3] = newUfo3;
	}
	
	return catmull;
}


glm::mat4 createCameraMatrixF()
{
	rotation = glm::quat_cast(cameraMatrix);
	PxTransform shipPosition = shipBody->getGlobalPose();
	glm::quat shipQuaternion = glm::quat(shipPosition.q.w, shipPosition.q.x, shipPosition.q.y, shipPosition.q.z);
	glm::vec3 offset = glm::quat(shipPosition.q.w, shipPosition.q.x, shipPosition.q.y, shipPosition.q.z) * glm::vec3(0, 0, 1) * 0.65f;
	cameraPos = offset + glm::vec3(shipPosition.p.x, shipPosition.p.y - 0.65f, shipPosition.p.z);

	glm::quat kwaternionX = glm::angleAxis(roznicaY, glm::vec3(1, 0, 0));
	glm::quat kwaternionY = glm::angleAxis(roznicaX, glm::vec3(0, 1, 0));
	glm::quat kwaternionZ = glm::angleAxis(roznicaZ / 10, glm::vec3(0, 0, 1));
	roznicaX = 0;
	roznicaY = 0;
	roznicaZ = 0;
	glm::quat rotationChange = kwaternionZ * kwaternionY * kwaternionX;
	rotation = rotationChange * rotation;
	rotation = glm::normalize(rotation);

	glm::quat inversedRotation;
	inversedRotation = glm::inverse(rotation);

	cameraDir = inversedRotation * glm::vec3(0.0f, 0.0f, -1.0f);
	cameraSide = inversedRotation * glm::vec3(1.0f, 0.0f, 0.0f);

	return glm::translate(glm::vec3(0,-1,0))*Core::createViewMatrixQuat(cameraPos, rotation);
}

glm::mat4 createCameraMatrix()
{
	PxTransform shipPosition = shipBody->getGlobalPose();
	glm::quat shipQuaternion = glm::quat(shipPosition.q.w, shipPosition.q.x, shipPosition.q.y, shipPosition.q.z);
	glm::vec3 offset = glm::quat(shipPosition.q.w, shipPosition.q.x, shipPosition.q.y, shipPosition.q.z) * glm::vec3(0, 0, 1) * 0.65f;
	cameraPos = offset + glm::vec3(shipPosition.p.x, shipPosition.p.y - 0.65f, shipPosition.p.z);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(shipPosition.p.x, shipPosition.p.y - 0.65f, shipPosition.p.z);
	cameraDir = glm::normalize(cameraPos - cameraTarget);

	return glm::translate(glm::vec3(0, -1, 0)) * glm::lookAt(cameraPos, cameraPos - cameraDir, cameraUp);

}

void createObjects() {
	for (int i = 0; i < 70; i++) {
		glm::vec2 asteroid2D = glm::circularRand(500.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x, rand() % 50 - 50, asteroid2D.y);
	}
	for (int i = 70; i < 140; i++) {
		glm::vec2 asteroid2D = glm::circularRand(550.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x, rand() % 50 - 50, asteroid2D.y);
	}
	for (int i = 140; i < 210; i++) {
		glm::vec2 asteroid2D = glm::circularRand(500.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x + sunPos2.x, rand() % 50 - 50 + sunPos2.y, asteroid2D.y + sunPos2.z);
	}
	for (int i = 210; i < 280; i++) {
		glm::vec2 asteroid2D = glm::circularRand(550.0f);
		wspolrzedne[i] = glm::vec3(asteroid2D.x + sunPos2.x, rand() % 50 - 50 + sunPos2.y, asteroid2D.y + sunPos2.z);
	}

	ship = new Ship(programColor, &shipModel, sunPos, sunPos2, glm::vec3(0.6f));
	ship->setMatrix(glm::rotate(shipAngle,glm::vec3(0,1,0))*glm::scale(glm::vec3(0.0008f)));

	ufo = new Ufo(programUfo, &ufoModel, glm::translate(glm::vec3(0.0f)), textureUfo, sunPos, sunPos2);

	rocket = new Ship(programColor, &rocketModel, sunPos, sunPos2, glm::vec3(0.6f));
	rocket->setMatrix(glm::translate(glm::vec3(0, 200, 0)));

	sun1 = new Sun(programSun, &sphereModel, glm::translate(sunPos) * glm::scale(glm::vec3(8 * 14.0f)),sunPos,sunPos2,textureSun);
	sun2 = new Sun(programSun, &sphereModel, glm::translate(sunPos2) * glm::scale(glm::vec3(8 * 14.0f)), sunPos, sunPos2, textureSun);

	for (int i = 0; i < 280; i++) {
		//std::shared_ptr<Asteroid> asteroid = Asteroid::create(programBump, &sphereModel, glm::translate(wspolrzedne[i]), textureAsteroid, sunPos, sunPos2);
		//asteroid->setNormal(textureAsteroid_normals);
		asteroids.emplace_back(new Asteroid(programBump, &sphereModel, glm::translate(wspolrzedne[i]), textureAsteroid, sunPos, sunPos2));
		asteroids[i]->setNormal(textureAsteroid_normals);
		//renderables.emplace_back(asteroid);
	}

	mercury = new Planet(programTexture, &sphereModel, glm::translate(mercuryTranslate), textureMercury, sunPos, sunPos2);
	venus = new Planet(programTexture, &sphereModel, glm::translate(venusTranslate), textureVenus, sunPos, sunPos2);
	earth = new Planet(programTexture, &sphereModel, glm::translate(earthTranslate), textureEarth, sunPos, sunPos2);
	mars = new Planet(programTexture, &sphereModel, glm::translate(marsTranslate), textureMars, sunPos, sunPos2);
	jupiter = new Planet(programTexture, &sphereModel, glm::translate(jupiterTranslate), textureJupiter, sunPos, sunPos2);
	saturn = new Planet(programTexture, &saturnModel, glm::translate(saturnTranslate), textureSaturn, sunPos, sunPos2);
	uranus = new Planet(programTexture, &sphereModel, glm::translate(uranusTranslate), textureUranus, sunPos, sunPos2);
	neptune = new Planet(programTexture, &sphereModel, glm::translate(neptuneTranslate), textureNeptune, sunPos, sunPos2);

	mercury2 = new Planet(programTexture, &sphereModel, glm::translate(mercury2Translate), textureMercury, sunPos, sunPos2);
	venus2 = new Planet(programTexture, &sphereModel, glm::translate(venus2Translate), textureVenus, sunPos, sunPos2);
	earth2 = new Planet(programTexture, &sphereModel, glm::translate(earth2Translate), textureEarth, sunPos, sunPos2);
	mars2 = new Planet(programTexture, &sphereModel, glm::translate(mars2Translate), textureMars, sunPos, sunPos2);
	jupiter2 = new Planet(programTexture, &sphereModel, glm::translate(jupiter2Translate), textureJupiter, sunPos, sunPos2);
	saturn2 = new Planet(programTexture, &saturnModel, glm::translate(saturn2Translate), textureSaturn, sunPos, sunPos2);
	uranus2 = new Planet(programTexture, &sphereModel, glm::translate(uranus2Translate), textureUranus, sunPos, sunPos2);
	neptune2 = new Planet(programTexture, &sphereModel, glm::translate(neptune2Translate), textureNeptune, sunPos, sunPos2);

	moon = new Planet(programTexture, &sphereModel, glm::translate(moonTranslate), textureMercury, sunPos, sunPos2);
	moon2 = new Planet(programTexture, &sphereModel, glm::translate(moon2Translate), textureMercury, sunPos, sunPos2);
}

void drawObjects() {
	timeF = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	// ship
	//ship.setMatrix(shipModelMatrix);
	//shipBody->userData = &ship.getMatrix();
	ship->setMatrix(ship->getMatrix() * glm::rotate(shipAngle, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.0008f)));
	ship->draw(ship->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//rocketMatrix = ship->getMatrix();
	//rocketMatrix[3][1] -= 0.1f;
	//rocketMatrix = rocketMatrix * glm::scale(glm::vec3(0.3f));
	//rocket->setMatrix(rocketMatrix);
	rocket->setMatrix(rocket->getMatrix() * glm::rotate(shipAngle,glm::vec3(0,1,0)) * glm::scale(glm::vec3(0.00024f)));
	rocket->draw(rocket->getColor(), cameraPos, perspectiveMatrix, cameraMatrix);

	ufo->setMatrix(glm::translate(predictMove()) * glm::scale(glm::vec3(4.0f)));
	//ufo->setMatrix(glm::translate(glm::vec3(300,0,250)) * glm::scale(glm::vec3(4.0f)));
	ufoBody->setKinematicTarget(PxTransform(ufo->getMatrix()[3][0], ufo->getMatrix()[3][1], ufo->getMatrix()[3][2]));
	ufo->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	
	sun1->setMatrix(sun1->getMatrix() * glm::scale(glm::vec3(8 * 14.0f)));
	sun1->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	sun2->setMatrix(sun2->getMatrix() * glm::scale(glm::vec3(8 * 14.0f)));
	sun2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	
	for (auto obj : asteroids) {
		obj->setMatrix(obj->getMatrix());
		obj->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	}

	//overall rotation matrix for planets
	glm::mat4 planetRotation = glm::rotate(3.14f / 2.f * timeF / 2, glm::vec3(0.0f, 1.0f, 0.0f));

	//mercury
	mercuryTranslate = glm::vec3(sunPos.x + 170.0f * sinf(timeF / 8), sunPos.y, sunPos.z + 170.0f * cosf(timeF / 8));
	mercury->setMatrix(glm::translate(mercuryTranslate) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
	if(mercuryBody) mercuryBody->setKinematicTarget(PxTransform(mercury->getMatrix()[3][0], mercury->getMatrix()[3][1], mercury->getMatrix()[3][2]));
	mercury->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//venus
	venusTranslate = glm::vec3(sunPos.x + -260.0f * sinf(timeF / 10), sunPos.y, sunPos.z + -260.0f * cosf(timeF / 10));
	venus->setMatrix(glm::translate(venusTranslate) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
	venusBody->setKinematicTarget(PxTransform(venus->getMatrix()[3][0], venus->getMatrix()[3][1], venus->getMatrix()[3][2]));
	venus->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//earth
	earthTranslate = glm::vec3(sunPos.x + 350.0f * sinf(timeF / 12), sunPos.y, sunPos.z + 350.0f * cosf(timeF / 12));
	earth->setMatrix(glm::translate(earthTranslate) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
	earthBody->setKinematicTarget(PxTransform(earth->getMatrix()[3][0], earth->getMatrix()[3][1], earth->getMatrix()[3][2]));
	earth->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//mars
	marsTranslate = glm::vec3(sunPos.x + -440.0f * sinf(timeF / 14), sunPos.y, sunPos.z + -440.0 * cosf(timeF / 14));
	mars->setMatrix(glm::translate(marsTranslate) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
	marsBody->setKinematicTarget(PxTransform(mars->getMatrix()[3][0], mars->getMatrix()[3][1], mars->getMatrix()[3][2]));
	mars->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//jupiter
	jupiterTranslate = glm::vec3(sunPos.x + 800.0f * sinf(timeF / 16), sunPos.y, sunPos.z + 800.0f * cosf(timeF / 16));
	jupiter->setMatrix(glm::translate(jupiterTranslate) * planetRotation * glm::scale(glm::vec3(7 * 7.1f)));
	jupiterBody->setKinematicTarget(PxTransform(jupiter->getMatrix()[3][0], jupiter->getMatrix()[3][1], jupiter->getMatrix()[3][2]));
	jupiter->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//saturn
	saturnTranslate = glm::vec3(sunPos.x + -1100.0f * sinf(timeF / 18), sunPos.y, sunPos.z + -1100.0f * cosf(timeF / 18));
	saturn->setMatrix(glm::translate(saturnTranslate) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(6.0f / 40)));
	saturnBody->setKinematicTarget(PxTransform(saturn->getMatrix()[3][0], saturn->getMatrix()[3][1], saturn->getMatrix()[3][2]));
	saturn->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//uranus
	uranusTranslate = glm::vec3(sunPos.x + 1400.0f * sinf(timeF / 20), sunPos.y, sunPos.z + 1400.0f * cosf(timeF / 20));
	uranus->setMatrix(glm::translate(uranusTranslate) * planetRotation * glm::scale(glm::vec3(40.0f)));
	uranusBody->setKinematicTarget(PxTransform(uranus->getMatrix()[3][0], uranus->getMatrix()[3][1], uranus->getMatrix()[3][2]));
	uranus->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//neptune
	neptuneTranslate = glm::vec3(sunPos.x + -1700.0f * sinf(timeF / 22), sunPos.y, sunPos.z + -1700.0f * cosf(timeF / 22));
	neptune->setMatrix(glm::translate(neptuneTranslate) * planetRotation * glm::scale(glm::vec3(39.0f)));
	neptuneBody->setKinematicTarget(PxTransform(neptune->getMatrix()[3][0], neptune->getMatrix()[3][1], neptune->getMatrix()[3][2]));
	neptune->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//mercury2
	mercury2Translate = glm::vec3(sunPos2.x + 170.0f * sinf(timeF / 8), sunPos2.y, sunPos2.z + 170.0f * cosf(timeF / 8));
	mercury2->setMatrix(glm::translate(mercury2Translate) * planetRotation * glm::scale(glm::vec3(20 * 0.48f)));
	mercuryBody2->setKinematicTarget(PxTransform(mercury2->getMatrix()[3][0], mercury2->getMatrix()[3][1], mercury2->getMatrix()[3][2]));
	mercury2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//venus2
	venus2Translate = glm::vec3(sunPos2.x + -260.0f * sinf(timeF / 10), sunPos2.y, sunPos2.z + -260.0f * cosf(timeF / 10));
	venus2->setMatrix(glm::translate(venus2Translate) * planetRotation * glm::scale(glm::vec3(15 * 1.21f)));
	venusBody2->setKinematicTarget(PxTransform(venus2->getMatrix()[3][0], venus2->getMatrix()[3][1], venus2->getMatrix()[3][2]));
	venus2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//earth2
	earth2Translate = glm::vec3(sunPos2.x + 350.0f * sinf(timeF / 12), sunPos2.y, sunPos2.z + 350.0f * cosf(timeF / 12));
	earth2->setMatrix(glm::translate(earth2Translate) * planetRotation * glm::scale(glm::vec3(15 * 1.27f)));
	earthBody2->setKinematicTarget(PxTransform(earth2->getMatrix()[3][0], earth2->getMatrix()[3][1], earth2->getMatrix()[3][2]));
	earth2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//mars2
	mars2Translate = glm::vec3(sunPos2.x + -440.0f * sinf(timeF / 14), sunPos2.y, sunPos2.z + -440.0 * cosf(timeF / 14));
	mars2->setMatrix(glm::translate(mars2Translate) * planetRotation * glm::scale(glm::vec3(20 * 0.68f)));
	marsBody2->setKinematicTarget(PxTransform(mars2->getMatrix()[3][0], mars2->getMatrix()[3][1], mars2->getMatrix()[3][2]));
	mars2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//
	
	//jupiter2
	jupiter2Translate = glm::vec3(sunPos2.x + 800.0f * sinf(timeF / 16), sunPos2.y, sunPos2.z + 800.0f * cosf(timeF / 16));
	jupiter2->setMatrix(glm::translate(jupiter2Translate)* planetRotation* glm::scale(glm::vec3(7 * 7.1f)));
	jupiterBody2->setKinematicTarget(PxTransform(jupiter2->getMatrix()[3][0], jupiter2->getMatrix()[3][1], jupiter2->getMatrix()[3][2]));
	jupiter2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//
	
	//saturn2
	saturn2Translate = glm::vec3(sunPos2.x + -1100.0f * sinf(timeF / 18), sunPos2.y, sunPos2.z + -1100.0f * cosf(timeF / 18));
	saturn2->setMatrix(glm::translate(saturn2Translate) * planetRotation * glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(6.0f / 40)));
	saturnBody2->setKinematicTarget(PxTransform(saturn2->getMatrix()[3][0], saturn2->getMatrix()[3][1], saturn2->getMatrix()[3][2]));
	saturn2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//uranus2
	uranus2Translate = glm::vec3(sunPos2.x + 1400.0f * sinf(timeF / 20), sunPos2.y, sunPos2.z + 1400.0f * cosf(timeF / 20));
	uranus2->setMatrix(glm::translate(uranus2Translate)* planetRotation* glm::scale(glm::vec3(40.0f)));
	uranusBody2->setKinematicTarget(PxTransform(uranus2->getMatrix()[3][0], uranus2->getMatrix()[3][1], uranus2->getMatrix()[3][2]));
	uranus2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//neptune2
	neptune2Translate = glm::vec3(sunPos2.x + -1700.0f * sinf(timeF / 22), sunPos2.y, sunPos2.z + -1700.0f * cosf(timeF / 22));
	neptune2->setMatrix(glm::translate(neptune2Translate)* planetRotation* glm::scale(glm::vec3(39.0f)));
	neptuneBody2->setKinematicTarget(PxTransform(neptune2->getMatrix()[3][0], neptune2->getMatrix()[3][1], neptune2->getMatrix()[3][2]));
	neptune2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//moon
	moonTranslate = glm::vec3((sunPos.x + 350.0f * sinf(timeF / 12)) + 40 * sinf(timeF), sunPos.y, (sunPos.z + 350.0f * cosf(timeF / 12)) + 40 * cosf(timeF));
	moon->setMatrix(glm::translate(moonTranslate)* glm::scale(glm::vec3(0.25f))* planetRotation* glm::scale(glm::vec3(15 * 1.27f)));
	moonBody->setKinematicTarget(PxTransform(moon->getMatrix()[3][0], moon->getMatrix()[3][1], moon->getMatrix()[3][2]));
	moon->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//moon2
	moon2Translate = glm::vec3((sunPos2.x + 350.0f * sinf(timeF / 12)) + 40 * sinf(timeF), sunPos2.y, (sunPos2.z + 350.0f * cosf(timeF / 12)) + 40 * cosf(timeF));
	moon2->setMatrix(glm::translate(moon2Translate)* glm::scale(glm::vec3(0.25f))* planetRotation* glm::scale(glm::vec3(15 * 1.27f)));
	moonBody2->setKinematicTarget(PxTransform(moon2->getMatrix()[3][0], moon2->getMatrix()[3][1], moon2->getMatrix()[3][2]));
	moon2->drawTexture(cameraPos, perspectiveMatrix, cameraMatrix);
	//

	//gunsight
	if (mouseKeyDown) {
		text(swidth/2 - 5, sheight/2 - 50, "+", 20);
	}
	//

	//particle effect
	for (auto effect : particleEffects) {
		if (effect->isActive()) {
				effect->sendProjectionToShader(perspectiveMatrix, cameraMatrix, particleMatrix);
				effect->simulate();
			}
	}
	//

	reloadRocket();
}

void renderScene()
{
	double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	static double prevTime = time;
	double dtime = time - prevTime;
	prevTime = time;

	// Update physics
	if (dtime < 1.f) {
		physicsTimeToProcess += dtime;
		while (physicsTimeToProcess > 0) {
			// here we perform the physics simulation step
			scene.step(physicsStepTime);
			physicsTimeToProcess -= physicsStepTime;
		}
	}
	//shipBody->setAngularVelocity();
	shipBody->setLinearVelocity(PxVec3(0, 0, 0));
	shipBody->setAngularVelocity(PxVec3(0, 0, 0));

	PxRigidBodyExt::addLocalForceAtLocalPos(*shipBody, PxVec3(0, 0, F_side), PxVec3(2, 0, 0));
	PxRigidBodyExt::addLocalForceAtLocalPos(*shipBody, PxVec3(0, 0, F_front), PxVec3(0, 0, 0));
	PxRigidBodyExt::addLocalForceAtLocalPos(*shipBody, PxVec3(0, F_qe, 0), PxVec3(0, 0, 0));
	PxRigidBodyExt::addLocalForceAtLocalPos(*shipBody, PxVec3(0, F_zc, 0), PxVec3(2, 0, 0));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	if (!freeLook) {
		cameraMatrix = createCameraMatrix();
	}
	else {
		cameraMatrix = createCameraMatrixF();
	}
	perspectiveMatrix = Core::createPerspectiveMatrix(frustumScale);

	updateTransforms();
	lowerForces();
	removeInActiveActors();
	Skybox::renderSkybox(programSkybox, cameraMatrix, perspectiveMatrix);
	drawObjects();
	glutSwapBuffers();
}

void mouse(int x, int y)
{
	if (freeLook) {
		roznicaX = (x - ostatniX) / 100.0f;
		roznicaY = (y - ostatniY) / 100.0f;
		ostatniX = x;
		ostatniY = y;
	}
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (mouseKeyDown) {
			mouseKeyDown = false;
			cameraPos -= cameraDir * 50.0f;
		}
		else {
			mouseKeyDown = true;
			cameraPos += cameraDir * 50.0f;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//effect = new ParticleEffect(programParticle, 1, 0.0015625f, textureParticle, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
		shoot();
	}
}

void loadParticleTextures() {
	textureParticle = Core::LoadParticleTextures();
}

void init()
{
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	programSun = shaderLoader.CreateProgram("shaders/shader_sun.vert", "shaders/shader_sun.frag");
	programSight = shaderLoader.CreateProgram("shaders/shader_sight.vert", "shaders/shader_sight.frag");
	programBump = shaderLoader.CreateProgram("shaders/shader_bump.vert", "shaders/shader_bump.frag");
	programSkybox = shaderLoader.CreateProgram("shaders/shader_skybox.vert", "shaders/shader_skybox.frag");
	programUfo = shaderLoader.CreateProgram("shaders/shader_ufo.vert", "shaders/shader_ufo.frag");
	programParticle = shaderLoader.CreateProgram("shaders/shader_particle.vert", "shaders/shader_particle.frag");

	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/wraith.obj");
	planeModel = obj::loadModelFromFile("models/plane.obj");
	saturnModel = obj::loadModelFromFile("models/saturn.obj");
	ufoModel = obj::loadModelFromFile("models/ufo.obj");
	rocketModel = obj::loadModelFromFile("models/rocket.obj");

	textureAsteroid = Core::LoadTexture("textures/asteroid.png");
	textureAsteroid_normals = Core::LoadTexture("textures/asteroid_normals.png");
	textureJupiter = Core::LoadTexture("textures/jupiter.png");
	textureMars = Core::LoadTexture("textures/mars.png");
	textureMercury = Core::LoadTexture("textures/mercury.png");
	textureVenus = Core::LoadTexture("textures/venus.png");
	textureEarth = Core::LoadTexture("textures/earth2.png");
	textureSaturn = Core::LoadTexture("textures/saturn.png");
	textureUranus = Core::LoadTexture("textures/uranus.png");
	textureNeptune = Core::LoadTexture("textures/neptune.png");
	textureSun = Core::LoadTexture("textures/sun.png");
	textureUfo = Core::LoadTexture("textures/ufo.png");

	loadParticleTextures();

	Skybox::initSkybox();
	createObjects();
	initPhysicsScene();
	appLoadingTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

}

void keyboard(unsigned char key, int x, int y)
{
	float angleSpeed = 0.1f;
	float moveSpeed = 10.0f;
	switch (key)
	{
	case 'w': F_front -= 25; break;
	case 's': F_front += 25; break;
	case 'd': F_side += 5.0f; break;
	case 'a': F_side -= 5.0f; break;
	case 'q': F_qe -= 15; break;
	case 'e': F_qe += 15; break;
	case 'z': F_zc += 5; break;
	case 'c': F_zc -= 5; break;
	case 'm': shipAngle += glm::radians(2.0f); break;
	case 'f': freeLook = !freeLook; break;
	case 'r': F_front = 0; F_side = 0; F_zc = 0; F_qe = 0; break;
	case 'k': shoot(); break;
	}
}

void onReshape(int width, int height)
{
	frustumScale = (float)width / height;
	swidth = width;
	sheight = height;
	int w = width;
	int h = height;
	if (width > height)
		h = height * frustumScale;
	if (height > width)
		w = width * frustumScale;
	glViewport(0, 0, w, h);
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
	shaderLoader.DeleteProgram(programSun);
	shaderLoader.DeleteProgram(programSight);
	shaderLoader.DeleteProgram(programBump);
	shaderLoader.DeleteProgram(programSkybox);
	shaderLoader.DeleteProgram(programUfo);
	shaderLoader.DeleteProgram(programParticle);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 30);
	glutInitWindowSize(650, 650);
	glutCreateWindow("Spaceship Simulator Project");
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutReshapeFunc(onReshape);

	glutMainLoop();

	shutdown();

	return 0;
}
