#ifndef INDEXOUTOFBOUNDSEXCEPTION_HPP
#define INDEXOUTOFBOUNDSEXCEPTION_HPP

#include "multiscale/exception/RuntimeException.hpp"

#include <string>


namespace multiscale {

    //! Class for representing an index out of bounds exception
    class IndexOutOfBoundsException : public RuntimeException {

        public:

            IndexOutOfBoundsException() {}

            /*
             * \param file  The name of the file
             * \param line  The line number from which the exception was thrown
             * \param msg   The index value
             */
            explicit IndexOutOfBoundsException(const std::string &file, int line, const std::string &msg) {
                constructExplanatoryString<const std::string &>(file, line,
                    ERR_INDEX_OUT_OF_BOUNDS_BEGIN + msg + ERR_INDEX_OUT_OF_BOUNDS_END
                );
            }

            /*
             * \param file  The name of the file
             * \param line  The line number from which the exception was thrown
             * \param msg   The index value
             */
            explicit IndexOutOfBoundsException(const std::string &file, int line, const char *msg) {
                constructExplanatoryString<const std::string &>(file, line,
                    (ERR_INDEX_OUT_OF_BOUNDS_BEGIN + std::string(msg) + ERR_INDEX_OUT_OF_BOUNDS_END).c_str()
                );
            }

    };

};


#endif
