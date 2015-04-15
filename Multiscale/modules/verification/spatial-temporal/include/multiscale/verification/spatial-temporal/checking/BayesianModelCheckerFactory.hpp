#ifndef BAYESIANMODELCHECKERFACTORY_HPP
#define BAYESIANMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating BayesianModelChecker instances
        class BayesianModelCheckerFactory : public ModelCheckerFactory {

            private:

                double alpha;                   /*!< The shape parameter \f$ \alpha \f$ for the Beta distribution prior */
                double beta;                    /*!< The shape parameter \f$ \beta \f$ for the Beta distribution prior */

                double bayesFactorThreshold;    /*!< The Bayes factor threshold */

            public:

                BayesianModelCheckerFactory(double alpha, double beta, double bayesFactorThreshold);
                ~BayesianModelCheckerFactory();

                //! Create an instance of BayesianModelChecker
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
