#ifndef PROBABILISTICLOGICPROPERTYATTRIBUTE_HPP
#define PROBABILISTICLOGICPROPERTYATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/ComparatorAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/visitor/LogicPropertyVisitor.hpp"

#include "boost/fusion/include/adapt_struct.hpp"
#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class for representing a probabilistic logic property attribute
        class ProbabilisticLogicPropertyAttribute {

            public:

                ComparatorAttribute         comparator;                 /*!< The comparator */
                double                      probability;                /*!< The probability */
                LogicPropertyAttributeType  logicProperty;              /*!< The logic property */

                LogicPropertyAttributeType  evaluationLogicProperty;    /*!< The logic property used only for
                                                                             evaluation purposes */

            public:

                //! Get the type of the comparator
                ComparatorType getComparator();

                //! Get the probability
                double getProbability();

                //! Evaluate the truth value of the logic property considering the given spatial temporal trace
                /*!
                 * \param trace The spatial temporal trace
                 */
                bool evaluate(const SpatialTemporalTrace &trace);

            private:

                // Constants
                static const std::string ERR_TRACE_LENGTH_ZERO;

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
