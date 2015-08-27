#ifndef HETEROGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP
#define HETEROGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a heterogeneous time series component type
        enum class HeterogeneousTimeSeriesComponentType : unsigned int {
            Peak    = 0,    /*!< The peak of the time series */
            Valley          /*!< The value of the time series */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                                   Output stream
         * \param heterogeneousTimeSeriesComponentType  The heterogeneous time series component type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HeterogeneousTimeSeriesComponentType &heterogeneousTimeSeriesComponentType);


        //! Class for representing a heterogeneous time series component attribute
        class HeterogeneousTimeSeriesComponentAttribute {

            public:

                HeterogeneousTimeSeriesComponentType  heterogeneousTimeSeriesComponent;   /*!< The heterogeneous
                                                                                               time series component */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HeterogeneousTimeSeriesComponentAttribute,
    (multiscale::verification::HeterogeneousTimeSeriesComponentType, heterogeneousTimeSeriesComponent)
)


#endif
