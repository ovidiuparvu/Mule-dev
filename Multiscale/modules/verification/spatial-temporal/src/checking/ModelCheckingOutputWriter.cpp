#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

using namespace multiscale::verification;


void ModelCheckingOutputWriter::printParsingLogicPropertyMessage(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(logicProperty, MSG_PARSING, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResultMessage(bool propertyHolds,
                                                                const std::string &detailedResult,
                                                                const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(logicProperty, MSG_RESULT, ColourCode::GREEN);

    if (propertyHolds) {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, MSG_RESULT, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, MSG_RESULT, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printSuccessMessage() {
    ConsolePrinter::printColouredMessage(MSG_SUCCESS, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printFailedMessage() {
    ConsolePrinter::printColouredMessage(MSG_FAILED, ColourCode::RED);
}


// Constants
const std::string ModelCheckingOutputWriter::MSG_PARSING = "[ PARSING  ]";
const std::string ModelCheckingOutputWriter::MSG_RESULT  = "[ RESULT   ]";
const std::string ModelCheckingOutputWriter::MSG_SUCCESS = "[ SUCCESS  ]";
const std::string ModelCheckingOutputWriter::MSG_FAILED  = "[ FAILED   ]";
