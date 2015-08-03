#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <cstdio>

using namespace multiscale;
using namespace multiscale::verification;


// Evaluate the abstract syntax tree considering the provided time series data
void evaluateAbstractSyntaxTree(AbstractSyntaxTree &abstractSyntaxTree,
                                const std::string &logicProperty,
                                SpatialTemporalTrace &timeseries) {
    MultiscaleArchitectureGraph multiscaleArchitectureGraph;

    // Evaluate abstract syntax tree considering the provided time series data
    bool evaluationResult = abstractSyntaxTree.evaluate(timeseries, multiscaleArchitectureGraph);

    // Output the result of the evaluation and the corresponding logic property
    printf("%c ::: %s", (evaluationResult ? 'T' : 'F') , logicProperty.c_str());
}

// Evaluate logic properties considering the provided time series data
int evaluateLogicProperties(const std::vector<std::string> &logicProperties,
                            SpatialTemporalTrace &timeseries) {
    AbstractSyntaxTree abstractSyntaxTree;

    for (const std::string &logicProperty : logicProperties) {
        // Create a new parser for the provided logic property
        Parser parser(logicProperty);

        // Parse the logic property and create the corresponding abstract syntax tree
        parser.parse(abstractSyntaxTree);

        // Evaluate the abstract syntax tree considering the provided time series data
        evaluateAbstractSyntaxTree(abstractSyntaxTree, logicProperty, timeseries);
    }

    return EXEC_SUCCESS_CODE;
}

// Evaluate logic properties considering the provided time series data
int evaluateLogicProperties(const std::string &timeseriesInputFilePath,
                            const std::string &logicPropertiesInputFilePath) {
    TemporalDataReader timeseriesReader;
    LogicPropertyDataReader logicPropertiesReader;

    std::vector<std::string> logicProperties
        = logicPropertiesReader.readLogicPropertiesFromFile(logicPropertiesInputFilePath);

    SpatialTemporalTrace timeseries
        = timeseriesReader.readTimeSeriesFromFile(timeseriesInputFilePath);

    return evaluateLogicProperties(logicProperties, timeseries);
}

// Main program
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: NumericCsvModelCheckerSample <timeseries-csv-input-file> <logic-properties-input-file>.\n");

        return EXEC_ERR_CODE;
    }

    try {
        return evaluateLogicProperties(std::string(argv[1]), std::string(argv[2]));
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);
    } catch(...) {
        printf("Exception of unknown type!\n");
    }

    return EXEC_ERR_CODE;
}
