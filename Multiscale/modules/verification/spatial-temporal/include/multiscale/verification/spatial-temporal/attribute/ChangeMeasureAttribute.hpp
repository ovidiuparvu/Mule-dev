#ifndef CHANGEMEASUREATTRIBUTE_HPP
#define CHANGEMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a change measure type
        enum class ChangeMeasureType : unsigned int {
            Derivative = 0,    /*!< Derivative representing rate of change */
            Ratio              /*!< Ratio of value change over difference in time change */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out               Output stream
         * \param changeMeasureType The change measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const ChangeMeasureType &changeMeasureType);


        //! Class for representing a change measure attribute
        class ChangeMeasureAttribute {

            public:

                ChangeMeasureType changeMeasureType;    /*!< The change measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::ChangeMeasureAttribute,
    (multiscale::verification::ChangeMeasureType, changeMeasureType)
)


#endif
