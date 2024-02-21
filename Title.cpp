#include "Title.h"
#include"TextureManager.h"
#include "DirectXCommon.h"
Title::~Title() {
	for (int i = 0; i < 4; i++) {
		delete sprite[i];
	}}
void Title::Initialize() { 
	png[0] = TextureManager::Load("Hunting1.png"); 
	png[1] = TextureManager::Load("Hunting2.png"); 
	png[2] = TextureManager::Load("Hunting3.png"); 
	png[3] = TextureManager::Load("Hunting4.png"); 
	for (int i = 0; i < 4; i++) {
		sprite[i] = Sprite::Create(png[i], {0, 0});
		
	}
}
void Title::Update() { 
	numcount++; 
	if (numcount >= 30) {
		num++;
		numcount = 0;
		if (num >= 3) {

			num = 0;
		}
	}
}
void Title::Draw() { sprite[num]->Draw(); }