#include "Hammer.h"
#include"Enemy.h"
void Hammer::Initialize() { 
	worldTransform_.Initialize();
	Collider::Initialize();
	Collider::SetTypeID(static_cast<uint32_t>(CollisionTypeIDef::kPlayerWeapon));
}
void Hammer::Update() { 
	
	worldTransform_.UpdateMatrix(); 
	
}
Vector3 Hammer::GetCenterPosition() const { 
	const Vector3 offset = {0.0f, 4.5f, 0.0f};
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);
	return worldPos;
}
void Hammer::OnCollision([[maybe_unused]] Collider* other) { 
	uint32_t typeID = other->GetTypeID();
	if (typeID == static_cast<uint32_t>(CollisionTypeIDef::kEnemy)) {
		Enemy* enemy = static_cast<Enemy*>(other);
		enemy->Reset(true);
	}
}