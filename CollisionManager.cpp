#include "CollisionManager.h"
void CollisionManager::Reset() { 
	colliders_.clear(); 
}
void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	Vector3 colliderA_ = colliderA->GetCenterPosition();
	Vector3 colliderB_ = colliderB->GetCenterPosition();
	Vector3 subtract = colliderB_ - colliderA_;
	float distance = Length(subtract);
	if (distance <= 3.0) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}
void CollisionManager::CheckAllCollisions() {
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}
void CollisionManager::AddCollider(Collider* collider) { colliders_.push_back(collider); }