#include "multiscale/core/Multiscale.hpp"
#include "multiscale/exception/ExceptionHandler.hpp"
#include "multiscale/exception/InvalidInputException.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/verification/spatial-temporal/attribute/ProbabilisticLogicPropertyAttribute.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

#include <iostream>

using namespace multiscale;
using namespace multiscale::verification;


// Construct the logic statement considering the provided input file path
/*!
 * The format of the file path should be:
 *     "<NumericStateVariable1Name>_<NumericStateVariable1Name>.csv"
 */
void constructLogicStatement(std::string &logicStatement,
                             const std::string &inputFilePath) {
    std::vector<std::string> numericStateVariablesNames
        = StringManipulator::split(inputFilePath, "/_.");

    std::string firstNumericStateVariableName
        = numericStateVariablesNames[numericStateVariablesNames.size() - 3];
    std::string secondNumericStateVariableName
        = numericStateVariablesNames[numericStateVariablesNames.size() - 2];

    logicStatement = "P > 0.9 [ " + (
                         "similar(" + (
                             "[1, 19] {" + firstNumericStateVariableName + "}, " +
                             "[1, 19] {" + secondNumericStateVariableName + "}, " +
                             "5"
                         ) + ") ]"
                     );
}

// Evaluate the abstract syntax tree considering the provided trace
void evaluateAbstractSyntaxTree(AbstractSyntaxTree &abstractSyntaxTree,
                                const SpatialTemporalTrace &trace) {
    TypeSemanticsTable typeSemanticsTable;

    std::cout << (abstractSyntaxTree.evaluate(trace, typeSemanticsTable))
              << std::endl;
}

// Analyse patterns considering the provided parser and trace
int analysePatterns(Parser &parser, const SpatialTemporalTrace &trace) {
    AbstractSyntaxTree result;

    parser.parse(result);

    evaluateAbstractSyntaxTree(result, trace);

    return EXEC_SUCCESS_CODE;
}

// Analyse patterns considering timeseries data provided in the input file
int analysePatterns(const std::string &inputFilePath) {
    std::string logicStatement;
    AbstractSyntaxTree result;
    TemporalDataReader reader;

    // Construct the logic statement considering the provided input file path
    constructLogicStatement(logicStatement, inputFilePath);

    Parser parser(logicStatement);

    SpatialTemporalTrace trace = reader.read(inputFilePath);

    return analysePatterns(parser, trace);
}

// Main program
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: PatternAnalysisNonInteractiveSample <timeseries-input-file>" << std::endl;

        return EXEC_ERR_CODE;
    }

    try {
        return analysePatterns(std::string(argv[1]));
    } catch(const std::exception &e) {
        ExceptionHandler::printDetailedErrorMessage(e);
    } catch(...) {
        std::cerr << "Exception of unknown type!" << std::endl;
    }

    return EXEC_ERR_CODE;
}
