#ifndef TIMESERIESMEASUREATTRIBUTE_HPP
#define TIMESERIESMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a timeseries measure type
        enum class TimeseriesMeasureType : unsigned int {
            EnteringTime    = 0,    /*!< The entering time */
            EnteringValue           /*!< The entering value */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param timeseriesMeasureType The timeseries measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const TimeseriesMeasureType &timeseriesMeasureType);


        //! Class for representing a timeseries measure attribute
        class TimeseriesMeasureAttribute {

            public:

                TimeseriesMeasureType  timeseriesMeasure;   /*!< The timeseries measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeseriesMeasureAttribute,
    (multiscale::verification::TimeseriesMeasureType, timeseriesMeasure)
)


#endif
