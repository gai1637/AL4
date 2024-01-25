#pragma once
#include"Collider.h"
#include"Model.h"
#include"WorldTransform.h"
#include"MathUtilityForText.h"

class Enemy;
class Hammer final : public Collider{
private:
	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;

public:
	const Vector3& GetRotation() const { return worldTransform_.rotation_; }
	void SetRotation(const Vector3& rotation) { worldTransform_.rotation_ = rotation; }
	void SetTranslation(const Vector3& translation_) { worldTransform_.translation_=translation_; }
	 WorldTransform& GetWorldTransfoem() { return worldTransform_; }
	void Initialize();
	void Update();
	Vector3 GetCenterPosition() const override;
	void OnCollision([[maybe_unused]]Collider* other) override;
};
