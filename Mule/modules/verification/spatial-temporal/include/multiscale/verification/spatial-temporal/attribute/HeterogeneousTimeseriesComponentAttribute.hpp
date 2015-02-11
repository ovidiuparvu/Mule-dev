#ifndef HETEROGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP
#define HETEROGENEOUSTIMESERIESCOMPONENTATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a heterogeneous timeseries component type
        enum class HeterogeneousTimeseriesComponentType : unsigned int {
            Peak    = 0,    /*!< The peak of the timeseries */
            Valley          /*!< The value of the timeseries */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                                   Output stream
         * \param heterogeneousTimeseriesComponentType  The heterogeneous timeseries component type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const HeterogeneousTimeseriesComponentType &heterogeneousTimeseriesComponentType);


        //! Class for representing a heterogeneous timeseries component attribute
        class HeterogeneousTimeseriesComponentAttribute {

            public:

                HeterogeneousTimeseriesComponentType  heterogeneousTimeseriesComponent;   /*!< The heterogeneous
                                                                                               timeseries component */
        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::HeterogeneousTimeseriesComponentAttribute,
    (multiscale::verification::HeterogeneousTimeseriesComponentType, heterogeneousTimeseriesComponent)
)


#endif
