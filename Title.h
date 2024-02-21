#pragma once
#include"Sprite.h"
class Title {
public:
	void Initialize();
	void Update();
	void Draw();
	~Title();

private:
	uint32_t png[4] = {0,0,0,0};
	int num;
	int numcount;
	Sprite* sprite[4] = {nullptr,nullptr,nullptr,nullptr};

};
