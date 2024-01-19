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
#include<optional>
class Player : public BaseCharacter{
private:
	enum {
		Body,
		Head,
		L_arm,
		R_arm,
		Hammer
	};
	enum class Behavior {
		kRoot,
		kAttack,
		kJump,
		kjumpAttack,
	};

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;


	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;

	
	WorldTransform worldTransform_Body_;
	
	WorldTransform worldTransform_Head_;
	
	WorldTransform worldTransform_L_arm_;
	
	WorldTransform worldTransform_R_arm_;
	
	WorldTransform worldTransform_Hammer_;
	
	
	float floatingParameter_;

	Vector3 velocity_ = {};

	XINPUT_STATE joyState; 

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models)override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection &viewprojection);

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	void InitializeFloatingGimmick();
	void UpdateFloatingGimmick();
	void BehaviorRootUpdate();
	void BehaviorAttackUpdate();
	void BehaviorRootInitialize();
	void BehaviorAttackInitialize();
	void BehaviorJumpInitialize();
	void BehaviorJumpUpdate();
	void BehaviorJumpAttackInitialize();
	void BehaviorJumpAttackUpdate();


	const WorldTransform &GetWorldTransform() { return worldTransform_Body_; }
};
