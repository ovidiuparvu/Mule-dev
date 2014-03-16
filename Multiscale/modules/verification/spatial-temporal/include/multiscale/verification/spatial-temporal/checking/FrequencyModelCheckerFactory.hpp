#ifndef FREQUENCYMODELCHECKERFACTORY_HPP
#define FREQUENCYMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating FrequencyModelChecker instances
        class FrequencyModelCheckerFactory : public ModelCheckerFactory {

            public:

                FrequencyModelCheckerFactory();
                ~FrequencyModelCheckerFactory();

                //! Create an instance of FrequencyModelChecker
                /*!
                 * \param abstractSyntaxTree The abstract syntax tree representing the logic property to be checked
                 */
                std::shared_ptr<ModelChecker> createInstance(const AbstractSyntaxTree &abstractSyntaxTree) override;

        };

    };

};

#endif
