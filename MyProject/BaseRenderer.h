#pragma once
#include <glad\glad.h>

class BaseRenderer {
protected:
	void enableBackCulling();
	void disableBackCulling();
	BaseRenderer();
};
