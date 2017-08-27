#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H
#include <RawModel.h>
#include <ModelTex.h>
class TexturedModel {
	RawModel *model;
	ModelTex *tex;
public:
	TexturedModel(RawModel *model, ModelTex *tex);
	RawModel* getRawModel();
	ModelTex* getModelTex();
};
#endif
