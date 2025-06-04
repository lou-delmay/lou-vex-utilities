# lou-vex-utilities

## range
Functions like py range.
`int[] range(int n)`
Giving it a single integer input n returns an array going from 0 to that n-1
`int[] range(int a, int b)`
Giving it two integers a and b returns an array starting at min(a,b) and ending at max(a,b)-1

## swap_elements
`int[] swap_elements(int[] list, int a, int b)`
Swaps two elements a and b of an array

## fisher_yates
`int[] fisher_yates(int[] list, int seed)`
Shuffles an array based on the seed, single threaded

## spherical_to_cartesian
`vector spherical_to_cartesian(vector)`
`vector spherical_to_cartesian(float, float, float)`
Converts Spherical to Cartesian corrdinates, duh !

## cartesian_to_spherical
`vector cartesian_to_spherical(vector)`
`vector cartesian_to_spherical(float, float, float)`
Converts Cartesian to Spherical corrdinates, duh !