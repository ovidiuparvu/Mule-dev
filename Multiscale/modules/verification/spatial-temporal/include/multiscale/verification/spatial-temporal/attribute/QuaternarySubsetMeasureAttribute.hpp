#ifndef QUATERNARYSUBSETMEASUREATTRIBUTE_HPP
#define QUATERNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a quaternary subset measure type
        enum class QuaternarySubsetMeasureType : int {
            Covar = 1    /*!< Covariance */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                            Output stream
         * \param quaternarySubsetMeasureType    The quaternary subset measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const QuaternarySubsetMeasureType &quaternarySubsetMeasureType);


        //! Class for representing a quaternary subset measure attribute
        class QuaternarySubsetMeasureAttribute {

            public:

                QuaternarySubsetMeasureType quaternarySubsetMeasure;    /*!< The quaternary subset measure */

            public:

                //! Return the quaternary subset measure type
                QuaternarySubsetMeasureType evaluate() const;

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::QuaternarySubsetMeasureAttribute,
    (multiscale::verification::QuaternarySubsetMeasureType, quaternarySubsetMeasure)
)

#endif
