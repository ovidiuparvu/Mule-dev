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


// Evaluate the abstract syntax tree considering the provided timeseries
void evaluateAbstractSyntaxTree(AbstractSyntaxTree &abstractSyntaxTree,
                                const SpatialTemporalTrace &timeseries) {
    TypeSemanticsTable typeSemanticsTable;

    bool evaluationResult = abstractSyntaxTree.evaluate(timeseries, typeSemanticsTable);

    std::cout << (evaluationResult ? "T" : "F") << std::endl;
}

// Analyse patterns considering the provided logic properties and timeseries
int analysePatterns(const std::vector<std::string> &logicProperties,
                    const SpatialTemporalTrace &timeseries) {
    AbstractSyntaxTree result;

    for (const std::string &logicProperty : logicProperties) {
        // Create a new parser for the provided logic property
        Parser parser(logicProperty);

        // Parse the logic property and create the corresponding abstract syntax tree
        parser.parse(result);

        // Evaluate the abstract syntax tree considering the provided timeseries
        evaluateAbstractSyntaxTree(result, timeseries);
    }

    return EXEC_SUCCESS_CODE;
}

// Analyse patterns considering timeseries data and logic properties provided in the input files
int analysePatterns(const std::string &timeseriesInputFilePath,
                    const std::string &logicPropertiesInputFilePath) {
    TemporalDataReader timeseriesReader;
    LogicPropertyDataReader logicPropertiesReader;

    std::vector<std::string> logicProperties
        = logicPropertiesReader.readLogicPropertiesFromFile(logicPropertiesInputFilePath);

    SpatialTemporalTrace timeseries
        = timeseriesReader.readTimeseriesFromFile(timeseriesInputFilePath);

    return analysePatterns(logicProperties, timeseries);
}

// Main program
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: PatternAnalysisNonInteractiveSample "
                  << "<timeseries-input-file> <logic-properties-input-file>"
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
