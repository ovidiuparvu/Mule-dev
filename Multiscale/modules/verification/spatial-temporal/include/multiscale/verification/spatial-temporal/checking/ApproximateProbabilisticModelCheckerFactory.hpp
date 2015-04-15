#ifndef APPROXIMATEPROBABILISTICMODELCHECKERFACTORY_HPP
#define APPROXIMATEPROBABILISTICMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating ApproximateProbabilisticModelChecker instances
        class ApproximateProbabilisticModelCheckerFactory : public ModelCheckerFactory {

            private:

                double delta;                       /*!< The upper bound on the probability for the computed probability to
                                                         deviate from the true probability */
                double epsilon;                     /*!< The considered deviation from the true probability */

            public:

                ApproximateProbabilisticModelCheckerFactory(double delta, double epsilon);
                ~ApproximateProbabilisticModelCheckerFactory();

                //! Create an instance of ApproximateProbabilisticModelChecker
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
