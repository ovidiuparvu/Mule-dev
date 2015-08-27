#ifndef TIMESERIESMEASUREATTRIBUTE_HPP
#define TIMESERIESMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a time series measure type
        enum class TimeSeriesMeasureType : unsigned int {
            EnteringTime    = 0,    /*!< The entering time */
            EnteringValue           /*!< The entering value */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param timeSeriesMeasureType The time series measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const TimeSeriesMeasureType &timeSeriesMeasureType);


        //! Class for representing a time series measure attribute
        class TimeSeriesMeasureAttribute {

            public:

                TimeSeriesMeasureType  timeSeriesMeasure;   /*!< The time series measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TimeSeriesMeasureAttribute,
    (multiscale::verification::TimeSeriesMeasureType, timeSeriesMeasure)
)


#endif
