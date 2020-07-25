#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"

class PathNode;

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();
	std::vector<PathNode*>* m_vPatrolPath;
	//bool m_bActivatePatrol = false;
	bool m_bReadyToMoveNext = true;
	int m_iNextNodeIdx = -1;
	glm::vec2 Direction;
};

#endif /* defined (__PLANE__) */
