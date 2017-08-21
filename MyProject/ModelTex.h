#ifndef MODELTEX_H
#define MODELTEX_H
#include <vector>
using namespace std;
class ModelTex {
	std::vector<unsigned int> texture;
	
public:
	ModelTex();
	void addTexture(unsigned int texture);
	unsigned int getNumTextures();
	unsigned int getTexture(unsigned int index);
};
#endif
