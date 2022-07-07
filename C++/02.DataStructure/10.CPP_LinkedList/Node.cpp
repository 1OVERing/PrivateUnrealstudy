#include "Node.h"

Node::Node() : Data(), Next(nullptr)
{}

Node::Node(int data) : Data(data), Next(nullptr)
{}

Node::~Node()
{
}
std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os << "Data : " << node.Data;
}