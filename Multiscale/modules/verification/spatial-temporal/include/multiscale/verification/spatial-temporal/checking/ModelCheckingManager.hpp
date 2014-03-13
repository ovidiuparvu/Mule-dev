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

                std::string                     logicQueriesFilepath;  /*!< The path to the file containing logic queries */
                std::string                     tracesFolderPath;      /*!< The path to the folder containing traces */

                Parser                          parser;                 /*!< The parser used to verify if logical queries
                                                                            are syntactically correct */

                std::vector<std::string>        logicQueries;           /*!< The collection of logic queries */
                std::vector<AbstractSyntaxTree> abstractSyntaxTrees;    /*!< The collection of logic queries */
                std::vector<ModelChecker>       modelCheckers;          /*!< The collection of model checkers */

                SpatialTemporalDataReader       traceReader;            /*!< The behaviour/trace reader */

            public:

                ModelCheckingManager(const std::string &logicQueriesFilepath, const std::string &tracesFolderpath);
                ~ModelCheckingManager();

                //! Run the model checking tasks
                void runModelCheckingTasks();

            private:

                //! Initialise the model checking manager considering the given logic queries input file and traces folder
                /*!
                 * \param logicQueriesFilepath  The path to the logic queries input file
                 * \param tracesFolderPath      The path to the folder containing traces
                 */
                void initialise(const std::string &logicQueriesFilepath, const std::string &tracesFolderPath);


        };

    };

};

#endif
