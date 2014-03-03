#ifndef UNARYSUBSETMEASUREATTRIBUTE_HPP
#define UNARYSUBSETMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a unary subset measure type
        enum class UnarySubsetMeasureType : int {
            Count           = 1,    /*!< Number of spatial entities */
            Clusteredness   = 2,    /*!< The overall clusteredness of the entities */
            Density         = 3     /*!< The overall density of the entities */
        };


        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                        Output stream
         * \param unarySubsetMeasureType     The unary subset measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out, const UnarySubsetMeasureType &unarySubsetMeasureType);


        //! Class for representing a unary subset measure attribute
        class UnarySubsetMeasureAttribute {

            public:

                UnarySubsetMeasureType unarySubsetMeasureType;    /*!< The unary subset measure type */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::UnarySubsetMeasureAttribute,
    (multiscale::verification::UnarySubsetMeasureType, unarySubsetMeasureType)
)

#endif
