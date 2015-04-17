#!/bin/bash

###############################################################################
#
# A script for executing the frequentist statistical model checker Mudi for
# a given set of PBLSTL statements, spatio-temporal traces and an output 
# folder.
#
###############################################################################

# Check if the required number of parameters was provided
if [[ $# -ne 3 ]];
then
    echo "Please run the script with the required parameters: ExecuteMudiStatistical.sh <input-folder-PBLSTL> <input-folder-traces> <output-folder>";

    exit 1; 
fi

# Check if the given input folder containing PBLSTL statments input files is valid
if [[ ! -d $1 ]];
then
    echo "The input folder path for the PBLSTL statements input files is invalid. Please change.";

    exit 1;
fi

# Check if the given input folder containing traces is valid
if [[ ! -d $2 ]];
then
    echo "The input folder path for the spatio-temporal traces is invalid. Please change.";

    exit 1;
fi

# Initialize constants values
NR_EXECUTIONS_PER_PBLSTL_INPUT_FILE=500;

# Initialize command line arguments dependent variables
pblstlStatementsInputFolder=$1;
spatioTemporalTracesFolder=$2;
outputFolder=$3;

# Initialize the parameter values passed to the Mudi model checker
mudiModelCheckerType=1;
mudiSpatioTemporalTraces=${spatioTemporalTracesFolder};
mudiExtraEvaluationTime=0;
mudiTypeSpecificParameters="--type-I-error 0.05 --type-II-error 0.05";

# Create output folder
mkdir -p ${outputFolder};

# Run the model checker for each PBLSTL statement input file and record results
for pblstlStatementsFile in `find ${pblstlStatementsInputFolder} -type f`; 
do
    # Inform the user about which PBLSTL statements input file is evaluated
    echo "Evaluating ${pblstlStatementsFile}...";

    # Get the filename without extension
    pblstlStatementsBasename=${pblstlStatementsFile##*/};
    pblstlStatementsFilenameWithoutExtension=${pblstlStatementsBasename%.in};

    # Initialize pblstl statement filename dependent variables
    pblstlStatementsFolder=${outputFolder}/${pblstlStatementsFilenameWithoutExtension};
    pblstlStatementsResults="${pblstlStatementsFolder}/${pblstlStatementsFilenameWithoutExtension}_results.out";

    # Create the output folder specific to the PBLSTL input file
    mkdir -p ${pblstlStatementsFolder};

    # Create the file which will hold the overall results
    truncate -s0 ${pblstlStatementsResults};

    # Run the model checker and record the results for this particular PBLSTL input file
    for i in `seq 1 1 ${NR_EXECUTIONS_PER_PBLSTL_INPUT_FILE}`;
    do
        # Initialize the name of the result file corresponding to this particular execution
        pblstlStatementsNthResults="${pblstlStatementsFolder}/${pblstlStatementsFilenameWithoutExtension}_${i}.out";

        # Run the model checker
        /usr/bin/time -f '%E' bin/Mudi --model-checker-type ${mudiModelCheckerType} --logic-queries ${pblstlStatementsFile} --spatial-temporal-traces ${mudiSpatioTemporalTraces} --extra-evaluation-time ${mudiExtraEvaluationTime} ${mudiTypeSpecificParameters} --verbose 1>${pblstlStatementsNthResults} 2>&1;

        # Get the specific information of interest
        modelCheckerExecutionId=${i};
        modelCheckingResult=`cat ${pblstlStatementsNthResults} | egrep "\[ RESULT   \] The logic property holds: .*" | egrep -o "[^ ]+$"`;
        nrOfEvaluatedTraces=`cat ${pblstlStatementsNthResults} | tail -n3 | head -n1 | egrep -o "[0-9]+/[0-9]+" | cut -d"/" -f2`;
        nrOfTracesEvaluatedTrue=`cat ${pblstlStatementsNthResults} | tail -n3 | head -n1 | egrep -o "[0-9]+/[0-9]+" | cut -d"/" -f1`;
        nrOfTracesEvaluatedFalse=$((${nrOfEvaluatedTraces} - ${nrOfTracesEvaluatedTrue}));
        executionTime=`cat ${pblstlStatementsNthResults} | tail -n1`;

        echo "${modelCheckerExecutionId} ${modelCheckingResult} ${nrOfEvaluatedTraces} ${nrOfTracesEvaluatedTrue} ${nrOfTracesEvaluatedFalse} ${executionTime}" >> ${pblstlStatementsResults};
    done
done
