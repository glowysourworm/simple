#pragma once

#include "simpleGraphDefinitions.h"
#include "simpleGraphEdgeCollection.h"
#include "simpleGraphNode.h"
#include "simpleGraphEdge.h"
#include <simple.h>
#include <simpleArray.h>
#include <simpleList.h>
#include <functional>

namespace simple::math
{
	/// <summary>
	/// Defines a graph with type constraints for graphNode, and graphEdge
	/// </summary>
	/// <typeparam name="TValue">Type for the node value</typeparam>
	/// <typeparam name="TWeight">Type for the node weight</typeparam>
	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	class simpleGraph
	{
	public:
		simpleGraph();
		simpleGraph(const simpleArray<TNode>& nodes, const simpleArray<TEdge>& edges);
		simpleGraph(const simpleArray<TNode>& nodes);
		simpleGraph(const simpleGraph<TNode, TEdge>& copy);
		~simpleGraph();

		void addEdge(const TEdge& edge);
		void modify(const TEdge& existingEdge, const TEdge& newEdge);
		simpleList<TEdge> getAdjacentEdges(const TNode& node) const;
		TEdge findEdge(const TNode& node1, const TNode& node2) const;
		bool containsEdge(const TEdge& edge) const;
		bool containsNode(const TNode& node) const;

		simpleList<TEdge> getEdges () const;

		int getNodeCount() const;
		int getEdgeCount() const;

		void iterate(graphIterator<TNode, TEdge> callback) const;
		void iterateNodes(graphSimpleNodeIterator<TNode, TEdge> callback) const;
		void iterateEdges(graphSimpleEdgeIterator<TNode, TEdge> callback) const;
		void iterateAdjacentEdges (const TNode& node, graphSimpleEdgeIterator<TNode, TEdge> callback);

	private:
		simpleList<TNode> getNodes() const
		{
			return *_nodes;
		}

		simpleGraphEdgeCollection<TNode, TEdge> getEdges() const
		{
			return *_edgeCollection;
		}

	private:
		simpleList<TNode>* _nodes;

		simpleGraphEdgeCollection<TNode, TEdge>* _edgeCollection;
	};

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>::simpleGraph()
	{
		_nodes = new simpleList<TNode>();
		_edgeCollection = new simpleGraphEdgeCollection<TNode, TEdge>();
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>::simpleGraph(const simpleArray<TNode>& nodes, const simpleArray<TEdge>& edges)
	{
		_nodes = new simpleList<TNode>(nodes);
		_edgeCollection = new simpleGraphEdgeCollection<TNode, TEdge>(nodes, edges);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>::simpleGraph(const simpleArray<TNode>& nodes)
	{
		_nodes = new simpleList<TNode>(nodes);
		_edgeCollection = new simpleGraphEdgeCollection<TNode, TEdge>(nodes, simpleArray<TEdge>());
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>::simpleGraph(const simpleGraph<TNode, TEdge>& copy)
	{
		_nodes = new simpleList<TNode>(copy.getNodes());
		_edgeCollection = new simpleGraphEdgeCollection(copy.getNodes(), copy.getEdges());
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleGraph<TNode, TEdge>::~simpleGraph()
	{
		delete _nodes;
		delete _edgeCollection;
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::addEdge(const TEdge& edge)
	{
		if (!_nodes->contains(edge.node1))
			_nodes->add(edge.node1);

		if (!_nodes->contains(edge.node2))
			_nodes->add(edge.node2);

		_edgeCollection->addEdge(edge);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	int simpleGraph<TNode, TEdge>::getNodeCount() const
	{
		return _nodes->count();
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	int simpleGraph<TNode, TEdge>::getEdgeCount() const
	{
		return _edgeCollection->edgeCount();
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleList<TEdge> simpleGraph<TNode, TEdge>::getEdges() const
	{
		return _edgeCollection->getEdges();
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::modify(const TEdge& existingEdge, const TEdge& newEdge)
	{
		if (_nodes->contains(newEdge.node1))
			_nodes->remove(newEdge.node1);

		if (_nodes->contains(newEdge.node2))
			_nodes->remove(newEdge.node2);

		if (_edgeCollection->containsEdge(existingEdge))
			_edgeCollection->removeEdge(existingEdge);

		this->addEdge(newEdge);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	simpleList<TEdge> simpleGraph<TNode, TEdge>::getAdjacentEdges(const TNode& node) const
	{
		return _edgeCollection->getAdjacentEdges(node);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	TEdge simpleGraph<TNode, TEdge>::findEdge(const TNode& node1, const TNode& node2) const
	{
		return _edgeCollection->findEdge(node1, node2);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	bool simpleGraph<TNode, TEdge>::containsEdge(const TEdge& edge) const
	{
		return _edgeCollection->containsEdge(edge);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	bool simpleGraph<TNode, TEdge>::containsNode(const TNode& node) const
	{
		return _nodes->contains(node);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::iterate(graphIterator<TNode, TEdge> callback) const
	{
		bool userBreak = false;

		for (int index = 0; index < _nodes->count() && !userBreak; index++)
		{
			TNode node = _nodes->get(index);

			simpleList<TEdge> adjacentEdges = this->getAdjacentEdges(node);

			userBreak |= (callback(node, adjacentEdges) == iterationCallback::breakAndReturn);
		}
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::iterateNodes(graphSimpleNodeIterator<TNode, TEdge> callback) const
	{
		_nodes->forEach(callback);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::iterateEdges(graphSimpleEdgeIterator<TNode, TEdge> callback) const
	{
		_edgeCollection->getEdges().forEach(callback);
	}

	template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
	void simpleGraph<TNode, TEdge>::iterateAdjacentEdges(const TNode& node, graphSimpleEdgeIterator<TNode, TEdge> callback)
	{
		_edgeCollection->getAdjacentEdges (node).forEach (callback);
	}
}
