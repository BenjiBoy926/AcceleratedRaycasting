#include "trianglebuilder.h"

std::vector<Triangle3f> Triangle3fBuilder::fromMesh(const nori::Mesh* mesh) {
	std::vector<Triangle3f> triangles;
	
	for (int i = 0; i < mesh->getVertexCount(); i++) {
		triangles.push_back(Triangle3f(mesh, i));
	}

	return triangles;
}