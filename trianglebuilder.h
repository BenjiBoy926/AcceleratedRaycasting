#pragma once

#include <vector>
#include "triangle.h"
#include <nori/mesh.h>

class Triangle3fBuilder
{
public:
	static std::vector<Triangle3f> fromMesh(const nori::Mesh*);

private:
	Triangle3fBuilder() {}
	~Triangle3fBuilder() {}
};
