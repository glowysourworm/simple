#pragma once

#include <simple.h>

namespace simple::math
{
	template <isHashable TNode>
	struct simpleGraphEdge : simpleStruct
	{
	public:
		TNode node1;
		TNode node2;

		simpleGraphEdge()
		{
			node1 = default_value::value<TNode>();
			node2 = default_value::value<TNode>();
		}

		simpleGraphEdge(const TNode& anode1, const TNode& anode2)
		{
			node1 = anode1;
			node2 = anode2;
		}

		simpleGraphEdge(const simpleGraphEdge& copy)
		{
			node1 = copy.node1;
			node2 = copy.node2;
		}
		virtual ~simpleGraphEdge() {}

		virtual float weight() const
		{
			throw simpleException ("Function must be overridde in a child class:  simpelGraphEdge::weight");
		}

		virtual void operator=(const simpleGraphEdge& copy)
		{
			node1 = copy.node1;
			node2 = copy.node2;
		}

		virtual bool operator==(const simpleGraphEdge& edge) const
		{
			return compare(edge);
		}

		virtual bool operator!=(const simpleGraphEdge& edge) const
		{
			return !compare(edge);
		}

		virtual size_t getHash() const override
		{
			return hashGenerator::generateHash(node1, node2);
		}

	private:

		bool compare(const simpleGraphEdge& edge) const
		{
			return (node1 == edge.node1 && node2 == edge.node2) ||
				   (node1 == edge.node2 && node2 == edge.node1);
		}
	};
}
