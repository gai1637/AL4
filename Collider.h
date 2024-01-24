#pragma once
#include"Vector3.h"
class Collider {
private:
	float Lengh_ = 1.5f;

public:
	float GetLengh() { return Lengh_; }
	void SetLengh(float Lengh) { Lengh_ = Lengh; }
	virtual void OnCollision(){}
	virtual Vector3 GetCenterPosition() const = 0;
	virtual ~Collider() = default;
	

};
