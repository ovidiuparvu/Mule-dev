#ifndef LOGICPROPERTYEVALUATOR_HPP
#define LOGICPROPERTYEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/Nil.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class LogicPropertyAttribute;
        class OrLogicPropertyAttribute;
        class AndLogicPropertyAttribute;
        class EquivalenceLogicPropertyAttribute;
        class ImplicationLogicPropertyAttribute;
        class PrimaryLogicPropertyAttribute;
        class UntilLogicPropertyAttribute;


        //! Variant for the logic property attribute
        typedef boost::variant<
            Nil,
            boost::recursive_wrapper<LogicPropertyAttribute>,
            boost::recursive_wrapper<OrLogicPropertyAttribute>,
            boost::recursive_wrapper<AndLogicPropertyAttribute>,
            boost::recursive_wrapper<ImplicationLogicPropertyAttribute>,
            boost::recursive_wrapper<EquivalenceLogicPropertyAttribute>,
            boost::recursive_wrapper<UntilLogicPropertyAttribute>,
            boost::recursive_wrapper<PrimaryLogicPropertyAttribute>
        > LogicPropertyAttributeType;


        //! Abstract class used for evaluating logic properties
        class LogicPropertyEvaluator {

            public:

                virtual ~LogicPropertyEvaluator() {};

                //! Evaluate the truth value of a logic property considering the given spatial temporal trace
                /*!
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                virtual bool evaluate(const SpatialTemporalTrace &trace,
                                      const LogicPropertyAttributeType &lhsLogicProperty) const = 0;

        };

    };

};

#endif
