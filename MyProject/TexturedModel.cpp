#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel model, const ModelTex tex) : model(model), tex(tex) {
}

RawModel TexturedModel::getRawModel()
{
	return model;
}

ModelTex TexturedModel::getModelTex() {
	return tex;
}

