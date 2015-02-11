#ifndef HOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP
#define HOMOGENEOUSTIMESERIESMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a homogeneous timeseries measure type
        enum class HomogeneousTimeseriesMeasureType : unsigned int {
            TimeSpan    = 0,    /*!< The time span covered by the homogeneous timeseries */
            Values              /*!< The values defining the homogeneous timeseries */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                               Output stream
         * \param homogeneousTimeseriesMeasureType  The homogeneous timeseries measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HomogeneousTimeseriesMeasureType &homogeneousTimeseriesMeasureType);


        //! Class for representing a homogeneous timeseries measure attribute
        class HomogeneousTimeseriesMeasureAttribute {

            public:

                HomogeneousTimeseriesMeasureType    homogeneousTimeseriesMeasure;   /*!< The homogeneous timeseries
                                                                                         measure */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousTimeseriesMeasureAttribute,
    (multiscale::verification::HomogeneousTimeseriesMeasureType, homogeneousTimeseriesMeasure)
)


#endif
