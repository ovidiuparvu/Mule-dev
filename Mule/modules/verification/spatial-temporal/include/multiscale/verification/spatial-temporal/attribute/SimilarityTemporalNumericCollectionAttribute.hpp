#ifndef SIMILARITYTEMPORALNUMERICCOLLETIONATTRIBUTE_HPP
#define SIMILARITYTEMPORALNUMERICCOLLETIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/SimilarityMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a similarity temporal numeric collection attribute
        class SimilarityTemporalNumericCollectionAttribute {

            public:

                SimilarityMeasureAttribute
                    similarityMeasure;              /*!< The similarity measure*/
                TemporalNumericCollectionAttribute
                    lhsTemporalNumericCollection;   /*!< The left hand side temporal numeric collection */
                TemporalNumericCollectionAttribute
                    rhsTemporalNumericCollection;   /*!< The right hand side temporal numeric collection */
                double
                    toleratedSimilarityDifference;  /*!< The tolerated similarity difference */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SimilarityTemporalNumericCollectionAttribute,
    (multiscale::verification::SimilarityMeasureAttribute, similarityMeasure)
    (multiscale::verification::TemporalNumericCollectionAttribute, lhsTemporalNumericCollection)
    (multiscale::verification::TemporalNumericCollectionAttribute, rhsTemporalNumericCollection)
    (double, toleratedSimilarityDifference)
)


#endif
