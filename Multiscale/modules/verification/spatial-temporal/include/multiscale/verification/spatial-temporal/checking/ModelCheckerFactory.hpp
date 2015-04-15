#ifndef MODELCHECKERFACTORY_HPP
#define MODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"

#include <memory>


namespace multiscale {

    namespace verification {

        //! Interface for different model checker factories
        class ModelCheckerFactory {

            public:

                ModelCheckerFactory() {};
                virtual ~ModelCheckerFactory() {};

                //! Create an instance of the model checker
                /*!
                 * \param abstractSyntaxTree            The abstract syntax tree representing the logic property to be
                 *                                      checked
                 * \param multiscaleArchitectureGraph   The multiscale architecture graph encoding the hierarchical
                 *                                      organization of scales and subsystems
                 */
                virtual std::shared_ptr<ModelChecker>
                createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                               const MultiscaleArchitectureGraph &multiscaleArchitectureGraph) = 0;

        };

    };

};


#endif
