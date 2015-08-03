#ifndef STATEVARIABLE_HPP
#define STATEVARIABLE_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing a state variable
        class StateVariable {

            protected:

                std::string scaleAndSubsystem;  /*!< The scale and subsystem of the state variable */

            public:

                StateVariable();
                StateVariable(const std::string &scaleAndSubsystem);
                ~StateVariable();

                //! Get the scale and subsystem of the state variable
                std::string getScaleAndSubsystem() const;

                //! Set the scale and subsystem of the state variable
                /*!
                 * \param scaleAndSubsystem The scale and subsystem which will be associated with the state variable
                 */
                void setScaleAndSubsystem(const std::string &scaleAndSubsystem);

        };

    };

};


#endif
