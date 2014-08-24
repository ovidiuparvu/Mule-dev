#ifndef NUMERICSTATEVARIABLEID_HPP
#define NUMERICSTATEVARIABLEID_HPP

#include <string>


namespace multiscale {

    namespace verification {

        //! Class for representing the identity (name, type) of a numeric state variable
        class NumericStateVariableId {

            private:

                std::string     name;           /*!< The name of the numeric state variable */
                unsigned long   semanticType;   /*!< The semantic type of the numeric state variable */
                
            public:

                /*!
                 * The default value for the numeric state variable type is 0.
                 */
                NumericStateVariableId(const std::string &name, unsigned long semanticType = 0)
                    : name(name), semanticType(semanticType) {}

                //! Get the name of the numeric state variable
                const std::string& getName() const;

                //! Set the name of the numeric state variable
                /*!
                 * \param name  The name of the numeric state variable
                 */
                void setName(const std::string& name);

                //! Get the semantic type of the numeric state variable
                unsigned long getSemanticType() const;

                //! Set the semantic type of the numeric state variable
                /*!
                 * \param type  The type of the numeric state variable
                 */
                void setSemanticType(unsigned long semanticType);

                //! Overload the < operator
                /*!
                 * \param rhs   The right hand side numeric state variable identity
                 *              i.e. (lhs < rhs)?
                 */
                bool operator<(const NumericStateVariableId &rhs) const;

                //! Return the string representation of the numeric state variable identity
                std::string toString() const;


                // Constants
                static const std::string OUTPUT_STRING_BEGIN;
                static const std::string OUTPUT_STRING_SEPARATOR;
                static const std::string OUTPUT_STRING_END;

        };

    };

};

#endif
