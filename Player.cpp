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

	worldTransform_Head_.translation_ = {0.f,1.4f,0.0f};
	
	
	worldTransform_L_arm_.Initialize();
	worldTransform_L_arm_.parent_ = &worldTransform_Body_;
	worldTransform_L_arm_.translation_= {-0.5f, 1.25f, 0.0f};

	
	worldTransform_R_arm_.Initialize();
	worldTransform_R_arm_.parent_ = &worldTransform_Body_;
	worldTransform_R_arm_.translation_ = {0.5f, 1.25f, 0.0f};

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


	ImGui::Begin("a");
	ImGui::SliderFloat("L_Arm_x",&worldTransform_Head_.translation_.x,-5.0f,5.0f);
	ImGui::SliderFloat("L_Arm_y",&worldTransform_Head_.translation_.y,-5.0f,5.0f);
	ImGui::SliderFloat("L_Arm_z",&worldTransform_Head_.translation_.z,-5.0f,5.0f);
	


	ImGui::End();
}
Player::~Player() {
	
	
}
void Player::Update() { 
	
	XINPUT_STATE joyState; 
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float speed = 0.3f;
		const float threshold = 0.7f;
		bool isMoving = false;


		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX
		};
		if (Length(move) > threshold) {
			isMoving = true;
		}
		if (isMoving) {
			move = Normalize(move) * speed;
			if (viewProjection_) {
				Matrix4x4 matRotX = MakeRotateXMatrix(viewProjection_->rotation_.x);
				Matrix4x4 matRotY = MakeRotateYMatrix(viewProjection_->rotation_.y);
				Matrix4x4 matRotZ = MakeRotateZMatrix(viewProjection_->rotation_.z);
				Matrix4x4 matRot = matRotZ * matRotX * matRotY;

				move = TransformNormal(move, matRot);
			}
			worldTransform_Body_.translation_ += move;
			worldTransform_Body_.rotation_.y = std::atan2(move.x, move.z);
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



	worldTransform_.UpdateMatrix();
	worldTransform_Head_.UpdateMatrix();
	worldTransform_Body_.UpdateMatrix();
	worldTransform_L_arm_.UpdateMatrix();
	worldTransform_R_arm_.UpdateMatrix();
}
void Player::Draw(const ViewProjection &viewprojection) { 
	/*model_->Draw(worldTransform_, viewprojection);*/
	models_[Body]->Draw(worldTransform_Body_, viewprojection);
	models_[Head]->Draw(worldTransform_Head_, viewprojection);
	models_[L_arm]->Draw(worldTransform_L_arm_, viewprojection);
	models_[R_arm]->Draw(worldTransform_R_arm_, viewprojection);
}