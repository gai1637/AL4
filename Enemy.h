#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<memory>
#include"BaseCharacter.h"
class Enemy : public BaseCharacter{
public:
	void Initialize(const std::vector<Model*>& models)override;
	
	void Update()override;
	void Draw(const ViewProjection& viewProjection)override;

private:
	enum{
		body,
		L_arm,
		R_arm
	};
	WorldTransform worldTransform_L_arm_;
	Vector3 L_arm_Lengh;
	WorldTransform worldTransform_R_arm_;
	Vector3 R_arm_Lengh;

};
