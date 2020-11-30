#include "bboxext.h"

nori::BoundingBox3f BoundingBox3fExt::getOctant(const nori::BoundingBox3f& bbox, int octant) {
	if (octant < 0 || octant >= 8) {
		throw std::out_of_range("Octant is invalid: " + std::to_string(octant));
	}
	
	// Store extents of the box for convenience
	nori::Vector3f midVector = bbox.getCenter() - bbox.min;

	// Get a transform vector that will be added to the box's min
	nori::Vector3f transform = nori::Vector3f(
		midVector.x() * (octant % 2),
		midVector.y() * ((octant / 2) % 2),
		midVector.z() * (octant / 4)
	);

	// Return the bounding box
	return nori::BoundingBox3f(
		bbox.min + transform,
		bbox.min + midVector + transform
	);
}

std::array<nori::BoundingBox3f, 8> BoundingBox3fExt::getOctants(const nori::BoundingBox3f& bbox) {
	std::array<nori::BoundingBox3f, 8> ret = {};
	for (int i = 0; i < 8; i++) {
		ret[i] = getOctant(bbox, i);
	}
	return ret;
}