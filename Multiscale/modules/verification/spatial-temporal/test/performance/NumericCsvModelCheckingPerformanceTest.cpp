#include "NumericCsvModelCheckingPerformanceTest.hpp"

#include "multiscale/verification/spatial-temporal/data/LogicPropertyDataReader.hpp"
#include "multiscale/verification/spatial-temporal/data/TemporalDataReader.hpp"
#include "multiscale/verification/spatial-temporal/model/AbstractSyntaxTree.hpp"
#include "multiscale/verification/spatial-temporal/model/MultiscaleArchitectureGraph.hpp"
#include "multiscale/verification/spatial-temporal/parsing/Parser.hpp"

using namespace multiscale::verification;
using namespace multiscaletest;


double
NumericCsvModelCheckingPerformanceTest::RunNumericCsvModelCheckingPerformanceTest(
    const std::string &logicPropertiesInputFilePath,
    const std::string &timeSeriesInputFilePath
) {
    this->logicPropertiesInputFilePath = logicPropertiesInputFilePath;
    this->timeSeriesInputFilePath      = timeSeriesInputFilePath;

    return (
        RunPerformanceTest()
    );
}

void
NumericCsvModelCheckingPerformanceTest::RunTest() {
    TemporalDataReader timeSeriesReader;
    LogicPropertyDataReader logicPropertiesReader;

    std::vector<std::string> logicProperties
        = logicPropertiesReader.readLogicPropertiesFromFile(logicPropertiesInputFilePath);

    SpatialTemporalTrace timeSeries
        = timeSeriesReader.readTimeSeriesFromFile(timeSeriesInputFilePath);

    EvaluateLogicProperties(logicProperties, timeSeries);
}

void
NumericCsvModelCheckingPerformanceTest::ValidateTestResults() {}

void
NumericCsvModelCheckingPerformanceTest::EvaluateLogicProperties(
    const std::vector<std::string> &logicProperties,
    SpatialTemporalTrace &timeSeries
) {
    AbstractSyntaxTree abstractSyntaxTree;
    MultiscaleArchitectureGraph multiscaleArchitectureGraph;

    for (const std::string &logicProperty : logicProperties) {
        // Create a new parser for the provided logic property
        Parser parser(logicProperty);

        // Parse the logic property and create the corresponding abstract syntax tree
        parser.parse(abstractSyntaxTree);

        // Evaluate the abstract syntax tree considering the provided time series data
        abstractSyntaxTree.evaluate(timeSeries, multiscaleArchitectureGraph);
    }
}
