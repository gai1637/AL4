#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"Player.h"
#include"Skydome.h"
#include"Ground.h"
#include"FollowCamera.h"
#include"Enemy.h"
#include"CollisionManager.h"
#include"Title.h"
#include"Fade.h"
#include"Clear.h"
GameScene::GameScene() {}

GameScene::~GameScene() { 
	
}

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
	EnemyModels = {
		
		modelEnemyBody_.get(), 
		modelEnemyL_arm_.get(), 
		modelEnemyR_arm_.get()
	};

	enemyCounter_ = 0;
	MaxenemyCounter = 1;

	player_ = std::make_unique<Player>();
	player_->Initialize(playerModels);

	enemy_ =std::make_unique<Enemy>();
	enemy_->Initialize(EnemyModels);
	enemies_.push_back(std::move(enemy_));


	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	ground_ = std::make_unique<Ground>();
	ground_->Initialize();

	followcamera_ = std::make_unique<FollowCamera>();
	followcamera_->Initialize();
	
	player_->SetViewProjection(&followcamera_->GetViewProjection());
	followcamera_->SetTarget(&player_->GetWorldTransform());
	
	collisionManager_ = std::make_unique<CollisionManager>();
	collisionManager_->Initialize();
	
	scene = TITLE;

	title_ = std::make_unique<Title>();
	title_->Initialize();

	Fade_ = std::make_unique<Fade>();
	Fade_->Initialize();

	clear_ = std::make_unique<Clear>();
	clear_->Initialize();

	}

void GameScene::Update() { 
	switch (scene) {
	case TITLE:
		title_->Update();
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = GAME;
		}
		break;
	case GAME:
		Fade_->Update();
		GameUpdate();
		break;
	case CLERA:
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = TITLE;
		}
		break;
	}

}

void GameScene::GameUpdate() {
	followcamera_->Update();

	viewProjection_.matView = followcamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followcamera_->GetViewProjection().matProjection;
	
	viewProjection_.TransferMatrix();
	/*viewProjection_.translation_ = followcamera_->GetViewProjection().translation_;
	viewProjection_.rotation_ = followcamera_->GetViewProjection().rotation_;*/
	player_->Update();
	
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
	enemy->Update();
	}
	
	
	
	
	/*ground_->Update();
	skydome_->Update();*/
	/*viewProjection_.TransferMatrix();*/
	collisionManager_->UpdateWorldTransform();
	CheckAllCollisions();
	EnemySpoon();
	if (Fade_->GetColor() >= 1 && Fade_->Getfalg()) {
	scene = CLERA;
	Fade_->Setflag(false);
	}
}
void GameScene::TitleUpdate() {
	if (input_->TriggerKey(DIK_SPACE)) {
	scene = GAME;
	}
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
	switch (scene) {
	case TITLE:

	break;
	case GAME:
		player_->Draw(viewProjection_);
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
	enemy->Draw(viewProjection_);
	}
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	break;
	case CLERA:
	
	break;

	default:
	break;
	}
	/*collisionManager_->Draw(viewProjection_);*/
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	switch (scene) {
	case TITLE:
	title_->Draw();
	break;
	case GAME:
	Fade_->Draw();
	break;
	case CLERA:
		clear_->Draw();
	break;

	default:
	break;
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::CheckAllCollisions() { 
	collisionManager_->Reset();
	collisionManager_->AddCollider(player_.get());
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
	collisionManager_->AddCollider(enemy.get());
	
	}
	collisionManager_->AddCollider(player_->GetHammer().get());
	collisionManager_->CheckAllCollisions();
	
}
void GameScene::EnemySpoon() { 
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
	if (enemy->GetReset()) {
		enemy->SetPos({
			static_cast<float>(rand() % 100),
			0,
			static_cast<float>(rand() % 100),
		});
		enemy->Reset(false);
		enemycount_++;
	}
	}
	if (enemycount_ >= 1) {
	Fade_->Setflag(true);
	enemycount_ = 0;
	}
}