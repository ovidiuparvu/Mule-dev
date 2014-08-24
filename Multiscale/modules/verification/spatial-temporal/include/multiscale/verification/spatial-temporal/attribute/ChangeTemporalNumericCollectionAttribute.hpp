#ifndef CHANGETEMPORALNUMERICCOLLETIONATTRIBUTE_HPP
#define CHANGETEMPORALNUMERICCOLLETIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ChangeMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Class for representing a change temporal numeric collection attribute
        class ChangeTemporalNumericCollectionAttribute {

            public:

                ChangeMeasureAttribute
                    changeMeasure;              /*!< The change measure*/
                TemporalNumericCollectionAttribute
                    temporalNumericCollection;  /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ChangeTemporalNumericCollectionAttribute,
    (multiscale::verification::ChangeMeasureAttribute, changeMeasure)
    (multiscale::verification::TemporalNumericCollectionAttribute, temporalNumericCollection)
)


#endif
