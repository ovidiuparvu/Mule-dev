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
                 * \param abstractSyntaxTree            The abstract syntax tree representing the logic property to be
                 *                                      checked
                 * \param multiscaleArchitectureGraph   The multiscale architecture graph encoding the hierarchical
                 *                                      organization of scales and subsystems
                 */
                std::shared_ptr<ModelChecker>
                createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                               const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) override;

        };

    };

};


#endif
