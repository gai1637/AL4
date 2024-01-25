#pragma once
#include"Vector3.h"
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"CollisionTypeIDef.h"
class Collider {
private:
	float Lengh_ = 1.5f;
	WorldTransform worldTransform;
	uint32_t typeID_ = 0u;

public:
	float GetLengh() { return Lengh_; }
	void SetLengh(float Lengh) { Lengh_ = Lengh; }
	virtual void OnCollision([[maybe_unused]]Collider* other) {}
	virtual Vector3 GetCenterPosition() const = 0;
	virtual ~Collider() = default;
	void Initialize();
	void UpdateWorldTransform();
	void Draw(Model* model,const ViewProjection& viewProjection);
	const uint32_t GetTypeID() const { return typeID_; }
	void SetTypeID(uint32_t typeID) { typeID_ = typeID; }

};
