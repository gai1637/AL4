#include "Enemy.h"

#include "TextureManager.h"
#include <cassert>
#include<math.h>
#include"MathUtilityForText.h"
#include<imgui.h>
void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models);
	worldTransform_L_arm_.Initialize();
	worldTransform_L_arm_.parent_ = &worldTransform_;
	worldTransform_L_arm_.translation_ = {-0.8f, 1.0f, 0.0f};
	worldTransform_R_arm_.Initialize();
	worldTransform_R_arm_.parent_ = &worldTransform_;
	worldTransform_R_arm_.translation_ = {0.8f, 1.0f, 0.0f};
}
void Enemy::Update() {
	
	const float speed = 0.1f;
	worldTransform_.rotation_.y += 0.01f;
	Vector3 move = {0.f, 0.f, speed};
	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransform_.rotation_.y);
	move = TransformNormal(move, matRotY);
	worldTransform_.translation_ += move;

	/*worldTransform_L_arm_.translation_ = worldTransform_.translation_ + L_arm_Lengh;
	worldTransform_R_arm_.translation_ = worldTransform_.translation_ + R_arm_Lengh;*/

	BaseCharacter::Update();
	worldTransform_L_arm_.UpdateMatrix();
	worldTransform_R_arm_.UpdateMatrix();

}
void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[body]->Draw(worldTransform_, viewProjection);
	models_[L_arm]->Draw(worldTransform_L_arm_, viewProjection);
	models_[R_arm]->Draw(worldTransform_R_arm_, viewProjection);
}