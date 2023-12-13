#include "Skydome.h"
void Skydome::Initialize() { 
	model_ = std::make_unique<Model>();
	model_.reset(Model::CreateFromOBJ("skydome",true));
	worldTransform_.Initialize();
	
}
void Skydome::Draw(ViewProjection &viewprojection_) { 
	model_->Draw(worldTransform_, viewprojection_);
}