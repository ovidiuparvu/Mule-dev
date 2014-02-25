#ifndef LOGICPROPERTYVISITOR_HPP
#define LOGICPROPERTYVISITOR_HPP

#include "multiscale/verification/spatial-temporal/attribute/LogicPropertyEvaluator.hpp"
#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to evaluate logic properties
        class LogicPropertyVisitor : public boost::static_visitor<bool> {

            private:

                SpatialTemporalTrace trace; /*!< The spatial temporal trace */

            public:

                LogicPropertyVisitor(const SpatialTemporalTrace &trace) {
                    this->trace = trace;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const T &logicProperty) const {
                    return logicProperty.evaluate(trace);
                }

                //! Overloading the operator ()
                template <typename T, typename U>
                bool operator() (const T &logicProperty, const U &lhsLogicProperty) const {
                    return logicProperty.evaluate(trace, lhsLogicProperty);
                }

        };

    };

};

#endif
