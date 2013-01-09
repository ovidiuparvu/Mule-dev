#include "../include/CircularSegment.hpp"
#include "../include/StringManipulator.hpp"

#include <sstream>

#define SEPARATOR " "

using namespace multiscale;


CircularSegment::CircularSegment() {
    this->startingRadius = 0;
    this->endingRadius   = 0;
    this->startingAngle  = 0;
    this->endingAngle    = 0;
    this->concentration  = 0;    
}

CircularSegment::~CircularSegment() {
    // Do nothing
}


void CircularSegment::initialise(double startingRadius, double endingRadius, double startingAngle,
                                 double endingAngle, double concentration) {
    this->startingRadius = startingRadius;
    this->endingRadius   = endingRadius;
    this->startingAngle  = startingAngle;
    this->endingAngle    = endingAngle;
    this->concentration  = concentration;    
}

double CircularSegment::getConcentration() const {
	return concentration;
}

double CircularSegment::getEndingAngle() const {
	return endingAngle;
}

double CircularSegment::getEndingRadius() const {
	return endingRadius;
}

double CircularSegment::getStartingAngle() const {
	return startingAngle;
}

double CircularSegment::getStartingRadius() const {
	return startingRadius;
}

string CircularSegment::toString() {
    string circularSegmentDescription = "";

    circularSegmentDescription += StringManipulator::toString(startingRadius);
	circularSegmentDescription += SEPARATOR;
    circularSegmentDescription += StringManipulator::toString(endingRadius);
	circularSegmentDescription += SEPARATOR;
    circularSegmentDescription += StringManipulator::toString(startingAngle);
	circularSegmentDescription += SEPARATOR;
    circularSegmentDescription += StringManipulator::toString(endingAngle);
	circularSegmentDescription += SEPARATOR;
    circularSegmentDescription += StringManipulator::toString(concentration);

    return circularSegmentDescription;
}
