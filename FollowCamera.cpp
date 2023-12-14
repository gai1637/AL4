#include "FollowCamera.h"
#include"MathUtilityForText.h"
#include "DirectXCommon.h"
#include "Input.h"
void FollowCamera::Initialize() {
	viewProjection_.farZ = 2000;
	viewProjection_.Initialize(); 
}
void FollowCamera::Update() {
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float speed = 0.03f;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;
	}
	if (target_) {
		Vector3 offset = {0.0f, 2.0f ,- 10.0f};
		
		Matrix4x4 matRotX = MakeRotateXMatrix(viewProjection_.rotation_.x);
		Matrix4x4 matRotY = MakeRotateYMatrix(viewProjection_.rotation_.y);
		Matrix4x4 matRotZ = MakeRotateZMatrix(viewProjection_.rotation_.z);
		Matrix4x4 matRot = matRotZ * matRotX * matRotY;
		offset = TransformNormal(offset, matRot);
		viewProjection_.translation_ = target_->translation_ + offset;
	}
	/*viewProjection_.TransferMatrix();*/
	viewProjection_.UpdateViewMatrix();
}