#ifndef NIL_HPP
#define NIL_HPP

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        //! A class used to avoid run-time errors when defining a variant type.
        /*!
         * When defining a variable of variant type "V" the default constructor of the
         * first type within "V" is called. In order to avoid run-time errors this type
         * needs to be different from the boost::recursive_wrapper<T> type. In variants
         * where all types are boost::recursive_wrapper<T_i> the Nil type can be added
         * before them in order to avoid the potential run-time errors.
         */
        class Nil {};

    };

};


BOOST_FUSION_ADAPT_STRUCT (
    multiscale::verification::Nil,
    /**/
);


#endif
