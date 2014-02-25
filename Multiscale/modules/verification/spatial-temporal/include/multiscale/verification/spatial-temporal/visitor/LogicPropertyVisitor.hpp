#ifndef LOGICPROPERTYVISITOR_HPP
#define LOGICPROPERTYVISITOR_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class used to evaluate logic properties
        class LogicPropertyVisitor : public boost::static_visitor<bool> {

            private:

                SpatialTemporalTrace trace;                             /*!< The spatial temporal trace */
                bool                 previousLogicPropertyTruthValue;   /*!< The truth value of the previous
                                                                             logic property */

            public:

                LogicPropertyVisitor(const SpatialTemporalTrace &trace, bool previousLogicPropertyTruthValue = true) {
                    this->trace = trace;
                    this->previousLogicPropertyTruthValue = previousLogicPropertyTruthValue;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const Nil &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const LogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return logicProperty.evaluate(trace);
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const OrLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const AndLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const ImplicationLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const EquivalenceLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const UntilLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

                //! Overloading the operator ()
                template <typename T>
                bool operator() (const PrimaryLogicPropertyAttribute &logicProperty, const T &lhsLogicProperty) const {
                    return true;
                }

        };

    };

};

#endif
