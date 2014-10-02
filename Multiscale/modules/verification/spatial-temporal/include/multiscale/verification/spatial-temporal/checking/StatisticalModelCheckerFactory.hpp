#ifndef STATISTICALMODELCHECKERFACTORY_HPP
#define STATISTICALMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating StatisticalModelChecker instances
        class StatisticalModelCheckerFactory : public ModelCheckerFactory {

            private:

                double typeIError;      /*!< The probability of a type I error */
                double typeIIError;     /*!< The probability of a type II error */

            public:

                StatisticalModelCheckerFactory(double typeIError, double typeIIError);
                ~StatisticalModelCheckerFactory();

                //! Create an instance of StatisticalModelChecker
                /*!
                 * \param abstractSyntaxTree The abstract syntax tree representing the logic property to be checked
                 * \param typeSemanticsTable The type semantics table mapping semantic criteria values to
                 *                           abstract natural numbers
                 */
                std::shared_ptr<ModelChecker> createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                                             const TypeSemanticsTable &typeSemanticsTable) override;

        };

    };

};


#endif
