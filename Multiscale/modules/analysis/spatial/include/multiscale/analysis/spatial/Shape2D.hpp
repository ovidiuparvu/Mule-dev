#ifndef SHAPE_HPP
#define SHAPE_HPP


namespace multiscale {

    namespace analysis {

        //! Enumeration for determining the type of a 2D shape
        enum Shape2D {
            Triangle = 1,   /*!< Triangular 2D shape */
            Rectangle = 2,  /*!< Rectangular 2D shape */
            Circle = 3,     /*!< Circular 2D shape */
            Undefined = 4   /*!< Undefined 2D shape */
        };

    };

};

#endif
