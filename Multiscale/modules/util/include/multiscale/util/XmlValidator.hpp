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

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * \param xmlFilepath   The path to the xml file
             * \param xmlSchemaPath The path to the xml schema file
             */
            static bool verifyIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath);

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * \param xmlFilepath   The path to the xml file
             * \param xmlSchemaPath The path to the xml schema file
             */
            static bool checkIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath);

            //! Check if the provided xml file path is valid
            /*!
             * \param xmlFilepath   The path to the xml file
             */
            static void validateXmlFilepath(const std::string &xmlFilepath);

            //! Check if the provided xml schema file path is valid
            /*!
             * \param xmlSchemaPath The path to the xml schema
             */
            static void validateXmlSchemaPath(const std::string &xmlSchemaPath);


            // Constants
            static const std::string ERR_INVALID_XML_FILEPATH;
            static const std::string ERR_INVALID_SCHEMA_FILEPATH;

            static const std::string ERR_SCHEMA_CONTENTS;

    };

};

#endif
