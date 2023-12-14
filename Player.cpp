#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include<math.h>
#include"MathUtilityForText.h"
void Player::Initialize() { 

	model_ = std::make_unique<Model>();
	model_.reset(Model::CreateFromOBJ("float",true));
	worldTransform_.Initialize();
	

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
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};
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
			worldTransform_.translation_ += move;
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);

		}
		/*const float kAngleInterRatio = 0.1f;*/
		worldTransform_.UpdateMatrix();
	}
}
void Player::Draw(const ViewProjection &viewprojection) { 
	model_->Draw(worldTransform_, viewprojection);
}