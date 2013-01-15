#include "../include/AnnularSector.hpp"
#include "../include/StringManipulator.hpp"

#include <sstream>

#define SEPARATOR " "

using namespace multiscale;


AnnularSector::AnnularSector() {
    this->startingRadius = 0;
    this->endingRadius   = 0;
    this->startingAngle  = 0;
    this->endingAngle    = 0;
    this->concentration  = 0;    
}

AnnularSector::~AnnularSector() {
    // Do nothing
}


void AnnularSector::initialise(double startingRadius, double endingRadius, double startingAngle,
                                 double endingAngle, double concentration) {
    this->startingRadius = startingRadius;
    this->endingRadius   = endingRadius;
    this->startingAngle  = startingAngle;
    this->endingAngle    = endingAngle;
    this->concentration  = concentration;    
}

double AnnularSector::getConcentration() const {
	return concentration;
}

double AnnularSector::getEndingAngle() const {
	return endingAngle;
}

double AnnularSector::getEndingRadius() const {
	return endingRadius;
}

double AnnularSector::getStartingAngle() const {
	return startingAngle;
}

double AnnularSector::getStartingRadius() const {
	return startingRadius;
}

string AnnularSector::toString() {
    string annularSectorDescription = "";

    annularSectorDescription += StringManipulator::toString(startingRadius);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString(endingRadius);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString(startingAngle);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString(endingAngle);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString(concentration);

    return annularSectorDescription;
}
