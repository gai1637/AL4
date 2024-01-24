#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include<math.h>
#include"MathUtilityForText.h"
#include<imgui.h>

void Player::Initialize(const std::vector<Model*>& models) { 

	
	worldTransform_.Initialize();

	
	BaseCharacter::Initialize(models);
	
	worldTransform_Body_.Initialize();
	worldTransform_Body_.parent_ = &worldTransform_;
	
	worldTransform_Head_.Initialize();
	worldTransform_Head_.parent_ = &worldTransform_Body_;

	worldTransform_Head_.translation_ = {0.0f,1.4f,0.0f};
	
	
	worldTransform_L_arm_.Initialize();
	worldTransform_L_arm_.parent_ = &worldTransform_Body_;
	worldTransform_L_arm_.translation_= {-0.5f, 1.25f, 0.0f};

	
	worldTransform_R_arm_.Initialize();
	worldTransform_R_arm_.parent_ = &worldTransform_Body_;
	worldTransform_R_arm_.translation_ = {0.5f, 1.25f, 0.0f};

	worldTransform_Hammer_.Initialize();
	worldTransform_Hammer_.parent_ = &worldTransform_L_arm_;
	worldTransform_Hammer_.rotation_ = {0.3f, -3.14f, -3.126f};
	worldTransform_Hammer_.translation_ = {0.5f, 0.f, 0.0f};


	InitializeFloatingGimmick();
}
void Player::InitializeFloatingGimmick() {

	floatingParameter_ = 0.0f;

}
void Player::UpdateFloatingGimmick() {

	const uint16_t cycle = 60; 
	const float step = 2.0f * PI / cycle;
	floatingParameter_ += step;
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * PI);
	const float floating_width = 0.25f;
	worldTransform_Body_.translation_.y = std::sin(floatingParameter_) * floating_width;


	
}
Player::~Player() {
	
	
}
void Player::BehaviorRootUpdate() {
	

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float speed = 0.3f;
		const float threshold = 0.7f;
		bool isMoving = false;


		velocity_ = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX
		};
		if (Length(velocity_) > threshold) {
			isMoving = true;
		}
		if (isMoving) {
			velocity_ = Normalize(velocity_) * speed;
			if (viewProjection_) {
				Matrix4x4 matRotX = MakeRotateXMatrix(viewProjection_->rotation_.x);
				Matrix4x4 matRotY = MakeRotateYMatrix(viewProjection_->rotation_.y);
				Matrix4x4 matRotZ = MakeRotateZMatrix(viewProjection_->rotation_.z);
				Matrix4x4 matRot = matRotZ * matRotX * matRotY;

				velocity_ = TransformNormal(velocity_, matRot);
			}
			worldTransform_Body_.translation_ += velocity_;
			worldTransform_Body_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
			/*worldTransform_Head_.rotation_.y=std::atan2(move.x, move.z);
			worldTransform_L_arm_.rotation_.y=std::atan2(move.x, move.z);
			worldTransform_R_arm_.rotation_.y=std::atan2(move.x, move.z);*/
		}
		/*const float kAngleInterRatio = 0.1f;*/
		
	}

	UpdateFloatingGimmick();

	/*worldTransform_Head_.translation_.x = worldTransform_Body_.translation_.x;
	worldTransform_Head_.translation_.y = worldTransform_Body_.translation_.y + Head_Lengh;
	worldTransform_Head_.translation_.x = worldTransform_Body_.translation_.x;

	worldTransform_L_arm_.translation_.x = worldTransform_Body_.translation_.x + L_Arm_Lengh.x;
	worldTransform_L_arm_.translation_.y = worldTransform_Body_.translation_.y + L_Arm_Lengh.y;
	worldTransform_L_arm_.translation_.z = worldTransform_Body_.translation_.x + L_Arm_Lengh.z;

	worldTransform_R_arm_.translation_.x = worldTransform_Body_.translation_.x + R_Arm_Lengh.x;
	worldTransform_R_arm_.translation_.y = worldTransform_Body_.translation_.y + R_Arm_Lengh.y;
	worldTransform_R_arm_.translation_.z = worldTransform_Body_.translation_.x + R_Arm_Lengh.z;*/

	if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_X) {
		behaviorRequest_ = Behavior::kAttack;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		behaviorRequest_ = Behavior::kJump;
	}

}
void Player::BehaviorAttackUpdate() { 
	if (worldTransform_L_arm_.rotation_.x <= -1.5f) {
		worldTransform_L_arm_.rotation_.x += 0.1f;
		worldTransform_R_arm_.rotation_.x += 0.1f;
	} else {
		behaviorRequest_ = Behavior::kRoot;
	}
	
}
void Player::BehaviorRootInitialize() {
	worldTransform_L_arm_.rotation_.x = 0.f; 
	worldTransform_R_arm_.rotation_.x = 0.f; 
}
void Player::BehaviorAttackInitialize() {
	worldTransform_L_arm_.rotation_.x = -3.5f; 
	worldTransform_R_arm_.rotation_.x = -3.5f; 
}
void Player::BehaviorJumpInitialize() { 
	worldTransform_Body_.translation_.y = 0;
	worldTransform_L_arm_.rotation_.x = 0;
	worldTransform_R_arm_.rotation_.x = 0;
	const float kJumpFirstSpeed = 1.0f;
	velocity_.y =kJumpFirstSpeed;
}
void Player::BehaviorJumpUpdate() {
	worldTransform_Body_.translation_ += velocity_;
	const float kGravityAccleration = 0.05f;
	Vector3 accelerationVector = {0, -kGravityAccleration, 0};
	velocity_ += accelerationVector;
	if (worldTransform_Body_.translation_.y <= 0.0f) {
		worldTransform_Body_.translation_.y = 0;
		behaviorRequest_ = Behavior::kRoot;
	}
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		
	}
		
	if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_X) {
		behaviorRequest_ = Behavior::kjumpAttack;
	}
}
void Player::BehaviorJumpAttackInitialize() { 
	worldTransform_L_arm_.rotation_.x = -3.5f; 
	worldTransform_R_arm_.rotation_.x = -3.5f; 
}
void Player::BehaviorJumpAttackUpdate() {
	worldTransform_Body_.translation_ += velocity_;
	const float kGravityAccleration = 0.05f;
	Vector3 accelerationVector = {0, -kGravityAccleration, 0};
	velocity_ += accelerationVector;
	if (worldTransform_L_arm_.rotation_.x <= -1.5f) {
		worldTransform_L_arm_.rotation_.x += 0.1f;
		worldTransform_R_arm_.rotation_.x += 0.1f;
	} 
	if (worldTransform_Body_.translation_.y <= 0.0f) {
		worldTransform_Body_.translation_.y = 0;
		behaviorRequest_ = Behavior::kRoot;
	}
	
}

