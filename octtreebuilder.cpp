#include "octtreebuilder.h"
#include "spatialpartitionbuilder.h"

OctTree<SpatialPartition3f> OctTreeBuilder::octreePartition(
	const nori::Mesh* mesh, 
	int triangleThreshold, 
	int depthThreshold) 
{
	return octreePartition(
		SpatialPartition3fBuilder::fromMesh(mesh),
		triangleThreshold, 
		depthThreshold
	);
}

OctTree<SpatialPartition3f> OctTreeBuilder::octreePartition(
	const SpatialPartition3f& partition,
	int triangleThreshold,
	int depthThreshold)
{
	return OctTree<SpatialPartition3f>(
		octreePartitionRecursive(
			partition,
			triangleThreshold,
			depthThreshold,
			0
		)
	);
}

OctNode<SpatialPartition3f> OctTreeBuilder::octreePartitionRecursive(
	const SpatialPartition3f& partition,  
	int triangleThreshold, 
	int depthThreshold, 
	int currentExecution) 
{
	std::cout << "Octree recursive call" << std::endl;
	// Check threshold values to see if we have reached the base case of the recursion
	if (partition.getTriangles().size() <= triangleThreshold || 
		currentExecution >= depthThreshold) 
	{
		std::cout << "Reached base case" << std::endl;
		return OctNode<SpatialPartition3f>(partition);
	}

	std::cout << "Skipped recursive case" << std::endl;
	std::cout << "Building eightfold paritition..." << std::endl;

	// Split up the current partition into eight sub-partitions
	std::array<SpatialPartition3f, 8> octants = partition.eightfoldPartition();

	std::cout << "Creating node..." << std::endl;
	// Initialize the current root
	OctNode<SpatialPartition3f> root = OctNode<SpatialPartition3f>(partition);

	for (int i = 0; i < 8; i++) {
		std::cout << "Processing child #" << i << std::endl;
		OctNode<SpatialPartition3f> child = octreePartitionRecursive(
			octants[i], 
			triangleThreshold, 
			depthThreshold, 
			currentExecution + 1
		);
		root.push_back(child);
	}

	std::cout << "Returning root" << std::endl;
	return root;
}