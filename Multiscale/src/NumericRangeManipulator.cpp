#include "../include/NumericRangeManipulator.hpp"

using namespace multiscale;

// Map a double from an old range to a new one
double NumericRangeManipulator::convertFromRange(double oldRangeMin, double oldRangeMax,
        										 double newRangeMin, double newRangeMax,
        										 double value) {
	double normalisedValue = (value - oldRangeMin)/(oldRangeMax - oldRangeMin);

	return (newRangeMin + normalisedValue * (newRangeMax - newRangeMin));
}

// Map an integer from an old range to a double on a new range
double NumericRangeManipulator::convertFromRange(int    oldRangeMin, int    oldRangeMax,
        										 double newRangeMin, double newRangeMax,
        										 int    value) {
	double normalisedValue = ((double)(value - oldRangeMin))/(oldRangeMax - oldRangeMin);

	return (newRangeMin + normalisedValue * (newRangeMax - newRangeMin));
}

// Map an integer from an old range to a new one
int NumericRangeManipulator::convertFromRange(int oldRangeMin, int oldRangeMax,
        									  int newRangeMin, int newRangeMax,
        									  int value) {
	double normalisedValue = (value - oldRangeMin)/(oldRangeMax - oldRangeMin);

	return (int)(newRangeMin + normalisedValue * (newRangeMax - newRangeMin));
}
