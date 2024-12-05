#pragma once

#include <simple.h>
#include <simpleException.h>
#include <simpleHash.h>
#include <simpleBST.h>

#include "simpleGraphDefinitions.h"
#include "simpleGraphAlgorithm.h"

namespace simple::math
{
    using namespace simple;

    template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
    class dijkstrasAlgorithm : public simpleGraphAlgorithm<TNode, TEdge>
    {
    public:

        dijkstrasAlgorithm();
        ~dijkstrasAlgorithm();

        void initialize(const TNode& source, const TNode& destination);
        simpleArray<TNode> run();

    private:

        void updateOutput(const TEdge& edge, const TNode& adjacentNode, float currentWeight);

    private:

        simpleGraph<TNode, TEdge>* _graph;

        // Hash table support for marking visited, output weights, and discovered nodes
        simpleHash<TNode, bool>* _visitedDict;
        simpleHash<TNode, float>* _outputDict;
        simpleHash<TNode, float>* _discoveredDict;

        // Frontier to maintain weight lists
        simpleBST<float, simpleHash<TNode, TNode>*>* _frontier;

        // Source / Destination
        TNode _source;
        TNode _destination;

        bool _initialized;
    };

    template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
    dijkstrasAlgorithm<TNode, TEdge>::dijkstrasAlgorithm(simpleGraph<TNode, TEdge>* graph)
    {
        _graph = graph;
        _visitedDict = new simpleHash<TNode, bool>();
        _outputDict = new simpleHash<TNode, float>();
        _discoveredDict = new simpleHash<TNode, float>();

        _frontier = new simpleBST<float, simpleHash<TNode, TNode>*>();
    }

    template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
    void dijkstrasAlgorithm<TNode, TEdge>::initialize(const TNode& source, const TNode& destination)
    {
        if (source == destination))
        throw simpleException("Trying to run dijkstrasAlgorithm with the same source and destination");

        _source = source;
        _destination = destination;

        _visitedDict->clear();
        _outputDict->clear();
        _discoveredDict->clear();
        _frontier->clear();

        _graph->iterateNodes([&_visitedDict, &_outputDict, &source] (const TNode& node)
        {
            _visitedDict->add(node, false);
            _outputDict->add(node, (node == source) ? 0 : std::numeric_limits<float>::max());

            return iterationCallback::iterate;
        });

