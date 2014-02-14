#include "multiscale/verification/spatial-temporal/attribute/UnarySubsetMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const UnarySubsetMeasureType &unarySubsetMeasureType) {
	switch (unarySubsetMeasureType) {
		case UnarySubsetMeasureType::Count:
			out << "count";
			break;

		case UnarySubsetMeasureType::Clusteredness:
			out << "clusteredness";
			break;

		case UnarySubsetMeasureType::Density:
			out << "density";
			break;

		default:
			out << "undefined";
	}

	return out;
}
