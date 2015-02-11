#ifndef APPROXIMATEBAYESIANMODELCHECKERFACTORY_HPP
#define APPROXIMATEBAYESIANMODELCHECKERFACTORY_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelCheckerFactory.hpp"


namespace multiscale {

    namespace verification {

        //! Class for creating ApproximateBayesianModelChecker instances
        class ApproximateBayesianModelCheckerFactory : public ModelCheckerFactory {

            private:

                double alpha;                   /*!< The shape parameter \f$ \alpha \f$ for the Beta distribution prior */
                double beta;                    /*!< The shape parameter \f$ \beta \f$ for the Beta distribution prior */

                double varianceThreshold;       /*!< The variance threshold */

            public:

                ApproximateBayesianModelCheckerFactory(double alpha, double beta,
                                                       double varianceThreshold);
                ~ApproximateBayesianModelCheckerFactory();

                //! Create an instance of ApproximateBayesianModelChecker
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
