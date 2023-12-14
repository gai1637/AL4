#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
class FollowCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }
	const ViewProjection &GetViewProjection() { return viewProjection_; }
	Vector3 ReturnViewRotate() { return viewProjection_.rotation_; }
	Vector3 ReturnViewTranslation() { return viewProjection_.translation_; }


private:
	ViewProjection viewProjection_;
	const WorldTransform* target_ = nullptr;
};
