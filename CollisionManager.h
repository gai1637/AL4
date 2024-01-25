#pragma once
#include<List>
#include"Collider.h"
#include"MathUtilityForText.h"
#include"Model.h"
#include"ViewProjection.h"
class Collider;
class CollisionManager {
private:
	std::list<Collider*> colliders_;
	std::unique_ptr<Model> model_sphere_;
public:
	void Initialize();
	void Reset();
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	void CheckAllCollisions();
	void AddCollider(Collider* collider);
	void UpdateWorldTransform();
	void Draw(const ViewProjection& viewProjection);
};
