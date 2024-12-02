#pragma once

#include <simple.h>
#include <simpleList.h>
#include "simpleGraphNode.h"
#include "simpleGraphEdge.h"
#include <concepts>
#include <functional>
#include <type_traits>

namespace simple::math
{
	// Abstract graph constraints
	template <typename TNode>
	concept isGraphNode = std::convertible_to<simpleGraphNode>;

	template <typename TEdge, typename TNode>
	concept isGraphEdge = std::convertible_to<TEdge, simpleGraphEdge<TNode>> &&
		std::convertible_to<TNode, simpleGraphNode>;

	// Graph Delegates
	template <isGraphNode TNode1, isGraphNode TNode2>
	using graphNodeConstructor = std::function<TNode2 (const TNode1& node)>;

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	using graphEdgeConstructor = std::function<TEdge (const TNode& node1, const TNode& node2)>;

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	using graphSimpleNodeIterator = std::function<iterationCallback (const TNode& node)>;

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	using graphSimpleEdgeIterator = std::function<iterationCallback (const TEdge& edge)>;

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	using graphIterator = std::function<iterationCallback (const TNode& node, const simpleList<TEdge>& adjacentEdges)>;
}