void Player::Update() { 
	
	
	if (behaviorRequest_) {
	behavior_ = behaviorRequest_.value();
	switch (behavior_) { 
	case Behavior::kRoot:
	default:
		BehaviorRootInitialize();
		
	break;
	case Behavior::kAttack:
	BehaviorAttackInitialize();
	
	break;
	case Behavior::kJump:
	BehaviorJumpInitialize();
	break;
	case Behavior::kjumpAttack:
	BehaviorJumpAttackInitialize();
	break;
	}
	behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) { 
	case Behavior::kRoot:
	default:
		
		BehaviorRootUpdate();
	break;
	case Behavior::kAttack:
	
	BehaviorAttackUpdate();
	break;
	case Behavior::kJump:
	BehaviorJumpUpdate();
	break;
	case Behavior::kjumpAttack:
	BehaviorJumpAttackUpdate();
	break;
	}

	
	ImGui::Begin("a");
	ImGui::SliderFloat("L_Arm_x",&worldTransform_Hammer_.translation_.x,-1.0f,1.0f);
	ImGui::SliderFloat("L_Arm_y",&worldTransform_Hammer_.translation_.y,-1.0f,1.0f);
	ImGui::SliderFloat("L_Arm_z",&worldTransform_Hammer_.translation_.z,-1.0f,1.0f);
	ImGui::SliderFloat("rotation_x",&worldTransform_Hammer_.rotation_.x,-0.0f,2.0f);
	ImGui::SliderFloat("rotation_y",&worldTransform_Hammer_.rotation_.y,-3.5f,0.0f);
	ImGui::SliderFloat("rotation_z",&worldTransform_Hammer_.rotation_.z,-3.5f,0.0f);
	


	ImGui::End();

	worldTransform_.UpdateMatrix();
	worldTransform_Body_.UpdateMatrix();
	worldTransform_Head_.UpdateMatrix();
	worldTransform_L_arm_.UpdateMatrix();
	worldTransform_R_arm_.UpdateMatrix();
	worldTransform_Hammer_.UpdateMatrix();
}
void Player::Draw(const ViewProjection &viewprojection) { 
	/*model_->Draw(worldTransform_, viewprojection);*/
	models_[Body]->Draw(worldTransform_Body_, viewprojection);
	models_[Head]->Draw(worldTransform_Head_, viewprojection);
	models_[L_arm]->Draw(worldTransform_L_arm_, viewprojection);
	models_[R_arm]->Draw(worldTransform_R_arm_, viewprojection);
	if (behavior_==Behavior::kAttack||behavior_==Behavior::kjumpAttack)
	models_[Hammer]->Draw(worldTransform_Hammer_, viewprojection);
}
Vector3 Player::GetCenterPosition() const { 
	const Vector3 offset = {0.0f, 1.5f, 0.0f};
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);
	return worldPos;
}
void Player::OnCollision() { behaviorRequest_ = Behavior::kJump; }