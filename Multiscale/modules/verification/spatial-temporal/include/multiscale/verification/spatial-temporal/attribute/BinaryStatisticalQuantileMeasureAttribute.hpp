#ifndef BINARYSTATISTICALQUANTILEMEASUREATTRIBUTE_HPP
#define BINARYSTATISTICALQUANTILEMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a binary statistical quantile measure type
        enum class BinaryStatisticalQuantileMeasureType : unsigned int {
            Percentile  = 0,    /*!< The percentile */
            Quartile            /*!< The quartile */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                                   Output stream
         * \param binaryStatisticalQuantileMeasureType  The binary statistial quantile measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const BinaryStatisticalQuantileMeasureType &binaryStatisticalQuantileMeasureType);


        //! Class for representing a binary statistical quantile measure attribute
        class BinaryStatisticalQuantileMeasureAttribute {

            public:

                BinaryStatisticalQuantileMeasureType
                    binaryStatisticalQuantileMeasureType;    /*!< The binary statistical quantile measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::BinaryStatisticalQuantileMeasureAttribute,
    (multiscale::verification::BinaryStatisticalQuantileMeasureType, binaryStatisticalQuantileMeasureType)
)


#endif
