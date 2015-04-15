#ifndef PROBABILISTICBLACKBOXMODELCHECKERFACTORY_HPP
#define PROBABILISTICBLACKBOXMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating ProbabilisticBlackBoxModelChecker instances
        class ProbabilisticBlackBoxModelCheckerFactory : public ModelCheckerFactory {

            public:

                ProbabilisticBlackBoxModelCheckerFactory();
                ~ProbabilisticBlackBoxModelCheckerFactory();

                //! Create an instance of ProbabilisticBlackBoxModelChecker
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
