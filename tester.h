#pragma once

#include "../../../nori_codebase/nori/include/nori/accel.h"
#include <sstream>

class Tester
{
public:
	static std::string testTriangleInside(const nori::Mesh*);
	static std::string testGetOctant();
	static std::string testEightfoldPartition(const nori::Mesh*);
	static std::string testOctreePartition(const nori::Mesh*);

	static std::string testAll(const nori::Mesh*);

private:
	Tester() {}
	~Tester() {}
};
