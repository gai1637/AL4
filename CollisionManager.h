#pragma once
#include<List>
#include"Collider.h"
#include"MathUtilityForText.h"
class Collider;
class CollisionManager {
private:
	std::list<Collider*> colliders_;

public:
	void Reset();
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	void CheckAllCollisions();
	void AddCollider(Collider* collider);
};
