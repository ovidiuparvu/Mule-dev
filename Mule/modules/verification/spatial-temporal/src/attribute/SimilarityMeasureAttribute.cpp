#include "multiscale/verification/spatial-temporal/attribute/SimilarityMeasureAttribute.hpp"

using namespace multiscale::verification;


//! Overload the output stream operator for the enumeration
std::ostream&
multiscale::verification::operator<<(std::ostream& out,
                                     const SimilarityMeasureType &similarityMeasureType) {
    switch (similarityMeasureType) {
        case SimilarityMeasureType::Opposite:
            out << "opposite";
            break;

        case SimilarityMeasureType::Similar:
            out << "similar";
            break;

        default:
            out << "undefined";
    }

    return out;
}
