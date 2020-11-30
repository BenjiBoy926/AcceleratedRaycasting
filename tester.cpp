#include "tester.h"
#include "octtreebuilder.h"

std::string testTriangleInsideHelper(const nori::BoundingBox3f& box, const std::array<Triangle3f, 3>& tri, bool strict) {
	std::ostringstream stream;

	stream << "BEGIN SUBTEST - Strictness: " << strict << std::endl << std::endl;
	for (int i = 0; i < 3; i++) {
		stream << "-- Test triangle:" << std::endl;
		stream << tri[i].toString() << std::endl;
		stream << "result: " << tri[i].inside(box, strict) << std::endl << std::endl;
	}
	stream << "END SUBTEST";

	return stream.str();
}

std::string Tester::testTriangleInside(const nori::Mesh* mesh) {
	std::ostringstream stream;

	nori::BoundingBox3f box(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(1.0, 1.0, 1.0));
	std::array<Triangle3f, 3> triangles = {
		Triangle3f(mesh, 0),
		Triangle3f(mesh, 1),
		Triangle3f(mesh, 2)
	};

	stream << "BEGIN TEST - triangle inside" << std::endl;
	stream << "Example box: " << box.toString() << std::endl << std::endl;

	// Test strictly inside
	stream << testTriangleInsideHelper(box, triangles, true) << std::endl << std::endl;

	// Test roughly inside
	stream << testTriangleInsideHelper(box, triangles, false) << std::endl << std::endl;

	stream << "END TEST";

	return stream.str();
}

std::string Tester::testGetOctant() {
	std::ostringstream stream;

	std::array<nori::BoundingBox3f, 3> boxes = {
		nori::BoundingBox3f(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(2.0, 2.0, 2.0)),
		nori::BoundingBox3f(nori::Point3f(-2.0,-2.0, -2.0), nori::Point3f(0.0, 0.0, 0.0)),
		nori::BoundingBox3f(nori::Point3f(-1.0, -1.0, -1.0), nori::Point3f(1.0, 1.0, 1.0))
	};
	std::array<nori::BoundingBox3f, 8> octants;

	stream << "BEGIN TEST - octants" << std::endl << std::endl;

	for (int i = 0; i < boxes.size(); i++) {
		octants = BoundingBox3fExt::getOctants(boxes[i]);

		stream << "For box: " << boxes[i].toString() << std::endl;
		//stream << "Box center: " << boxes[i].getCenter().toString() << std::endl;
		for (int i = 0; i < octants.size(); i++) {
			stream << "\tOctant #" << i << ": " << octants[i].toString() << std::endl;
		}
		stream << std::endl;
	}

	stream << "END TEST";

	return stream.str();
}

std::string Tester::testEightfoldPartition(const nori::Mesh* mesh) {
	std::ostringstream stream;

	std::array<SpatialPartition3f, 2> initPartitions = {
		SpatialPartition3f(
			nori::BoundingBox3f(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(5.0, 5.0, 5.0)),
			{
				Triangle3f(mesh, 0),
				Triangle3f(mesh, 1),
				Triangle3f(mesh, 2),
				Triangle3f(mesh, 3),
				Triangle3f(mesh, 4),
				Triangle3f(mesh, 5),
				Triangle3f(mesh, 6),
				Triangle3f(mesh, 7)
			}
		),
		SpatialPartition3f(
			nori::BoundingBox3f(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(3.0, 3.0, 3.0)),
			{
				Triangle3f(mesh, 0),
				Triangle3f(mesh, 1)
			}
		)
	};
	std::array<SpatialPartition3f, 8> octants;

	stream << "BEGIN TEST - eightfold partitions" << std::endl << std::endl;

	for (int i = 0; i < initPartitions.size(); i++) {
		stream << "For partition: " << initPartitions[i].toString() << std::endl;
		octants = initPartitions[i].eightfoldPartition();
		stream << "Octants:" << std::endl;

		for (int j = 0; j < octants.size(); j++) {
			stream << octants[j].toString() << std::endl;
		}
		stream << std::endl;
	}

	stream << "END TEST";

	return stream.str();
}

std::string Tester::testOctreePartition(const nori::Mesh* mesh) {
	std::ostringstream stream;

	std::array<SpatialPartition3f, 2> initPartitions = {
		SpatialPartition3f(
			nori::BoundingBox3f(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(5.0, 5.0, 5.0)),
			{
				Triangle3f(mesh, 0),
				Triangle3f(mesh, 1),
				Triangle3f(mesh, 2),
				Triangle3f(mesh, 3),
				Triangle3f(mesh, 4),
				Triangle3f(mesh, 5),
				Triangle3f(mesh, 6),
				Triangle3f(mesh, 7)
			}
		),
		SpatialPartition3f(
			nori::BoundingBox3f(nori::Point3f(0.0, 0.0, 0.0), nori::Point3f(3.0, 3.0, 3.0)),
			{
				Triangle3f(mesh, 0),
				Triangle3f(mesh, 1)
			}
		)
	};
	OctTree<SpatialPartition3f> tree;

	stream << "BEGIN TEST - Octree Constructrion by Spatial Partition" << std::endl << std::endl;

	for (int i = 0; i < initPartitions.size(); i++) {
		stream << "SUBTEST #" << i << std::endl;
		stream << "Partition: " << initPartitions[i].toString();
		
		tree = OctTreeBuilder::octreePartition(initPartitions[i], 2, 5);

		stream << "Resulting tree:" << std::endl;
		stream << tree.toString("\t") << std::endl << std::endl;
	}

	stream << "END TEST";

	return stream.str();
}

std::string Tester::testAll(const nori::Mesh* mesh) {
	std::ostringstream stream;

	stream << testTriangleInside(mesh) << std::endl;
	stream << testGetOctant() << std::endl;
	stream << testEightfoldPartition(mesh) << std::endl;
	stream << testOctreePartition(mesh) << std::endl;

	return stream.str();
}