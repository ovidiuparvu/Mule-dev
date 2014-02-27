#ifndef NUMERICVISITOR_HPP
#define NUMERICVISITOR_HPP

#include <boost/variant.hpp>


namespace multiscale {

    namespace verification {

        //! Class for evaluating numeric measures
        class NumericVisitor : public boost::static_visitor<double> {

            private:

                TimePoint timePoint;  /*!< The considered timepoint */

            public:

                NumericVisitor(const TimePoint &timePoint) {
                    this->timePoint = timePoint;
                }

                //! Evaluate the truth value of a numeric measure considering the given time point
                /*!
                 * \param timePoint  The given timepoint
                 */
//                double evaluate(const TimePoint &timePoint) const {
//                    std::string name = stateVariable.evaluate();
//
//                    return timePoint.getNumericStateVariable(name);
//                }

        }

    };

};

#endif
