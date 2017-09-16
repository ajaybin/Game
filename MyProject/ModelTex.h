#ifndef MODELTEX_H
#define MODELTEX_H
#include <vector>
using namespace std;
class ModelTex {
	std::vector<unsigned int> texture;
	float shineFactor;
	float reflectivity;

public:
	bool isTransparent;
	bool useFakeLight;
	ModelTex(float shineFactor, float reflectivity);
	void addTexture(unsigned int texture);
	unsigned int getNumTextures();
	unsigned int getTexture(unsigned int index);
	float getReflectivity();
	float getShineFactor();
};
#endif
