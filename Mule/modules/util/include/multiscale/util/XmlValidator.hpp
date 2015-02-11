#ifndef XMLVALIDATOR_HPP
#define XMLVALIDATOR_HPP

#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>

#include <string>

XERCES_CPP_NAMESPACE_USE


namespace multiscale {

    //! Class used to validate xml files
    class XmlValidator {

        public:

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * \param xmlFilepath       The path to the xml file
             * \param xmlSchemaPath     The path to the xml schema file
             */
            static bool isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath);

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * In case the xml file is not valid the error message is retrieved in xmlErrorMessage.
             *
             * \param xmlFilepath       The path to the xml file
             * \param xmlSchemaPath     The path to the xml schema file
             * \param xmlErrorMessage   The error message explaining why the xml file is not valid
             */
            static bool isValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                       std::string &xmlErrorMessage);

        private:

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * In case the xml file is not valid the error message is retrieved in xmlErrorMessage.
             *
             * \param xmlFilepath       The path to the xml file
             * \param xmlSchemaPath     The path to the xml schema file
             * \param xmlErrorMessage   The error message explaining why the xml file is not valid
             */
            static bool isValidXmlPathAndFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                              std::string &xmlErrorMessage);

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * In case the xml file is not valid the error message is retrieved in xmlErrorMessage.
             *
             * \param xmlFilepath       The path to the xml file
             * \param xmlSchemaPath     The path to the xml schema file
             * \param xmlErrorMessage   The error message explaining why the xml file is not valid
             */
            static bool verifyIfValidXmlFile(const std::string &xmlFilepath, const std::string &xmlSchemaPath,
                                             std::string &xmlErrorMessage);

            //! Check if the given xml file is valid considering the provided xml schema (xsd file)
            /*! The validation is performed using the Xerces C++ library.
             *
             * \param xmlFilepath       The path to the xml file
             * \param xmlSchemaPath     The path to the xml schema file
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

            //! Load the xml schema using the given parser
            /*!
             * \param parser        The given xml DOM parser
             * \param xmlSchemaPath The file path to the xml schema
             */
            static void loadParserSchema(const std::string &xmlSchemaPath, XercesDOMParser &parser);

            //! Configure the given parser
            /*!
             * \param parser The given xml DOM parser
             */
            static void configureParser(XercesDOMParser &parser);


            // Constants
            static const std::string ERR_INVALID_XML_FILEPATH;
            static const std::string ERR_INVALID_SCHEMA_FILEPATH;

            static const std::string ERR_SCHEMA_CONTENTS;

        private:

            //! Class used for handling errors during the xml file validation process
            class XmlValidationErrorHandler : public ErrorHandler {

                public:

                    //! Handle warning messages
                    /*!
                     * \param ex    The exception thrown during the validation process
                     */
                    void warning(const SAXParseException& ex) override;

                    //! Handle recoverable error messages
                    /*!
                     * \param ex    The exception thrown during the validation process
                     */
                    void error(const SAXParseException& ex) override;

                    //! Handle non-recoverable error messages
                    /*!
                     * \param ex    The exception thrown during the validation process
                     */
                    void fatalError(const SAXParseException& ex) override;

                    //! Reinitialise the error handler
                    void resetErrors() override;

                private:

                    //! Handle the exception thrown during the validation process
                    /*!
                     * \param ex    The exception thrown during the validation process
                     */
                    void handleValidationException(const SAXParseException& ex);

                    //! Construct the exception message for the given exception
                    /*!
                     * \param ex    The exception thrown during the validation process
                     */
                    std::string constructExceptionMessage(const SAXParseException &ex);

                    // Constants
                    static const std::string ERR_EXCEPTION_BEGIN_MSG;

                    static const std::string ERR_EXCEPTION_LINE_MSG;
                    static const std::string ERR_EXCEPTION_COLUMN_MSG;
                    static const std::string ERR_EXCEPTION_MIDDLE_MSG;

                    static const std::string ERR_EXCEPTION_END_MSG;

            };

    };

};


#endif
