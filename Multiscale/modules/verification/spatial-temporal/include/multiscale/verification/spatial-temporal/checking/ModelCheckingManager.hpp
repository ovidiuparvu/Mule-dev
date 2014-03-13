#ifndef MODELCHECKINGMANAGER_HPP
#define MODELCHECKINGMANAGER_HPP

#include "multiscale/verification/spatial-temporal/checking/ModelChecker.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <string>
#include <vector>


namespace multiscale {

    namespace verification {

        //! Class for managing the model checking processes
        class ModelCheckingManager {

            private:

                Parser                          parser;                     /*!< The parser used to verify if logical properties
                                                                                 are syntactically correct */

                std::vector<std::string>        logicProperties;            /*!< The collection of logic properties */
                std::vector<AbstractSyntaxTree> abstractSyntaxTrees;        /*!< The collection of abstract syntax tree obtained after
                                                                                 parsing the logic properties */

                LogicPropertyDataReader         logicPropertyReader;        /*!< The logic property reader */
                SpatialTemporalDataReader       traceReader;                /*!< The behaviour/trace reader */

                std::vector<std::shared_ptr<ModelChecker>> modelCheckers;   /*!< The collection of model checkers */

            public:

                ModelCheckingManager(const std::string &logicPropertyFilepath, const std::string &tracesFolderpath);
                ~ModelCheckingManager();

                //! Run the model checking tasks
                void runFrequencyModelChecking();

            private:

                //! Initialise the model checking manager considering the given logic properties input file and traces folder
                /*!
                 * \param logicPropertyFilepath The path to the logic properties input file
                 * \param tracesFolderPath      The path to the folder containing traces
                 */
                void initialise(const std::string &logicPropertyFilepath, const std::string &tracesFolderPath);

                //! Initialise the logic properties using the provided input file
                /*!
                 * \param logicPropertyFilepath The path to the logic properties input file
                 */
                void initialiseLogicProperties(const std::string &logicPropertiesFilepath);

                //! Initialise the spatial temporal trace reader using the provided folder path
                /*!
                 * \param tracesFolderPath  The path to the folder containing traces
                 */
                void initialiseTraceReader(const std::string &tracesFolderPath);

                //! Parse the logic properties and create abstract syntax trees whenever a logic property was successfully parsed
                void parseLogicProperties();

                //! Parse the given logic property and return true if parsing was successful and false otherwise
                /*! Exceptions are catched in this method
                 *
                 * \param logicProperty The given logic property
                 */
                bool parseLogicProperty(const std::string &logicProperty);

                //! Parse the given logic property and return true if parsing was successful and false otherwise
                /*! Exceptions are not catched in this method
                 *
                 * \param logicProperty The given logic property
                 */
                bool isValidLogicProperty(const std::string &logicProperty);

                //! Create the model checker instances
                /*! Each model checker instance verifies one logic property
                 */
                void createModelCheckers();

                //! Run the model checkers and verify the logic properties
                void runModelCheckers();

                //! Output the model checking results
                void outputModelCheckersResults();

        };

    };

};

#endif
