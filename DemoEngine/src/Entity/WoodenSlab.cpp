#include "WoodenSlab.h"

WoodenSlab::WoodenSlab()
{
	model = Model("C:/Users/sammo/Documents/Projects/DemoEngine/models/woodenslab/woodenslab.dae");
	bboxMin = model.meshes[0].bboxMin;
	bboxMax = model.meshes[0].bboxMax;
}

void WoodenSlab::update()
{
	draw();
}