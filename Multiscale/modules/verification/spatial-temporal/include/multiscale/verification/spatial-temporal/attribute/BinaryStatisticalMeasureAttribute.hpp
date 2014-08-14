#ifndef BINARYSTATISTICALMEASUREATTRIBUTE_HPP
#define BINARYSTATISTICALMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a binary statistical measure type
        enum class BinaryStatisticalMeasureType : unsigned int {
            Covar = 0   /*!< Covariance */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                           Output stream
         * \param binaryStatisticalMeasureType  The binary statistical measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const BinaryStatisticalMeasureType &binaryStatisticalMeasureType);


        //! Class for representing a binary statistical measure attribute
        class BinaryStatisticalMeasureAttribute {

            public:

                BinaryStatisticalMeasureType binaryStatisticalMeasureType;    /*!< The binary statistical measure
                                                                                   type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalMeasureAttribute,
    (multiscale::verification::BinaryStatisticalMeasureType, binaryStatisticalMeasureType)
)


#endif
