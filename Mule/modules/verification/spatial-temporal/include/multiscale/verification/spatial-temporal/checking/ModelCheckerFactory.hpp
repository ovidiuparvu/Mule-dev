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
                 * \param abstractSyntaxTree The abstract syntax tree representing the logic property to be checked
                 * \param typeSemanticsTable The type semantics table mapping semantic criteria values to
                 *                           abstract natural numbers
                 */
                virtual std::shared_ptr<ModelChecker> createInstance(const AbstractSyntaxTree &abstractSyntaxTree,
                                                                     const TypeSemanticsTable &typeSemanticsTable) = 0;

        };

    };

};


#endif
