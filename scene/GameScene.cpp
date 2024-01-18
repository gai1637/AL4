#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"Player.h"
#include"Skydome.h"
#include"Ground.h"
#include"FollowCamera.h"
#include"Enemy.h"

GameScene::GameScene() {}

GameScene::~GameScene() {  }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.farZ = 2000;
	viewProjection_.translation_.y = 2;
	viewProjection_.Initialize();

	modelFighterBody_=std::make_unique<Model>();
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body",true));
	modelFighterHead_=std::make_unique<Model>();
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head",true));
	modelFighterL_arm_=std::make_unique<Model>();
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm",true));
	modelFighterR_arm_=std::make_unique<Model>();
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm",true));
	modelFighterHammer_ = std::make_unique<Model>();
	modelFighterHammer_.reset(Model::CreateFromOBJ("hammer", true));

	modelEnemyBody_ = std::make_unique<Model>();
	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_arm_ = std::make_unique<Model>();
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_ = std::make_unique<Model>();
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));

	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(),
	    modelFighterHead_.get(),
	    modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(),
		modelFighterHammer_.get()
	};
	std::vector<Model*> EnemyModels = {
		
		modelEnemyBody_.get(), 
		modelEnemyL_arm_.get(), 
		modelEnemyR_arm_.get()
	};


	player_ = std::make_unique<Player>();
	player_->Initialize(playerModels);

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(EnemyModels);

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
	enemy_->Update();
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
	enemy_->Draw(viewProjection_);
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
