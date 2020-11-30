#pragma once

#include "octnode.h"

template<typename DataType>
class OctTree {
public:
	// Default, copy constructor, move constructors
	OctTree() {}	
	OctTree(const OctTree<DataType>& other) : root(other.root) {}
	OctTree(OctTree<DataType>&& other) : root(other.root) {}
	// Other constructor
	OctTree(const OctNode<DataType>& r) : root(r) {}
	// Destructor
	~OctTree() {}

	// Tree as a string
	std::string toString(const std::string& prefix) {
		return "TREE: " + root.toString(prefix);
	}

	// Copy and move assignment
	OctTree<DataType>& operator=(const OctTree<DataType>& other) {
		root = other.root;
		return *this;
	}
	OctTree<DataType>& operator=(OctTree<DataType>&& other) {
		root = other.root;
		return *this;
	}

private:
	OctNode<DataType> root;	// Root node in the tree
};