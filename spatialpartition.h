#pragma once

#include "triangle.h"
#include <nori/bbox.h>
#include "bboxext.h"

class SpatialPartition3f
{
public:
	SpatialPartition3f() : boundingBox(nori::BoundingBox3f()), triangles(std::vector<Triangle3f>()) {}
	SpatialPartition3f(nori::BoundingBox3f b, std::vector<Triangle3f> t) : boundingBox(b), triangles(t) {}
	~SpatialPartition3f() {}

	// Get the bounding box of the spatial partition
	nori::BoundingBox3f getBoundingBox() const;
	// Get the triangles of the spatial partition
	std::vector<Triangle3f> getTriangles() const;

	// Build an eightfold partition of the current partition
	std::array<SpatialPartition3f, 8> eightfoldPartition() const;

	// Get the partition as a string
	std::string toString(const std::string& = "") const;
	friend std::ostream& operator << (std::ostream&, const SpatialPartition3f&);

private:
	nori::BoundingBox3f boundingBox;
	std::vector<Triangle3f> triangles;
};
