#ifndef SCALEANDSUBSYSTEM_HPP
#define SCALEANDSUBSYSTEM_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a scale and subsystem
        class ScaleAndSubsystem {

            public:

                // Constants
                static const std::string DEFAULT_VALUE; /*!< The default scale and subsystem value used when no
                                                             explicit scale and subsystem is associated to a spatial
                                                             entity and/or numeric state variable */

        };

    };

};


#endif
