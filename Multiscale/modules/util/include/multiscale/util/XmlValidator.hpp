#ifndef XMLVALIDATOR_HPP
#define XMLVALIDATOR_HPP

#include <string>


namespace multiscale {

    //! Class used to validate xml files
    class XmlValidator {

        public:

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * \param xmlFilepath   The path to the xml file
             * \param xmlSchemaPath The path to the xml schema file
             */
            static bool isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath);

        private:

            // Constants
            static const std::string ERR_OPEN_SCHEMA_FILE;

    };

};

#endif
