#ifndef HOMOGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP
#define HOMOGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a homogeneous timeseries component type
        enum class HomogeneousTimeseriesComponentType : unsigned int {
            Ascent          = 0,    /*!< The ascending timeseries type */
            Descent            ,    /*!< The descending timeseries type */
            Plateau            ,    /*!< The plateau timeseries type */
            UniformAscent      ,    /*!< The uniformly (constantly) ascending timeseries type */
            UniformDescent          /*!< The uniformly (constantly) descending timeseries type */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                                   Output stream
         * \param homogeneousTimeseriesComponentType    The homogeneous timeseries component type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HomogeneousTimeseriesComponentType &homogeneousTimeseriesComponentType);


        //! Class for representing a homogeneous timeseries component attribute
        class HomogeneousTimeseriesComponentAttribute {

            public:

                HomogeneousTimeseriesComponentType  homogeneousTimeseriesComponent;   /*!< The homogeneous timeseries
                                                                                           component */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HomogeneousTimeseriesComponentAttribute,
    (multiscale::verification::HomogeneousTimeseriesComponentType, homogeneousTimeseriesComponent)
)


#endif
