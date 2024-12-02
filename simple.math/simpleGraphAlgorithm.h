#pragma once

#include "simpleGraph.h"
#include <simple.h>
#include <simpleException.h>
#include <simpleList.h>
#include <simpleListExtension.h>

namespace simple::math
{
	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	class simpleGraphAlgorithm
	{
	public:
		simpleGraphAlgorithm();
		~simpleGraphAlgorithm();

		virtual simpleGraph<TNode, TEdge>* run(const simpleList<TNode>& vertices,
		                                       graphEdgeConstructor<TNode, TEdge> edgeConstructor);

		simpleGraph<TNode, TEdge>* createFullGraph(const simpleList<TNode>& vertices,
		                                           graphEdgeConstructor<TNode, TEdge> edgeConstructor);

	protected:
		/// <summary>
		/// Returns FULL GRAPH:  Fully connected graph of all nodes
		/// </summary>
		simpleGraph<TNode, TEdge>* createDefaultGraph(const simpleList<TNode>& vertices,
		                                              graphEdgeConstructor<TNode, TEdge> edgeConstructor);
	};

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraphAlgorithm<TNode, TEdge>::simpleGraphAlgorithm()
	{
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraphAlgorithm<TNode, TEdge>::~simpleGraphAlgorithm()
	{
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>* simpleGraphAlgorithm<TNode, TEdge>::run(const simpleList<TNode>& vertices,
	                                                                   graphEdgeConstructor<TNode, TEdge>
	                                                                   edgeConstructor)
	{
		throw simpleException("Must override the run function in a child class:  graphAlgorithm.h");
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>* simpleGraphAlgorithm<TNode, TEdge>::createFullGraph(const simpleList<TNode>& vertices,
		graphEdgeConstructor<TNode, TEdge>
		edgeConstructor)
	{
		return createDefaultGraph(vertices);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>* simpleGraphAlgorithm<TNode, TEdge>::createDefaultGraph(
		const simpleList<TNode>& vertices, graphEdgeConstructor<TNode, TEdge> edgeConstructor)
	{
		if (vertices.count() == 0)
			throw simpleException("Trying to make a graph with zero vertices: delaunay.h");

		else if (vertices.count() == 1)
		{
			return new simpleGraph<TNode, TEdge>(vertices.toArray());
		}

		else
		{
			simpleList<TEdge> edges;

			simpleListExtension<TNode>::distinctPairs(vertices, vertices,
			                                          [&edges, &edgeConstructor](const TNode& node1, const TNode& node2)
			                                          {
				                                          edges.add(edgeConstructor(node1, node2));
			                                          });

			return new simpleGraph<TNode, TEdge>(vertices.toArray(), edges.toArray());
		}
	}
}
