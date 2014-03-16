#include "multiscale/util/ConsolePrinter.hpp"
#include "multiscale/verification/spatial-temporal/checking/ModelCheckingOutputWriter.hpp"

using namespace multiscale::verification;


void ModelCheckingOutputWriter::printIntroductionMessage() {
    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_NAME, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_COPYRIGHT, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag(MSG_EMPTY, TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_MODEL_CHECKING_DESC, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag(MSG_EMPTY, TAG_INTRO, ColourCode::CYAN);
    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_MODEL_CHECKING_TYPE, TAG_INTRO, ColourCode::CYAN); // TODO: Implement type completion
    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_MODEL_CHECKING_PARAMETERS, TAG_INTRO, ColourCode::CYAN); // TODO: Implement parameters completion
    ConsolePrinter::printMessageWithColouredTag(MSG_EMPTY, TAG_INTRO, ColourCode::CYAN);

    ConsolePrinter::printMessageWithColouredTag(MSG_INTRO_CONTACT, TAG_INTRO, ColourCode::CYAN);
}

void ModelCheckingOutputWriter::printParsingLogicPropertyMessage(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(logicProperty, TAG_PARSING, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResultMessage(bool doesPropertyHold,
                                                                const std::string &detailedResult,
                                                                const std::string &logicProperty) {
    printLogicPropertyForResult(logicProperty);
    printModelCheckingResult(doesPropertyHold);
    printModelCheckingDetailedResult(doesPropertyHold, detailedResult);
    printSeparatorForResult();
}

void ModelCheckingOutputWriter::printSuccessMessage() {
    ConsolePrinter::printColouredMessage(TAG_SUCCESS, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printFailedMessage() {
    ConsolePrinter::printColouredMessage(TAG_FAILED, ColourCode::RED);
}

void ModelCheckingOutputWriter::printLogicPropertyForResult(const std::string &logicProperty) {
    ConsolePrinter::printMessageWithColouredTag(logicProperty, TAG_RESULT, ColourCode::GREEN);
}

void ModelCheckingOutputWriter::printModelCheckingResult(bool doesPropertyHold) {
    if (doesPropertyHold) {
        ConsolePrinter::printMessageWithColouredTag(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_TRUE,
                                                    TAG_RESULT, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(MSG_LOGIC_PROPERTY_HOLDS + MSG_LOGIC_PROPERTY_HOLDS_FALSE,
                                                    TAG_RESULT, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printModelCheckingDetailedResult(bool doesPropertyHold,
                                                                 const std::string &detailedResult) {
    if (doesPropertyHold) {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, TAG_RESULT, ColourCode::GREEN);
    } else {
        ConsolePrinter::printMessageWithColouredTag(detailedResult, TAG_RESULT, ColourCode::RED);
    }
}

void ModelCheckingOutputWriter::printSeparatorForResult() {
    ConsolePrinter::printMessageWithColouredTag(MSG_EMPTY, TAG_SEPARATOR, ColourCode::GREEN);
}


// Constants
const std::string ModelCheckingOutputWriter::TAG_INTRO      = "[ INTRO    ]";
const std::string ModelCheckingOutputWriter::TAG_INIT       = "[ INIT     ]";
const std::string ModelCheckingOutputWriter::TAG_PARSING    = "[ PARSING  ]";
const std::string ModelCheckingOutputWriter::TAG_RESULT     = "[ RESULT   ]";
const std::string ModelCheckingOutputWriter::TAG_SUCCESS    = "[ SUCCESS  ]";
const std::string ModelCheckingOutputWriter::TAG_FAILED     = "[ FAILED   ]";
const std::string ModelCheckingOutputWriter::TAG_SEPARATOR  = "[==========]";

const std::string ModelCheckingOutputWriter::MSG_EMPTY      = "";

const std::string ModelCheckingOutputWriter::MSG_INTRO_NAME      = "Mudi @PROJECT_VERSION_MAJOR@.@PROJECT_VERSION_MINOR@.@PROJECT_VERSION_BUILD@ (Multidimensional model checker)"; // TODO: Implement version replacement
const std::string ModelCheckingOutputWriter::MSG_INTRO_COPYRIGHT = "Copyright Ovidiu Pârvu 2014";

const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_DESC          = "Model checking description";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_TYPE          = "Type:       ";
const std::string ModelCheckingOutputWriter::MSG_INTRO_MODEL_CHECKING_PARAMETERS    = "Parameters: ";

const std::string ModelCheckingOutputWriter::MSG_INTRO_CONTACT   = "For more details, recommendations or suggestions feel free to contact me at <ovidiu.parvu[AT]gmail.com>.";

const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS          = "The logic property holds: ";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_TRUE     = "TRUE";
const std::string ModelCheckingOutputWriter::MSG_LOGIC_PROPERTY_HOLDS_FALSE    = "FALSE";
