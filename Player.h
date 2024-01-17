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
class Player {
private:
	
	std::unique_ptr<Model> model_ = nullptr;
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;

	std::unique_ptr<Model> model_Head_ = nullptr;
	WorldTransform worldTransform_Head_;
	float Head_Lengh;
	std::unique_ptr<Model> model_Body_ = nullptr;
	WorldTransform worldTransform_Body_;
	std::unique_ptr<Model> model_L_arm_ = nullptr;
	WorldTransform worldTransform_L_arm_;
	Vector3 L_Arm_Lengh;
	std::unique_ptr<Model> model_R_arm_ = nullptr;
	WorldTransform worldTransform_R_arm_;
	Vector3 R_Arm_Lengh;

	float floatingParameter_;

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection &viewprojection);

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	void InitializeFloatingGimmick();
	void UpdateFloatingGimmick();

	const WorldTransform &GetWorldTransform() { return worldTransform_; }
};
