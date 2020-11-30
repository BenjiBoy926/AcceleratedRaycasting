#pragma once

#include <array>
#include <string>
#include <sstream>
#include <iomanip>
#include <nori/vector.h>
#include <nori/bbox.h>
#include <nori\common.h>
#include <nori/mesh.h>

class Triangle3f
{
public:
	Triangle3f() : mesh(nullptr), index((uint32_t)-1) {}
	Triangle3f(const nori::Mesh* mesh, uint32_t index) : mesh(mesh), index(index) {}
	~Triangle3f() {}

	// Get the triangle point at the specified index
	nori::Vector3f getPoint(int) const;

	// Determine if the triangle is inside the bounding box
	bool inside(const nori::BoundingBox3f&, bool strict) const;

	// Get a string of the triangle
	std::string toString(const std::string& = "") const;

	// Insertion operator
	friend std::ostream& operator << (std::ostream&, const Triangle3f&);

private:
	const nori::Mesh* mesh;	// Borrowed pointer to the mesh that contains the triangle points
	uint32_t index;			// Index in the mesh where the triangle points are found
};
