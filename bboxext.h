#pragma once

#include <nori/common.h>
#include <nori/bbox.h>
#include <array>

class BoundingBox3fExt
{
public:
	static nori::BoundingBox3f getOctant(const nori::BoundingBox3f&, int);
	static std::array<nori::BoundingBox3f, 8> getOctants(const nori::BoundingBox3f&);

private:
	BoundingBox3fExt();
	~BoundingBox3fExt();
};
