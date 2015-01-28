# Constants initialisations
# (TODO: Update)
caseStudy="AcuteInflammationOfGutAndLung";
caseStudyTypeSemanticsTable="type_semantics_table_acute_inflammation_of_gut_and_lung.xml";

# Path initialisations
modelCheckerExecutionScript="/home/ovidiu/Repositories/git/multiscale/Multiscale/script/verification/ExecuteStatisticalModelCheckingUsingMuleForEntireSpecificationNoExtraEvaluation.sh";
modelCheckerPath="/home/ovidiu/Repositories/git/multiscale/Multiscale/bin/Mule";
queriesInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/queries";
mstmlInputFolder="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/SpatioTemporalAnalysis/mstml/";
typeSemanticsTablePath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/type_semantics_table/${caseStudyTypeSemanticsTable}";
outputFolderPath="/media/seagate3tb/ModelChecking/CaseStudies/${caseStudy}/ModelChecking/results";

# Command used to run the model checking task
${modelCheckerExecutionScript} ${modelCheckerPath} ${queriesInputFolder} ${mstmlInputFolder} ${typeSemanticsTablePath} ${outputFolderPath}
