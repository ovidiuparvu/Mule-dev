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


// Print the evaluation results
void printEvaluationResults(const std::vector<std::string> &logicProperties,
                            const std::vector<bool> &evaluationResults) {
    std::size_t nrOfLogicProperties = logicProperties.size();

    // Print the evaluation result for each logic property
    for (std::size_t i = 0; i < nrOfLogicProperties; ++i) {
        printf("%c ::: %s", (evaluationResults[i] ? 'T' : 'F'), logicProperties[i].c_str());
    }
}

// Evaluate logic properties considering the provided time series data
void evaluateLogicProperties(const std::vector<std::string> &logicProperties,
                             SpatialTemporalTrace &timeSeries,
                             std::vector<bool> &evaluationResults) {
    AbstractSyntaxTree          abstractSyntaxTree;
    MultiscaleArchitectureGraph multiscaleArchitectureGraph;

    std::size_t nrOfLogicProperties = logicProperties.size();

    for (std::size_t i = 0; i < nrOfLogicProperties; ++i) {
        // Create a new parser for the provided logic property
        Parser parser(logicProperties[i]);

        // Parse the logic property and create the corresponding abstract syntax tree
        parser.parse(abstractSyntaxTree);

        // Evaluate the abstract syntax tree considering the provided time series data
        evaluationResults[i] = abstractSyntaxTree.evaluate(timeSeries, multiscaleArchitectureGraph);
    }
}

// Evaluate logic properties considering the provided time series data
int evaluateLogicProperties(const std::string &timeSeriesInputFilePath,
                            const std::string &logicPropertiesInputFilePath) {
    TemporalDataReader      timeSeriesReader;
    LogicPropertyDataReader logicPropertiesReader;

    // Read the logic properties from the given file
    std::vector<std::string> logicProperties
        = logicPropertiesReader.readLogicPropertiesFromFile(logicPropertiesInputFilePath);

    // Read the time series data from the given file
    SpatialTemporalTrace timeSeries
        = timeSeriesReader.readTimeSeriesFromFile(timeSeriesInputFilePath);

    // Define a vector for storing the result of evaluating logic properties against time series data
    std::vector<bool> evaluationResults(logicProperties.size());

    // Evaluate the logic properties
    evaluateLogicProperties(logicProperties, timeSeries, evaluationResults);

    // Print the evaluation results
    printEvaluationResults(logicProperties, evaluationResults);

    return EXEC_SUCCESS_CODE;
}

// Main program
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: NumericCsvModelCheckerSample <time-series-csv-input-file> <logic-properties-input-file>.\n");

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
