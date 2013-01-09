# Output preferences
set terminal pngcairo transparent font "Arial" fontscale 3 size 2048, 1572
set output 'mapcart2pol.png'

# Set the environment for using colorbox
set pm3d implicit at s

# Colorbox options
set style line 1234 linetype -1 linewidth 1
set colorbox border 1234
set cbrange [0:1]
set cblabel "Concentrations"

# Unset unnecessary elements
unset border
unset key
set   noxtics
set   noytics

# Plot the objects
set object 16 circle center screen 0.5, 0.5, 0 size screen 0.001 arc [0:360] 
set object 16 back fillcolor palette frac 0.1 fillstyle solid 1.00 noborder

set object 15 circle center screen 0.5, 0.5, 0 size screen 0.100667 arc [0:72] 
set object 15 back fillcolor palette frac 0.2 fillstyle solid 1.00 noborder

set object 14 circle center screen 0.5, 0.5, 0 size screen 0.100667 arc [72:144] 
set object 14 back fillcolor palette frac 0.3 fillstyle solid 1.00 noborder

set object 13 circle center screen 0.5, 0.5, 0 size screen 0.100667 arc [144:216] 
set object 13 back fillcolor palette frac 0.4 fillstyle solid 1.00 noborder

set object 12 circle center screen 0.5, 0.5, 0 size screen 0.100667 arc [216:288] 
set object 12 back fillcolor palette frac 0 fillstyle solid 1.00 noborder

set object 11 circle center screen 0.5, 0.5, 0 size screen 0.100667 arc [288:360] 
set object 11 back fillcolor palette frac 0.1 fillstyle solid 1.00 noborder

set object 10 circle center screen 0.5, 0.5, 0 size screen 0.200333 arc [0:72] 
set object 10 back fillcolor palette frac 0.3 fillstyle solid 1.00 noborder

set object 9 circle center screen 0.5, 0.5, 0 size screen 0.200333 arc [72:144] 
set object 9 back fillcolor palette frac 0.24 fillstyle solid 1.00 noborder

set object 8 circle center screen 0.5, 0.5, 0 size screen 0.200333 arc [144:216] 
set object 8 back fillcolor palette frac 0.1 fillstyle solid 1.00 noborder

set object 7 circle center screen 0.5, 0.5, 0 size screen 0.200333 arc [216:288] 
set object 7 back fillcolor palette frac 0.2 fillstyle solid 1.00 noborder

set object 6 circle center screen 0.5, 0.5, 0 size screen 0.200333 arc [288:360] 
set object 6 back fillcolor palette frac 0.5 fillstyle solid 1.00 noborder

set object 5 circle center screen 0.5, 0.5, 0 size screen 0.3 arc [0:72] 
set object 5 back fillcolor palette frac 0.9 fillstyle solid 1.00 noborder

set object 4 circle center screen 0.5, 0.5, 0 size screen 0.3 arc [72:144] 
set object 4 back fillcolor palette frac 0.1 fillstyle solid 1.00 noborder

set object 3 circle center screen 0.5, 0.5, 0 size screen 0.3 arc [144:216] 
set object 3 back fillcolor palette frac 0.2 fillstyle solid 1.00 noborder

set object 2 circle center screen 0.5, 0.5, 0 size screen 0.3 arc [216:288] 
set object 2 back fillcolor palette frac 0.22 fillstyle solid 1.00 noborder

set object 1 circle center screen 0.5, 0.5, 0 size screen 0.3 arc [288:360] 
set object 1 back fillcolor palette frac 0.34 fillstyle solid 1.00 noborder


# Set a very small range for the y values
set yrange [0.0000 : 0.00000001]

# Plot just in order for the objects to be visible
plot 1
