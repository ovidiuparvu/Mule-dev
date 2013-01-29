#include "multiscale/video/circular/AnnularSector.hpp"
#include "multiscale/util/StringManipulator.hpp"

#include <sstream>

#define SEPARATOR " "

using namespace multiscale::video;


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

    annularSectorDescription += StringManipulator::toString<double>(startingRadius);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString<double>(endingRadius);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString<double>(startingAngle);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString<double>(endingAngle);
	annularSectorDescription += SEPARATOR;
    annularSectorDescription += StringManipulator::toString<double>(concentration);

    return annularSectorDescription;
}
