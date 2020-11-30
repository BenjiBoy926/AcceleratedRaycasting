#include "spatialpartition.h"

nori::BoundingBox3f SpatialPartition3f::getBoundingBox() const {
	return boundingBox;
}

std::vector<Triangle3f> SpatialPartition3f::getTriangles() const {
	return triangles;
}

std::array<SpatialPartition3f, 8> SpatialPartition3f::eightfoldPartition() const {
	std::array<SpatialPartition3f, 8> partition = {};
	
	nori::BoundingBox3f partBox;
	std::vector<Triangle3f> subTriangles;

	for (int i = 0; i < 8; i++) {

		// Create the part box
		partBox = BoundingBox3fExt::getOctant(boundingBox, i);

		// Add all triangles that overlap the current box
		for each (Triangle3f tri in triangles)
		{
			if (tri.inside(partBox, false)) {
				subTriangles.push_back(tri);
			}
		}

		// Add the spatial partition with the sub triangles
		partition[i] = SpatialPartition3f(partBox, subTriangles);
		subTriangles.clear();
	}

	return partition;
}

std::string SpatialPartition3f::toString(const std::string& prefix) const {
	std::ostringstream stream;

	stream << prefix << "SpatialPartition3f: {" << std::endl;
	stream << prefix << "\tbox: " << boundingBox.toString() << std::endl;
	stream << prefix << "\ttriangles: [" << std::endl;

	// Insert strings of each triangle
	for (int i = 0; i < triangles.size(); i++) {
		stream << prefix << triangles[i].toString(prefix + "\t\t");
		if (i < (triangles.size() - 1)) {
			stream << ", ";
		}
		stream << std::endl;
	}

	stream << prefix << "\t]" << std::endl;
	stream << prefix << "}";

	return stream.str();
}

std::ostream& operator<<(std::ostream& out, const SpatialPartition3f& partition) {
	return out << partition.toString();
}