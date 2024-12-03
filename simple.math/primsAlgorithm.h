#pragma once

#include <simple.h>
#include <simpleException.h>
#include <simpleList.h>
#include "simpleGraph.h"
#include "simpleGraphAlgorithm.h"
#include "simplePoint.h"
#include "simpleLine.h"
#include <limits>

namespace simple::math
{
	using namespace simple;

	/// <summary>
	/// Defines the Minimum Spanning Tree (MST) algorithm Prim's Algorithm
	/// </summary>
	class primsAlgorithm : public simpleGraphAlgorithm<simplePoint<float>, simpleLine<float>>
	{
	public:
		primsAlgorithm()
		{
		};

		~primsAlgorithm()
		{
		};

		simpleGraph<simplePoint<float>, simpleLine<float>>*
		run(const simpleList<simplePoint<float>>& vertices,
		    graphEdgeConstructor<simplePoint<float>, simpleLine<float>> edgeConstructor) override;
	};

	simpleGraph<simplePoint<float>, simpleLine<float>>* primsAlgorithm::run(
		const simpleList<simplePoint<float>>& vertices,
		graphEdgeConstructor<simplePoint<float>, simpleLine<float>> edgeConstructor)
	{
		if (vertices.count() < 3)
			return this->createDefaultGraph(vertices, edgeConstructor);

		// Procedure (Prim's Algorithm)
		//
		// 1) Start the tree with a single vertex
		// 2) Calculate edges of the graph that connect NEW points not yet in the tree (P)
		//    to the existing tree points (T)
		// 3) Choose the least distant edge and add that edge to the tree
		//

		primsAlgorithm* that = this;

		simpleList<simplePoint<float>> unusedVertices(vertices);
		simpleList<simplePoint<float>> usedVertices;
		simpleList<simpleLine<float>> treeEdges;

		while (usedVertices.count() < vertices.count())
		{
			simplePoint<float> nextVertex = default_value::value<simplePoint<float>>();
			simpleLine<float> nextEdge = default_value::value<simpleLine<float>>();

			// Initialize the tree
			if (treeEdges.count() == 0)
			{
				simplePoint<float> firstVertex = unusedVertices.get(0);

				// Remove the first vertex - add to the used collection
				unusedVertices.remove(firstVertex);
				usedVertices.add(firstVertex);

				nextVertex = unusedVertices.withMin<double>([&firstVertex] (const simplePoint<float>& vertex)
				{
					return firstVertex.distance(vertex);
				});

				nextEdge = edgeConstructor (firstVertex, nextVertex);
			}

			else
			{
				//Get the next edge that connects an UNUSED vertex to a USED vertex
				for (int index = 0; index < unusedVertices.count (); index++)
				{
					// Edges in the current tree
					simplePoint<float> vertex = unusedVertices.get (index);

					float potentialEdgeWeight = std::numeric_limits<float>::max ();
					simplePoint<float> potentialNode = default_value::value<simplePoint<float>> ();

					for (int edgeIndex = 0; edgeIndex < treeEdges.count (); edgeIndex++)
					{
						simpleLine<float> edge = treeEdges.get (edgeIndex);
						float distance = edge.node1.distance (vertex);

						if (distance < potentialEdgeWeight)
						{
							potentialEdgeWeight = distance;
							potentialNode = edge.node1;
						}

						distance = edge.node2.distance (vertex);

						if (distance < potentialEdgeWeight)
						{
							potentialEdgeWeight = distance;
							potentialNode = edge.node2;
						}
					}

					// Check both potential edges for the least distant choice
					if (nextEdge == default_value::value<simpleLine<float>> () || potentialEdgeWeight < nextEdge.weight ())
					{
						nextEdge = edgeConstructor (potentialNode, vertex);
						nextVertex = vertex;
					}
				}
			}

			if (nextEdge == default_value::value<simpleLine<float>>())
				throw simpleException("No connection found between regions Minimum Spanning Tree:  primsAlgorithm.h");

			unusedVertices.remove(nextVertex);
			usedVertices.add(nextVertex);

			// Add next connection to the tree
			treeEdges.add(nextEdge);
		}

		return new simpleGraph<simplePoint<float>, simpleLine<float>>(vertices.toArray(), treeEdges.toArray());
	}
}
