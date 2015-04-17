#!/bin/bash

###############################################################################
#
# A script for executing the probabilistic black box model checker Mule for
# a given set of PBLMSTL statements, multiscale spatio-temporal traces, type
# semantics table, output folder, extra evaluation time and extra evaluation 
# program path.
#
###############################################################################

# Check if the required number of parameters was provided
if [[ $# -ne 7 ]];
then
    echo "Please run the script with the required parameters: $0 <path-to-mule> <input-folder-PBLMSTL> <input-folder-traces> <multiscale-architecture-graph> <output-folder> <extra-evaluation-time> <extra-evaluation-program-path>";

    exit 1; 
fi

# Check if the path to the Mule executable is valid
if [[ ! -f $1 ]];
then
    echo "The path to the Mule executable is invalid. Please change.";

    exit 1;
fi

# Check if the given input folder containing PBLMSTL statments input files points to a folder
if [[ ! -d $2 ]];
then
    echo "The input folder path for the PBLMSTL statements input files is invalid. Please change.";

    exit 1;
fi

# Check if the given input folder path points to a folder
if [[ ! -d $3 ]];
then
    echo "The input folder path for the multiscale spatio-temporal traces is invalid. Please change.";

    exit 1;
fi

# Check if the given multiscale architecture graph path points to a regular file
if [[ ! -f $4 ]];
then
    echo "The path for the multiscale architecture graph does not point to a regular file. Please change.";

    exit 1;
fi

# Check if the given extra evaluation time is a natural number
if [[ ! $6 =~ "^[1-9][0-9]+$" ]];
then
    echo "The extra evaluation time should be a natural number. Please change.";

    exit 1;
fi

# Check if the given extra evaluation program path points to a regular file
if [[ ! -f $7 ]];
then
    echo "The path to the extra evaluation script does not point to a regular file. Please change.";

    exit 1;
fi

# Initialize constants values
NR_EXECUTIONS_PER_PBLMSTL_INPUT_FILE=500;

# Initialize command line arguments dependent variables
muleExecutablePath=$1;
pblmstlStatementsInputFolder=$2;
multiscaleSpatioTemporalTracesFolder=$3;
multiscaleArchitectureGraph=$4;
outputFolder=$5;
extraEvaluationTime=$6;
extraEvaluationProgramPath=$7;

# Initialize the parameter values passed to the Mule model checker
muleModelCheckerType=0;
muleSpatioTemporalTraces=${multiscaleSpatioTemporalTracesFolder};
muleTypeSpecificParameters="";

# Create output folder
mkdir -p ${outputFolder};

# Run the model checker for each PBLSTL statement input file and record results
for pblmstlStatementsFile in `find ${pblmstlStatementsInputFolder} -maxdepth 1 -type f`; 
do
    # Inform the user about which PBLMSTL statements input file is evaluated
    echo "Evaluating ${pblmstlStatementsFile}...";

    # Get the filename without extension
    pblmstlStatementsBasename=${pblmstlStatementsFile##*/};
    pblmstlStatementsFilenameWithoutExtension=${pblmstlStatementsBasename%.in};

    # Initialize PBLSTML statement filename dependent variables
    pblmstlStatementsFolder=${outputFolder}/${pblmstlStatementsFilenameWithoutExtension};
    pblmstlStatementsResults="${pblmstlStatementsFolder}/${pblmstlStatementsFilenameWithoutExtension}_results.out";

    # Create the output folder specific to the PBLMSTL input file
    mkdir -p ${pblmstlStatementsFolder};

    # Create the file which will hold the overall results
    truncate -s0 ${pblmstlStatementsResults};

    # Run the model checker and record the results for the considered PBLMSTL input file
    for i in `seq 1 1 ${NR_EXECUTIONS_PER_PBLMSTL_INPUT_FILE}`;
    do
        # Initialize the name of the result file corresponding to this particular execution
        pblmstlStatementsNthResults="${pblmstlStatementsFolder}/${pblmstlStatementsFilenameWithoutExtension}_${i}.out";

        # Run the model checker
        /usr/bin/time -f '%E' ${muleExecutablePath} --model-checker-type ${muleModelCheckerType} --logic-queries ${pblmstlStatementsFile} --spatial-temporal-traces ${muleSpatioTemporalTraces} --multiscale-architecture-graph ${multiscaleArchitectureGraph} --extra-evaluation-time ${extraEvaluationTime} --extra-evaluation-program ${extraEvaluationProgramPath} ${muleTypeSpecificParameters} --verbose 1>${pblmstlStatementsNthResults} 2>&1;

        # Get the specific information of interest
        modelCheckerExecutionId=${i};
        modelCheckingResult=`cat ${pblmstlStatementsNthResults} | egrep "\[ RESULT   \] The logic property holds: .*" | egrep -o "[^ ]+$"`;
        nrOfEvaluatedTraces=`cat ${pblmstlStatementsNthResults} | tail -n3 | head -n1 | egrep -o "[0-9]+/[0-9]+" | cut -d"/" -f2`;
        nrOfTracesEvaluatedTrue=`cat ${pblmstlStatementsNthResults} | tail -n3 | head -n1 | egrep -o "[0-9]+/[0-9]+" | cut -d"/" -f1`;
        nrOfTracesEvaluatedFalse=$((${nrOfEvaluatedTraces} - ${nrOfTracesEvaluatedTrue}));
        executionTime=`cat ${pblmstlStatementsNthResults} | tail -n1`;

        # Output summary results to the centralised results file
        echo "${modelCheckerExecutionId} ${modelCheckingResult} ${nrOfEvaluatedTraces} ${nrOfTracesEvaluatedTrue} ${nrOfTracesEvaluatedFalse} ${executionTime}" >> ${pblmstlStatementsResults};
    done
done
