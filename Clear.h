#pragma once
#include"Sprite.h"
#include"TextureManager.h"
#include<memory>
class Clear {
public:
	void Initialize();
	
	void Draw();

private:
	int png;
	std::unique_ptr<Sprite> sprite_;
};
