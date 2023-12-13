#include "Ground.h"
void Ground::Initialize() { 
	model_ = std::make_unique<Model>();
	model_.reset(Model::CreateFromOBJ("ground",true));
	worldTransform_.Initialize();
}
void Ground::Draw(ViewProjection& viewprojection_) {
	model_->Draw(worldTransform_, viewprojection_);
}