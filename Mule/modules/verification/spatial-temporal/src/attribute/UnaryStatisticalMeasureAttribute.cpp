#include "multiscale/verification/spatial-temporal/attribute/UnaryStatisticalMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const UnaryStatisticalMeasureType &unaryStatisticalMeasureType) {
    switch (unaryStatisticalMeasureType) {
        case UnaryStatisticalMeasureType::Avg:
            out << "avg";
            break;

        case UnaryStatisticalMeasureType::Count:
            out << "count";
            break;

        case UnaryStatisticalMeasureType::Geomean:
            out << "geomean";
            break;

        case UnaryStatisticalMeasureType::Harmean:
            out << "harmean";
            break;

        case UnaryStatisticalMeasureType::Kurt:
            out << "kurt";
            break;

        case UnaryStatisticalMeasureType::Max:
            out << "max";
            break;

        case UnaryStatisticalMeasureType::Median:
            out << "median";
            break;

        case UnaryStatisticalMeasureType::Min:
            out << "min";
            break;

        case UnaryStatisticalMeasureType::Mode:
            out << "mode";
            break;

        case UnaryStatisticalMeasureType::Product:
            out << "product";
            break;

        case UnaryStatisticalMeasureType::Skew:
            out << "skew";
            break;

        case UnaryStatisticalMeasureType::Stdev:
            out << "stdev";
            break;

        case UnaryStatisticalMeasureType::Sum:
            out << "sum";
            break;

        case UnaryStatisticalMeasureType::Var:
            out << "var";
            break;

        default:
            out << "undefined";
    }

    return out;
}
