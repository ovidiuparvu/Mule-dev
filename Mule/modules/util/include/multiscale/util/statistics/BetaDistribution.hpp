#ifndef BETADISTRIBUTION_HPP
#define BETADISTRIBUTION_HPP

#include "multiscale/util/statistics/Distribution.hpp"


namespace multiscale {

    //! Class for analysing Beta distributed data
    class BetaDistribution : public Distribution {

        public:

            //! Compute the value of the cumulative distribution function (cdf) for a Beta distribution
            /*! The value of the cumulative distribution function (cdf) is computed
             *  considering the given probability and shape parameters.
             *
             * \param alpha         Shape parameter \f$ alpha \f$
             * \param beta          Shape parameter \f$ beta \f$
             * \param probability   The considered probability when computing the value of the cdf
             */
            static double cdf(double alpha, double beta, double probability);

        private:

            //! Validate the shape parameters \f$ \alpha \f$ and \f$ \beta \f$
            /*! \f$ \alpha \f$ and \f$ \beta \f$ should be greater than zero
             *
             * \param alpha The shape parameter \f$ \alpha \f$ for the Beta distribution
             * \param beta  The shape parameter \f$ \beta \f$ for the Beta distribution
             */
            static void validateShapeParameters(double alpha, double beta);

            //! Check if the given shape parameter value is valid
            /*! The shape parameter values should be greater than zero
             *
             * \param shapeParameter    The given shape parameter
             */
            static bool isValidShapeParameter(double shapeParameter);

            //! Compute the value of the cumulative distribution function (cdf) for a Beta distribution considering that the parameters are valid
            /*!
             * \param alpha         Shape parameter \f$ alpha \f$
             * \param beta          Shape parameter \f$ beta \f$
             * \param probability   The considered probability when computing the value of the cdf
             */
            static double computeCdf(double alpha, double beta, double probability);


            // Constants
            static const std::string ERR_SHAPE_PARAMETERS_BEGIN;
            static const std::string ERR_SHAPE_PARAMETERS_MIDDLE;
            static const std::string ERR_SHAPE_PARAMETERS_END;

    };

};


#endif
