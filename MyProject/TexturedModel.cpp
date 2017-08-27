#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel *model, ModelTex *tex) {
	this->model = model;
	this->tex = tex;
}

RawModel* TexturedModel::getRawModel()
{
	return model;
}

ModelTex* TexturedModel::getModelTex() {
	return tex;
}

