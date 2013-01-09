#ifndef CIRCULARSEGMENT_HPP_
#define CIRCULARSEGMENT_HPP_

#include <string>

using namespace std;

// Class for defining a circular segment (sector of circular disc)

namespace multiscale {

    class CircularSegment {

	private:

		double startingRadius;
		double endingRadius;
		double startingAngle;
		double endingAngle;
		double concentration;

	public:

		CircularSegment ();
		~CircularSegment();

		void   initialise(double startingRadius, double endingRadius,
				          double startingAngle,  double endingAngle, double concentration);
		double getConcentration () const;
		double getEndingAngle   () const;
		double getEndingRadius  () const;
		double getStartingAngle () const;
		double getStartingRadius() const;
		string toString();

};
};

#endif
