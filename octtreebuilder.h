#pragma once

#include <nori/mesh.h>
#include "octtree.h"
#include "spatialpartition.h"
#include "trianglebuilder.h"
#include "tester.h"

class OctTreeBuilder
{
public:
	static OctTree<SpatialPartition3f> octreePartition(const nori::Mesh*, int, int);
	static OctTree<SpatialPartition3f> octreePartition(const SpatialPartition3f&, int, int);

private:
	OctTreeBuilder() {}
	~OctTreeBuilder() {}

	// Recursive function returns the root OctNode for an OctTree
	// If the number of triangles in the mesh is less than the threshold, 
	// the function returns an OctNode containing those triangles
	// If the number of triangles is higher than the threshold, the space is
	// subdivided into eight parts and this function is called again for each OctNode child
	static OctNode<SpatialPartition3f> octreePartitionRecursive(const SpatialPartition3f&, int, int, int);
};
