#ifndef UNARYNUMERICMEASURE_HPP
#define UNARYNUMERICMEASURE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a unary numeric measure type
        enum class UnaryNumericMeasureType : int {
            Abs     = 1,    /*!< Absolute value */
            Ceil    = 2,    /*!< Ceiling */
            Floor   = 3,    /*!< Floor */
            Round   = 4,    /*!< Round */
            Sign    = 5,    /*!< Sign: -1 (-), +1 (+) or 0 (0) */
            Sqrt    = 6,    /*!< Square root */
            Trunc   = 7     /*!< Truncation */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                        Output stream
         * \param unaryNumericMeasureType    The unary numeric measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const UnaryNumericMeasureType &unaryNumericMeasureType);


        //! Class for representing a unary numeric measure attribute
        class UnaryNumericMeasureAttribute {

            public:

                UnaryNumericMeasureType unaryNumericMeasureType;    /*!< The unary numeric measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnaryNumericMeasureAttribute,
    (multiscale::verification::UnaryNumericMeasureType, unaryNumericMeasureType)
)

#endif
