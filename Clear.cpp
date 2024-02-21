#include "Clear.h"
void Clear::Initialize() { 
	png = TextureManager::Load("GameClear.png"); 
	sprite_ = std::make_unique<Sprite>();
	sprite_.reset(Sprite::Create(png, {0, 0}));
}
void Clear::Draw() { sprite_->Draw(); }