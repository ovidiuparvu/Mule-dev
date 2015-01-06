# Function used to initialise the grids of cells, CDK1, Plk1 and APC corresponding
# to the current timepoint index
function initialiseGridsForTimepointIndex(timepointIndex, gridOfCells, gridOfCDK1, gridOfPlk1, gridOfAPC,    i, j) {
    for (i = 0; i <= DISCRETISED_SPACE_RESOLUTION; i++) {
        for (j = 0; j <= DISCRETISED_SPACE_RESOLUTION; j++) {
            gridOfCells[timepointIndex, i, j] = 0;
            gridOfCDK1[timepointIndex, i, j] = 0;
            gridOfPlk1[timepointIndex, i, j] = 0;
            gridOfAPC[timepointIndex, i, j] = 0;
        }
    }
}

# Normalise the value of the provided coordinate
function normalizeCoordinateValue(coordinateValue, maxCoordinateValue) {
    # Ensure the coordiante value is greater or equal to zero
    while (coordinateValue < 0) {
        coordinateValue = maxCoordinateValue + coordinateValue;
    }

    # Ensure the coordinate value is smaller or equal to maxCoordinateValue
    while (coordinateValue > maxCoordinateValue) {
        coordinateValue = coordinateValue - maxCoordinateValue;
    }

    # Return the normalized coordinate value
    return coordinateValue;
}

# Create header line considering the given prefix
function createHeaderLine(prefix,    i, headerLine) {
    # Initialise the header line
    headerLine = "";

    # Create the header line
    for (i = 0; i <= DISCRETISED_SPACE_RESOLUTION; i++) {
        for (j = 0; j <= DISCRETISED_SPACE_RESOLUTION; j++) {
            headerLine = headerLine "," prefix "_" i "_" j
        }
    } 

    # Return the header line
    return headerLine;
}

# Create contents line considering the given matrix and timepoint index
function createContentsLine(matrixOfValues, timepointIndex,    i, j) {
    # Initialise the contents line
    contentsLine = "";

    # Create the contents line
    for (i = 0; i <= DISCRETISED_SPACE_RESOLUTION; i++) {
        for (j = 0; j <= DISCRETISED_SPACE_RESOLUTION; j++) {
            contentsLine = contentsLine "," matrixOfValues[timepointIndex, i, j];
        }
    }

    # Return the contents line
    return contentsLine;
}


###############################################################################
###############################################################################


# Commands executed before going through each line of the file
BEGIN {
    # Initialise the field separator
    FS="\t";
    
    # Initialise the timepoint index with the first possible value "0"
    lastTimepointIndex = 0;
} 

# Commands executed when the first field is "Time"
($1 == "Time") {
    # Initialise the grid of cells, CDK1, Plk1 and APC corresponding to the 
    # current timepoint index
    initialiseGridsForTimepointIndex(lastTimepointIndex, gridOfCells, gridOfCDK1, gridOfPlk1, gridOfAPC);
} 

# Commands executed when the line is empty
($0 == "") {
    # Increment the value of timepoint index 
    lastTimepointIndex++;

    # Initialise the grid of cells, CDK1, Plk1 and APC corresponding to the 
    # current timepoint index
    initialiseGridsForTimepointIndex(lastTimepointIndex, gridOfCells, gridOfCDK1, gridOfPlk1, gridOfAPC);
}

# Commands executed when the line is not empty and the first field is not "Time"
(($1 != "Time") && ($0 != "")) {
    # Compute the value of the current timepoint
    timepoints[lastTimepointIndex] = ($1 * 100);

    # Obtain the coordinates of the discretised spatial position to which the 
    # values on the line correspond
    xCoordinate = $3; 
    yCoordinate = $4; 

    # Ensure that the values of the coordinates are greater or equal to zero
    # and smaller or equal to DISCRETISED_SPACE_RESOLUTION
    xCoordinate = normalizeCoordinateValue(xCoordinate, DISCRETISED_SPACE_RESOLUTION);
    yCoordinate = normalizeCoordinateValue(yCoordinate, DISCRETISED_SPACE_RESOLUTION);
    
    # Convert the coordinates values to integers
    xCoordinate = int(xCoordinate + 0.5); 
    yCoordinate = int(yCoordinate + 0.5); 

    # Update the values of the corresponding grid positions
    gridOfCells[lastTimepointIndex, xCoordinate, yCoordinate]++;
    gridOfCDK1[lastTimepointIndex, xCoordinate, yCoordinate] = gridOfCDK1[lastTimepointIndex, xCoordinate, yCoordinate] + $5;
    gridOfPlk1[lastTimepointIndex, xCoordinate, yCoordinate] = gridOfPlk1[lastTimepointIndex, xCoordinate, yCoordinate] + $6;
    gridOfAPC[lastTimepointIndex, xCoordinate, yCoordinate]  = gridOfAPC[lastTimepointIndex, xCoordinate, yCoordinate] + $7;
} 

# Commands executed after going through each line of the file
END {
    # Construct the header line
    header = "Time"; 
    
    header = header createHeaderLine("Cells");
    header = header createHeaderLine("CDK1");
    header = header createHeaderLine("PLK1");
    header = header createHeaderLine("APC");

    # Print the header line
    print header; 

    # Create and print the contents lines  
    contentsLine = "";

    # Print contents lines corresponding to each timepoint
    for (i = 0; i < lastTimepointIndex; i++) {
        contentsLine = timepoints[i];

        contentsLine = contentsLine createContentsLine(gridOfCells, i);
        contentsLine = contentsLine createContentsLine(gridOfCDK1, i);
        contentsLine = contentsLine createContentsLine(gridOfPlk1, i);
        contentsLine = contentsLine createContentsLine(gridOfAPC, i);

        print contentsLine;
    }
}
