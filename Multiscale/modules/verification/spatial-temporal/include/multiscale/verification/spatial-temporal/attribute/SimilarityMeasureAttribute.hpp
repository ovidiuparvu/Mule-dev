#ifndef SIMILARITYMEASUREATTRIBUTE_HPP
#define SIMILARITYMEASUREATTRIBUTE_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <fstream>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing a similarity measure type
        enum class SimilarityMeasureType : unsigned int {
            Opposite = 0,   /*!< The opposite type */
            Similar         /*!< The similar type */
        };

        //! Overload the output stream operator for the enumeration
        /*!
         * \param out                   Output stream
         * \param similarityMeasureType The similarity measure type to be printed out
         */
        std::ostream& operator<<(std::ostream& out,
                                 const SimilarityMeasureType &similarityMeasureType);


        //! Class for representing a similarity measure attribute
        class SimilarityMeasureAttribute {

            public:

                SimilarityMeasureType  similarityMeasure;   /*!< The similarity measure */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::SimilarityMeasureAttribute,
    (multiscale::verification::SimilarityMeasureType, similarityMeasure)
)


#endif
