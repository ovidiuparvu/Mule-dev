#include "multiscale/verification/spatial-temporal/attribute/BinarySubsetMeasureAttribute.hpp"

using namespace multiscale::verification;


BinarySubsetMeasureType BinarySubsetMeasureAttribute::evaluate() const {
    return binarySubsetMeasure;
}

//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const BinarySubsetMeasureType &binarySubsetMeasureType) {
    switch (binarySubsetMeasureType) {
        case BinarySubsetMeasureType::Avg:
            out << "avg";
            break;

        case BinarySubsetMeasureType::Geomean:
            out << "geomean";
            break;

        case BinarySubsetMeasureType::Harmean:
            out << "harmean";
            break;

        case BinarySubsetMeasureType::Kurt:
            out << "kurt";
            break;

        case BinarySubsetMeasureType::Max:
            out << "max";
            break;

        case BinarySubsetMeasureType::Median:
            out << "median";
            break;

        case BinarySubsetMeasureType::Min:
            out << "min";
            break;

        case BinarySubsetMeasureType::Mode:
            out << "mode";
            break;

        case BinarySubsetMeasureType::Product:
            out << "product";
            break;

        case BinarySubsetMeasureType::Skew:
            out << "skew";
            break;

        case BinarySubsetMeasureType::Stdev:
            out << "stdev";
            break;

        case BinarySubsetMeasureType::Sum:
            out << "sum";
            break;

        case BinarySubsetMeasureType::Var:
            out << "var";
            break;

        default:
            out << "undefined";
    }

    return out;
}
