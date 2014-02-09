#ifndef NOTEVALUATOR_HPP
#define NOTEVALUATOR_HPP

#include "multiscale/verification/spatial-temporal/evaluation/UnaryEvaluator.hpp"


namespace multiscale {

    namespace verification {

        //! Class for representing the evaluation of a "not" logical expression
        class NotEvaluator : public UnaryEvaluator {

            public:

                //! Evaluate the truth value of (NOT operand)
                /*!
                 * \param operand   The operand
                 */
                bool operator()(bool operand) const override;

        };

    };

};

#endif
