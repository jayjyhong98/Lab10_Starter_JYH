#include "Plane.h"
#include "PlayScene.h"
#include "PathNode.h"
#include "Game.h"
#include "Util.h"
#include "TextureManager.h"

Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
	m_vPatrolPath = ((PlayScene*)(Game::Instance()->getCurrentScene()))->getPatrolPath();
	int a = 10;
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"),
		x, y, 0.5f, 0, 255, true);
}

void Plane::update()
{
	bool PatrolMode = ((PlayScene*)(Game::Instance()->getCurrentScene()))->getPatrolMode();
	if (((PlayScene*)(Game::Instance()->getCurrentScene()))->getPatrolMode() == true)
	{
		if (m_bReadyToMoveNext)
		{
			++m_iNextNodeIdx;

			if (m_iNextNodeIdx == (*m_vPatrolPath).size())
			{
				m_iNextNodeIdx = 0;
			}
			Direction = ((*m_vPatrolPath)[m_iNextNodeIdx])->getTransform()->position - getTransform()->position;
			Direction = Util::normalize(Direction);
			//std::cout << "normalized direction: (" << normalized.x << ", " << normalized.y << ")" << std::endl;
			m_bReadyToMoveNext = false;
		}
		if (m_bReadyToMoveNext == false)
		{
			float length = Util::distance(((*m_vPatrolPath)[m_iNextNodeIdx])->getTransform()->position, getTransform()->position);
			if (length <= 5)
			{
				m_bReadyToMoveNext = true;
			}
			getTransform()->position.x += Direction.x * 5;
			getTransform()->position.y += Direction.y * 5;
		}
	}
}


void Plane::clean()
{
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}