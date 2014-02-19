#ifndef PROBABILISTICLOGICPROPERTYATTRIBUTE_HPP_
#define PROBABILISTICLOGICPROPERTYATTRIBUTE_HPP_

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"

#include "boost/fusion/include/adapt_struct.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing a probabilistic logic property attribute
        class ProbabilisticLogicPropertyAttribute {

            public:

                ComparatorAttribute         comparator;     /*!< The comparator */
                double                      probability;    /*!< The probability */
                LogicPropertyAttributeType  logicProperty;  /*!< The logic property */


                //! Get the type of the comparator
                ComparatorType getComparator();

                //! Get the probability
                double getProbability();

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT (
    multiscale::verification::ProbabilisticLogicPropertyAttribute,
    (multiscale::verification::ComparatorAttribute, comparator)
    (double, probability)
    (multiscale::verification::LogicPropertyAttributeType, logicProperty)
);

#endif
