#pragma once
#include"Vector3.h"
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
class Collider {
private:
	float Lengh_ = 1.5f;
	WorldTransform worldTransform;

public:
	float GetLengh() { return Lengh_; }
	void SetLengh(float Lengh) { Lengh_ = Lengh; }
	virtual void OnCollision(){}
	virtual Vector3 GetCenterPosition() const = 0;
	virtual ~Collider() = default;
	void Initialize();
	void UpdateWorldTransform();
	void Draw(Model* model,const ViewProjection& viewProjection);


};
