#include "triangle.h"
#include <stdexcept>

nori::Vector3f Triangle3f::getPoint(int i) const {
	if (i < 0 || i >= 3) {
		throw std::out_of_range("Index is out of range: " + std::to_string(i));
	}
	nori::MatrixXf positions = mesh->getVertexPositions();
	nori::MatrixXu indeces = mesh->getIndices().col(index);
	return positions(indeces(i));
}

bool Triangle3f::inside(const nori::BoundingBox3f& bbox, bool strict) const {
	if (strict) {
		return bbox.contains(getPoint(0)) && bbox.contains(getPoint(1)) && bbox.contains(getPoint(2));
	}
	else {
		return bbox.contains(getPoint(0)) || bbox.contains(getPoint(1)) || bbox.contains(getPoint(2));
	}
}

std::string Triangle3f::toString(const std::string& prefix) const {
	std::ostringstream stream;

	stream << prefix << "Triangle: {" << std::endl;

	for (int i = 0; i < 3; i++) {
		stream << prefix << "\tp" << i << ": " << getPoint(i).toString();

		// Input comma if not final point
		if (i < 2) {
			stream << ", ";
		}
		stream << std::endl;
	}

	stream << prefix << "}";

	return stream.str();
}

std::ostream& operator<<(std::ostream& out, const Triangle3f& tri) {
	return out << tri.toString();
}