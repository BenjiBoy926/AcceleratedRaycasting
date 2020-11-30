#pragma once

//#include "octchildren.h"
#include <stdexcept>
#include <array>

template <typename DataType>
class OctNode
{
public:
	// CONSTRUCTORS
	// Default, copy, move constructors
	OctNode() {}
	OctNode(const OctNode<DataType>& other) : data(other.data), children(other.children) {}
	OctNode(OctNode<DataType>&& other) : data(other.data), children(other.children) {}
	// Field constructor
	OctNode(DataType d) : data(d) {}

	// DESTRUCTOR
	~OctNode() {}

	// Push a child to the back.  Throw exception if more than eight children are pushed
	void push_back(const OctNode<DataType>& child) {
		if (children.size() > 8) {
			throw std::out_of_range("Cannot add more than eight children to an oct node");
		}
		children.push_back(child);
	}
	// Get a child at the index
	OctNode<DataType>& at(int index) {
		return children.at(index);
	}
	// Get the number of children
	int size() {
		return children.size();
	}

	// Convert node to a readable string
	std::string toString(const std::string& prefix) {
		std::ostringstream stream;

		stream << prefix << "OctNode:{" << std::endl;
		stream << prefix << "\tdata:{" << std::endl;
		stream << prefix << data << std::endl;
		stream << prefix << "\t}" << std::endl;

		stream << prefix << "\tchildren:[" << std::endl;

		for (int i = 0; i < children.size(); i++) {
			stream << prefix << "\t\t[" << i << "]:{" << std::endl;
			stream << children[i].toString(prefix + "\t\t\t");
			stream << prefix << "\t\t}" << std::endl;
		}
		stream << prefix << "\t]" << std::endl;
		stream << prefix << "}";

		return stream.str();
	}

	// OPERATORS

	// Insertion operator
	friend std::ostream& operator<<(std::ostream& out, const OctNode<DataType>& node) {
		return out << node.toString();
	}
	// Index operator
	OctNode<DataType>& operator[](int index) {
		return children[index];
	}
	// Copy and move assignment
	OctNode<DataType>& operator=(const OctNode<DataType>& other) {
		data = other.data;
		children = other.children;
		return *this;
	}
	OctNode<DataType>& operator=(OctNode<DataType>&& other) {
		data = other.data;
		children = other.children;
		return *this;
	}

private:
	DataType data;
	std::vector<OctNode<DataType>> children;
};
