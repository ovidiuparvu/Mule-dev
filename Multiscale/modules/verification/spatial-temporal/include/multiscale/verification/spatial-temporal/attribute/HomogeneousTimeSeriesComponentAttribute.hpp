#ifndef HOMOGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP
#define HOMOGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a homogeneous time series component type
        enum class HomogeneousTimeSeriesComponentType : unsigned int {
            Ascent          = 0,    /*!< The ascending time series type */
            Descent            ,    /*!< The descending time series type */
            Plateau            ,    /*!< The plateau time series type */
            UniformAscent      ,    /*!< The uniformly (constantly) ascending time series type */
            UniformDescent          /*!< The uniformly (constantly) descending time series type */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                                   Output stream
         * \param homogeneousTimeSeriesComponentType    The homogeneous time series component type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HomogeneousTimeSeriesComponentType &homogeneousTimeSeriesComponentType);


        //! Class for representing a homogeneous time series component attribute
        class HomogeneousTimeSeriesComponentAttribute {

            public:

                HomogeneousTimeSeriesComponentType  homogeneousTimeSeriesComponent;   /*!< The homogeneous time series
                                                                                           component */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousTimeSeriesComponentAttribute,
    (multiscale::verification::HomogeneousTimeSeriesComponentType, homogeneousTimeSeriesComponent)
)


#endif
