#ifndef SHAPE_HPP
#define SHAPE_HPP


namespace multiscale {

    namespace analysis {

        //! Enumeration for determining the type of a 2D shape
        enum class Shape2D : unsigned int {
            Triangle    = 0,    /*!< Triangular 2D shape */
            Rectangle      ,    /*!< Rectangular 2D shape */
            Circle         ,    /*!< Circular 2D shape */
            Undefined           /*!< Undefined 2D shape */
        };

    };

};


#endif
