#pragma once
#include "object.h"
#include "camera.h"

struct Scene
{
	Object* obj;
	Color bg_color;
	Camera* cam;
	bool use_skybox;
};