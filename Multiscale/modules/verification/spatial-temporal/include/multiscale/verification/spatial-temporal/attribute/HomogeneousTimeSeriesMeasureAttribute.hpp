#ifndef HOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP
#define HOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a homogeneous time series measure type
        enum class HomogeneousTimeSeriesMeasureType : unsigned int {
            TimeSpan    = 0,    /*!< The time span covered by the homogeneous time series */
            Values              /*!< The values defining the homogeneous time series */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                               Output stream
         * \param homogeneousTimeSeriesMeasureType  The homogeneous time series measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HomogeneousTimeSeriesMeasureType &homogeneousTimeSeriesMeasureType);


        //! Class for representing a homogeneous time series measure attribute
        class HomogeneousTimeSeriesMeasureAttribute {

            public:

                HomogeneousTimeSeriesMeasureType    homogeneousTimeSeriesMeasure;   /*!< The homogeneous time series
                                                                                         measure */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousTimeSeriesMeasureAttribute,
    (multiscale::verification::HomogeneousTimeSeriesMeasureType, homogeneousTimeSeriesMeasure)
)


#endif
