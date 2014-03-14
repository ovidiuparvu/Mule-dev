#!/bin/bash

if [ $# -ne 4 ];
then
    echo "Usage: GetDictyosteliumPositionsFromResults.sh <input_file> <output_file> <height> <width>.";
    
    exit 1;
fi

# Transpose the entire file
awk -F , '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str","a[i,j];
        }
        print str
    }
}' $1 > tmp_file

# Sort the file using natural ordering and store the results in a file
cat tmp_file | head -n1 > tmp_file2;
cat tmp_file | sort -V | tail -n `expr $3 \* $4` >> tmp_file2;

# Transpose the entire file containing the temporary results
awk -F , '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str","a[i,j];
        }
        print str
    }
}' tmp_file2 > $2

# Remove temporary files
rm tmp_file;
rm tmp_file2;
