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

	const WorldTransform &GetWorldTransform() { return worldTransform_; }
};
