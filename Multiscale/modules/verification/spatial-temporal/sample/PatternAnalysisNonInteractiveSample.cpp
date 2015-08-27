#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Evaluate the abstract syntax tree considering the provided time series
void evaluateAbstractSyntaxTree(AbstractSyntaxTree &abstractSyntaxTree,
                                SpatialTemporalTrace &timeSeries) {
    MultiscaleArchitectureGraph multiscaleArchitectureGraph;

    bool evaluationResult = abstractSyntaxTree.evaluate(timeSeries, multiscaleArchitectureGraph);

    std::cout << (evaluationResult ? "T" : "F") << std::endl;
}

// Analyse patterns considering the provided logic properties and time series
int analysePatterns(const std::vector<std::string> &logicProperties,
                    SpatialTemporalTrace &timeSeries) {
    AbstractSyntaxTree result;

    for (const std::string &logicProperty : logicProperties) {
        // Create a new parser for the provided logic property
        Parser parser(logicProperty);

        // Parse the logic property and create the corresponding abstract syntax tree
        parser.parse(result);

        // Evaluate the abstract syntax tree considering the provided timeSeries
        evaluateAbstractSyntaxTree(result, timeSeries);
    }

    return EXEC_SUCCESS_CODE;
}

// Analyse patterns considering time series data and logic properties provided in the input files
int analysePatterns(const std::string &timeSeriesInputFilePath,
                    const std::string &logicPropertiesInputFilePath) {
    TemporalDataReader timeSeriesReader;
    LogicPropertyDataReader logicPropertiesReader;

    std::vector<std::string> logicProperties
        = logicPropertiesReader.readLogicPropertiesFromFile(logicPropertiesInputFilePath);

    SpatialTemporalTrace timeSeries
        = timeSeriesReader.readTimeSeriesFromFile(timeSeriesInputFilePath);

    return analysePatterns(logicProperties, timeSeries);
}

// Main program
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: PatternAnalysisNonInteractiveSample "
                  << "<time-series-input-file> <logic-properties-input-file>"
                  << std::endl;

        return EXEC_ERR_CODE;
    }

    try {
        return analysePatterns(std::string(argv[1]), std::string(argv[2]));
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXEC_ERR_CODE;
}
