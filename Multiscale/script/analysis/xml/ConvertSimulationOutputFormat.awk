# Commands executed before going through each line of the file
BEGIN {
    FS="\t";

    tmpNrOfCells=0; 
    nrOfCells=0;
} 

# Commands executed when the first field is "Time"
($1 == "Time") {
    tmpNrOfCells = 0;
} 

# Commands executed when the line is empty
($0 == "") {
    nrOfCells = tmpNrOfCells; 
    tmpNrOfCells = 0;
} 

# Commands executed when the line is not empty and the first field is not "Time"
(($1 != "Time") && ($0 != "")) {
    xCoordinates[$1] = xCoordinates[$1] "," $3; 
    yCoordinates[$1] = yCoordinates[$1] "," $4; 
    times[$1] = $1; 
    
    tmpNrOfCells++;
} 

# Commands executed after going through each line of the file
END {
    header = "Time"; 

    for (i = 1; i <= nrOfCells; i++) {
        header = header ",X_" i
    } 

    for (i = 1; i <= nrOfCells; i++) {
        header = header ",Y_" i; 
    } 

    print header; 

    n = asort(times); 

    for (i = 1; i <= n; i++) {
        print times[i] xCoordinates[times[i]] yCoordinates[times[i]];
    }
}
