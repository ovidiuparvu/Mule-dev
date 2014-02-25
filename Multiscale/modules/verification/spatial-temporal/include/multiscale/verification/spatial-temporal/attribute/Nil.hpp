#ifndef NIL_HPP
#define NIL_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! A class used to avoid run-time errors when defining a variant type.
        /*!
         * When defining a variable of variant type "V" the default constructor of the
         * first type within "V" is called. In order to avoid run-time errors this type
         * needs to be different from the boost::recursive_wrapper<T> type. In variants
         * where all types are boost::recursive_wrapper<T_i> the Nil type can be added
         * before them in order to avoid the potential run-time errors.
         */
        class Nil {

            public:

                //! Evaluate the truth value of a logic property considering the spatial temporal trace
                /*!
                 * This method will always return true because the Nil class is used only to avoid run-time errors.
                 *
                 * \param trace The spatial temporal trace
                 */
                bool evaluate(const SpatialTemporalTrace &trace) const {
                    return true;
                }

                //! Evaluate the truth value of a logic property considering the spatial temporal trace and logic property
                /*!
                 * This method will always return true because the Nil class is used only to avoid run-time errors.
                 *
                 * \param trace             The spatial temporal trace
                 * \param lhsLogicProperty  The left hand side logic property
                 */
                bool evaluate(const SpatialTemporalTrace &trace,
                              const LogicPropertyAttributeType &lhsLogicProperty) const {
                    return true;
                }

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT (
    multiscale::verification::Nil,
    /**/
);

#endif
