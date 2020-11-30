#pragma once

#include "spatialpartition.h"
#include <nori/mesh.h>

class SpatialPartition3fBuilder
{
public:
	static SpatialPartition3f fromMesh(const nori::Mesh*);

private:
	SpatialPartition3fBuilder();
	~SpatialPartition3fBuilder();
};
