#include "Fade.h"
#include"TextureManager.h"
void Fade::Initialize() { 
	png = TextureManager::Load("black.png");
	sprite.reset(Sprite::Create(png, {0, 0}));
	color = 1.f;
	flag = false;
}
void Fade::Update() { 
	if (!flag) {
		if (color >= 0)
			color -= 0.003f;
		
	} else {
		if (color<=1) {
			color += 0.003f;
		}
	}
	sprite->SetColor({0, 0, 0, color});
}
void Fade::Draw() { sprite->Draw(); }