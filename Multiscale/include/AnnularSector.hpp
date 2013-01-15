#ifndef ANNULARSECTOR_HPP_
#define ANNULARSECTOR_HPP_

#include <string>

using namespace std;

// Class for defining an annular sector

namespace multiscale {

    class AnnularSector {

	private:

		double startingRadius;
		double endingRadius;
		double startingAngle;
		double endingAngle;
		double concentration;

	public:

		AnnularSector ();
		~AnnularSector();

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
