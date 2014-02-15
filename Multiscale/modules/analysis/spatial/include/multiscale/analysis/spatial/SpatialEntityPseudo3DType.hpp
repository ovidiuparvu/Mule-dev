#ifndef SPATIALENTITYPSEUDO3DTYPE_HPP
#define SPATIALENTITYPSEUDO3DTYPE_HPP


namespace multiscale {

    namespace analysis {

        //! Enumeration for determining the type of a pseudo 3D entity
        enum class SpatialEntityPseudo3DType : int {
            Cluster = 1,    /*!< Cluster */
            Region  = 2     /*!< Region */
        };

    };

};

#endif
