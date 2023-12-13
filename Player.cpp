#include "Player.h"
#include "TextureManager.h"
#include <cassert>
void Player::Initialize() { 

	model_ = std::make_unique<Model>();
	model_.reset(Model::CreateFromOBJ("float",true));
	worldTransform_.Initialize();
	viewProjection_.Initialize();

}
Player::~Player() {
	
	
}
void Player::Draw() { 
	model_->Draw(worldTransform_, viewProjection_);
}