        _initialized = true;
    }

    /// <summary>
    /// Runs Dijkstra's algorithm on an IGraph using the specified type. NOTE*** Type T must support
    /// reference lookup. (Used for list comparison)
    /// </summary>
    template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
    simpleArray<TNode> dijkstrasAlgorithm<TNode, TEdge>::run()
    {
        if (!_initialized)
            throw simpleException("Trying to run dijkstrasAlgorithm before initializing");

        const dijkstrasAlgorithm<TNode, TEdge>* that = this;
        TNode currentNode = _source;

        // Iterate while target not reached (AND) not visited
        while (!_visitedDict->get(currentNode) && !currentNode == _destination)
        {
            // Fetch the current weight for this vertex
            float currentWeight = _outputDict->get(currentNode);

            // Mark node as visited
            _visitedDict->set(currentNode, true);

            // Iterate edges connected to the current vertex
            _graph->iterateAdjacentEdges(currentNode, [&that, &currentWeight] (const TEdge& adjacentEdge)
            {
                TNode adjacentNode = (adjacentEdge.node1 == currentNode) ? adjacentEdge.node2 : adjacentEdge.node1;

                // Not yet visited - CAN MODIFY OUTPUT VALUE
                if (!_visitedDict->get(adjacentNode))
                {
                    that->updateOutput(adjacentEdge, adjacentNode, currentWeight);
                }

                return iterationCallback::iterate;
            });

            // Select next location from frontier queue - using the smallest weight
            if (_frontier->count() > 0)
            {
                // Lists in the frontier must have an entry
                simpleHash<TNode, TNode>* nextCostList = _frontier->minValue();
                float nextCost = _frontier->minKey();

                if (nextCostList->count() == 0)
                    throw simpleException("Mishandled BST in Dijkstras Algorithm:  dijkstrasAlgorithm.h");

                // Get the first from the list
                currentNode = nextCostList->firstKey();

                // Maintain frontier list
                nextCostList->remove(currentNode);

                if (nextCostList->count() == 0)
                    _frontier->remove(nextCost);
            }
        }

        // Create the final graph traversal
        if (currentNode != _destination)
            return default_value::value<simpleArray<TNode>>();

        else
        {
            // Fetch the final route from the output by tracing the vertices back to the source by lowest weight
            currentNode = _destination;

            float currentWeight = std::numeric_limits<float>::max();
            TNode nextNode = _destination;
            simpleList<TNode> finalRoute;

            do
            {
                TEdge finalEdge = default_value::value<TEdge>();

                // Add current node to the route
                finalRoute.add(currentNode);

                // Find lowest weight edge towards source
                _graph->iterateAdjacentEdges(currentNode, [] (const TEdge& edge)
                {
                    if (edge.node1 != currentNode &&
                        edge.node2 != currentNode)
                        return iterationCallback::iterate;

                    TNode otherNode = (edge.node1 == currentNode) ? edge.node2 : edge.node1;

                    if (_outputDict->get(otherNode) < currentWeight)
                    {
                        currentWeight = _outputDict->get(otherNode);
                        nextNode = otherNode;
                        finalEdge = edge;
                    }

                    return iterationCallback::iterate;
                });

                if (finalEdge != default_value::value<TEdge>())
                {
                    if (finalEdge.node1 == currentNode)
                        finalRoute.add(finalEdge.node2);
                    else
                        finalRoute.add(finalEdge.node1);
                }

                else
                    throw simpleException("Invalid route found:  dijkstrasAlgorithm::run");

                // Update the follower
                currentNode = nextNode;

            } while (currentNode != _source);

            // Must reverse the final traversal
            simpleList<TNode> reverseList;

            for (int index = finalRoute.count() - 1; index >= 0; index--)
            {
                reverseList.add(finalRoute.get(index));
            }

            return reverseList.toArray();
        }
    }

    template <isGraphNode TNode, isGraphEdge<TNode> TEdge>
    void dijkstrasAlgorithm<TNode, TEdge>::updateOutput(const TEdge& edge, const TNode& adjacentNode, float currentWeight)
    {
        // Procedure
        //
        // 1) Get the existing (old) weight from the output map
        // 2) Calculate the new weight and update the output map
        // 3) Fetch the old / new weight lists from the frontier BST 
        // 4) Update the old / new weight lists and the frontier
        //
        // NOTE*** The weight lists should be very small - so running the update should
        //         not depend heavily on the List<>.Contains(...) performance.
        //
        //         Also, the AVL binary search tree has O(log n) performance for inserts
        //         / removals / and searches.
        //

        // Pre-fetch the cost list for this frontier location
        float oldWeight = _outputDict->get(adjacentNode);

        // Update the output map
        _outputDict->set(adjacentNode, simpleMath::minOf(_outputDict->get(adjacentNode), currentWeight + edge.weight()));

        // Update the frontier
        float newWeight = _outputDict->get(adjacentNode);

        // CHECK FOR NEW FRONTIER NODE
        if (!_discoveredDict->contains(adjacentNode))
        {
            simpleHash<TNode, TNode>* existingDict = _frontier->containsKey(newWeight) ? _frontier->get(newWeight) : nullptr;

            if (existingDict != nullptr)
                existingDict->add(adjacentNode, adjacentNode);

            else
            {
                simpleHash<TNode, TNode>* newDict = new simpleHash<TNode, TNode>();
                newDict->add(adjacentNode, adjacentNode);

                _frontier->insert(newWeight, newDict);
            }

            _discoveredDict->add(adjacentNode, newWeight);
            return;
        }

        // UPDATE THE FRONTIER
        simpleHash<TNode, TNode>* oldWeightList = _frontier->containsKey(oldWeight) ? _frontier->get(oldWeight) : nullptr;
        simpleHash<TNode, TNode>* newWeightList = _frontier->containsKey(newWeight) ? _frontier->get(newWeight) : nullptr;

        // Both weights are absent from the frontier
        if (oldWeightList == nullptr &&
            newWeightList == nullptr)
        {
            simpleHash<TNode, TNode>* newDict = new simpleHash<TNode, TNode>();
            newDict->add(adjacentNode, adjacentNode);

            _frontier->insert(newWeight, newDict);
        }

        // Old weight list exists; New weight list is absent
        else if (oldWeightList != nullptr &&
                 newWeightList == nullptr)
        {
            // Check for existing locator
            if (oldWeightList->contains(adjacentNode))
                oldWeightList->remove(adjacentNode);

            // Remove unused node
            if (oldWeightList->count() == 0)
            {
                _frontier->remove(oldWeight);

                // (MEMORY!) Make sure to clean up these hash tables
                delete oldWeightList;
            }

            // Insert new node in the frontier
            simpleHash<TNode, TNode>* newDict = new simpleHash<TNode, TNode>();
            newDict->add(adjacentNode, adjacentNode);

            _frontier->insert(newWeight, newDict);
        }

        // Old weight is absent; New weight exists
        else if (oldWeightList == nullptr &&
                 newWeightList != nullptr)
        {
            // Locator doesn't exist in list
            if (!newWeightList->contains(adjacentNode))
                newWeightList->add(adjacentNode, adjacentNode);
        }

        // Both old and new weight lists exist
        else
        {
            // Check that they're different lists
            if (oldWeightList != newWeightList)
            {
                // Check that old weight list has element removed
                if (oldWeightList->contains(adjacentNode))
                    oldWeightList->remove(adjacentNode);

                if (oldWeightList->count() == 0)
                {
                    _frontier->remove(oldWeight);

                    // (MEMORY!) Make sure to clean up these hash tables
                    delete oldWeightList;
                }

                // Check that new weight list has element added
                if (!newWeightList->contains(adjacentNode))
                    newWeightList->add(adjacentNode, adjacentNode);
            }
        }
    }
}