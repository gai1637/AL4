#pragma once
#include"Sprite.h"
#include<memory>
class Fade {
public:
	void Initialize();
	void Update();
	void Draw();
	float GetColor() { return color; }
	void Setflag(bool num) { flag = num; }
	bool Getfalg() { return flag; }
	float Getcolor() { return color; }

private:
	int png;
	std::unique_ptr<Sprite> sprite;
	float color;
	bool flag;
};
