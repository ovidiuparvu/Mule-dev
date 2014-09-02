#ifndef USERDEFINEDTYPENAME_HPP
#define USERDEFINEDTYPENAME_HPP

#include <string>
#include <typeinfo>


namespace multiscale {

    //! Class for representing a user defined type name
    template <typename T>
    class UserDefinedTypeName {

        public:

            //! Retrieve the name of the given type
            static std::string name() {
                return typeid(T).name();
            }

    };


    // Macro for defining new type names
    #define DEFINE_TYPE_NAME(Type, Name)                                          \
        template <>                                                               \
        class UserDefinedTypeName<Type> {                                         \
                                                                                  \
            public:                                                               \
                                                                                  \
                static std::string name() {                                       \
                    return Name;                                                  \
                }                                                                 \
                                                                                  \
        };                                                                        \


    // Define type names for most employed types
    DEFINE_TYPE_NAME(bool, "bool")
    DEFINE_TYPE_NAME(char, "char")
    DEFINE_TYPE_NAME(char16_t, "char16_t")
    DEFINE_TYPE_NAME(char32_t, "char32_t")
    DEFINE_TYPE_NAME(double, "double")
    DEFINE_TYPE_NAME(float, "float")
    DEFINE_TYPE_NAME(int, "int")
    DEFINE_TYPE_NAME(long, "long")
    DEFINE_TYPE_NAME(long double, "long double")
    DEFINE_TYPE_NAME(long long int, "long long int")
    DEFINE_TYPE_NAME(short, "short")
    DEFINE_TYPE_NAME(signed char, "signed char")
    DEFINE_TYPE_NAME(std::string, "string")
    DEFINE_TYPE_NAME(unsigned char, "unsigned char")
    DEFINE_TYPE_NAME(unsigned short int, "unsigned short int")
    DEFINE_TYPE_NAME(unsigned long int, "unsigned long int")
    DEFINE_TYPE_NAME(unsigned long long int, "unsigned long long int")
    DEFINE_TYPE_NAME(void, "void")
    DEFINE_TYPE_NAME(wchar_t, "wchar_t")

};





#endif
