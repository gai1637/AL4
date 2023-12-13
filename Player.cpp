#include "Player.h"
#include "TextureManager.h"
#include <cassert>
void Player::Initialize() { 
	textureHandle_ = TextureManager::Load("mario.jpg");
	
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create());
	worldTransform_.Initialize();
	viewProjection_.Initialize();

}
Player::~Player() {
	
	
}
void Player::Draw() { 
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}