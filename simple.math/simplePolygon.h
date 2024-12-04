#pragma once

#include <simple.h>
#include <simpleList.h>
#include <simpleException.h>
#include "simpleLine.h"

namespace simple::math
{
    using namespace simple;

    template<isHashable T>
	class simplePolygon : public simpleObject
	{
	public:
        simplePolygon (const simpleList<simpleLine<T>>& orderedSegments, bool isClosed);
        ~simplePolygon ();

        bool isClosed () const;
        int segmentCount () const;

        simpleLine<T> getSegment (int index) const;
        simpleLine<T> getNextSegment (int index) const;
        simpleLine<T> getPreviousSegment (int index) const;

	private:

        simpleList<simpleLine<T>*>* _segments;

        bool _isClosed;
	};

    template<isHashable T>
    simplePolygon<T>::simplePolygon(const simpleList<simpleLine<T>>& orderedSegments, bool isClosed)
    {
        _segments = nullptr;
        _isClosed = false;

        initialize (orderedSegments, isClosed);
    }

    template<isHashable T>
    simplePolygon<T>::~simplePolygon ()
    {
	    for (int index = 0; index < _segments->count() ;index++)
	    {
            delete _segments->get (index);
	    }

        delete _segments;
    }


    template<isHashable T>
    void simplePolygon<T>::initialize(const simpleList<simpleLine<T>>& orderedSegments, bool isClosed)
    {
        if (orderedSegments.count() == 0)
            throw simpleException("Trying to initialize line polygon with no line segments");

        // VAILDATION
        if (isClosed)
        {
            if (orderedSegments.get(0).node1 != orderedSegments.get(orderedSegments.count()) - 1).node2)
                throw simpleException ("Invalid simplePolygon:  Must be a closed, sequential set of line segments");

            for (int index = 0; index < orderedSegments.count() - 2; index++)
            {
                if (orderedSegments.get(index).node2 != orderedSegments.get(index + 1).node1)
                    throw simpleException ("Invalid simplePolygon:  Must be a sequential, closed set of line segments");
            }
        }

        _segments = new simpleList<simpleLine<T>*>();

        for (int index = 0; index < orderedSegments.count(); index++)
        {
            _segments->add (new simpleLine<T> (orderedSegments.get (index)));
        }

        _isClosed = isClosed;
    }

    template<isHashable T>
    bool simplePolygon<T>::isClosed () const
    {
        return _isClosed;
    }

    template<isHashable T>
    int simplePolygon<T>::segmentCount () const
    {
        return _segments->count ();
    }

    template<isHashable T>
    simpleLine<T> simplePolygon<T>::getSegment (int index) const
    {
        return _segments->get (index);
    }

    template<isHashable T>
    simpleLine<T> simplePolygon<T>::getNextSegment (int index) const
    {
        return index + 1 >= _segments->count () ? _segments->get (0) : _segments->get (index + 1);
    }

    template<isHashable T>
    simpleLine<T> simplePolygon<T>::getPreviousSegment (int index) const
    {
        return index - 1 < 0 ? _segments->get(_segments->count() - 1) : _segments->get (index - 1);
    }
}