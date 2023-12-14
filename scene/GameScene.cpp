#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"Player.h"
#include"Skydome.h"
#include"Ground.h"
#include"FollowCamera.h"

GameScene::GameScene() {}

GameScene::~GameScene() {  }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.farZ = 2000;
	viewProjection_.translation_.y = 2;
	viewProjection_.Initialize();

	player_ = std::make_unique<Player>();
	player_->Initialize();


	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	ground_ = std::make_unique<Ground>();
	ground_->Initialize();

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	
	player_->SetViewProjection(&followcamera_->GetViewProjection());
	followcamera_->SetTarget(&player_->GetWorldTransform());

	
}

void GameScene::Update() { 
	
	followcamera_->Update();

	viewProjection_.matView = followcamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followcamera_->GetViewProjection().matProjection;
	
	viewProjection_.TransferMatrix();
	/*viewProjection_.translation_ = followcamera_->GetViewProjection().translation_;
	viewProjection_.rotation_ = followcamera_->GetViewProjection().rotation_;*/
	player_->Update();
	/*ground_->Update();
	skydome_->Update();*/
	/*viewProjection_.TransferMatrix();*/
	
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
