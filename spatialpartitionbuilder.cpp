#include "spatialpartitionbuilder.h"
#include "trianglebuilder.h"

SpatialPartition3f SpatialPartition3fBuilder::fromMesh(const nori::Mesh* mesh) {
	return SpatialPartition3f(mesh->getBoundingBox(), Triangle3fBuilder::fromMesh(mesh));
}