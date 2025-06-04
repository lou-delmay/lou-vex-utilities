# lou-vex-utilities

## range

Functions like py range.

`int[] range(int n)`

Giving it a single integer input n returns an array going from 0 to that n-1

`int[] range(int a, int b)`

Giving it two integers a and b returns an array starting at min(a,b) and ending at max(a,b)-1

## swap_elements

`int[] swap_elements(int[] list, int a, int b)`

`float[] swap_elements(float[] list, int a, int b)`

`vector2[] swap_elements(vector2[] list, int a, int b)`

`vector[] swap_elements(vector[] list, int a, int b)`

`vector4[] swap_elements(vector4[] list, int a, int b)`

`string[] swap_elements(string[] list, int a, int b)`

`matrix[] swap_elements(matrix[] list, int a, int b)`

`matrix3[] swap_elements(matrix3[] list, int a, int b)`

Swaps two elements a and b of an array

## fisher_yates

`int[] fisher_yates(int[] list, int seed)`

`float[] fisher_yates(float[] list, int seed)`

`vector2[] fisher_yates(vector2[] list, int seed)`

`vector[] fisher_yates(vector[] list, int seed)`

`vector4[] fisher_yates(vector4[] list, int seed)`

`string[] fisher_yates(string[] list, int seed)`

`matrix[] fisher_yates(matrix[] list, int seed)`

`matrix3[] fisher_yates(matrix3[] list, int seed)`

Shuffles an array based on the seed, single threaded

## spherical_to_cartesian

`vector spherical_to_cartesian(vector)`

`vector spherical_to_cartesian(float, float, float)`

Converts Spherical to Cartesian corrdinates, duh !

## cartesian_to_spherical

`vector cartesian_to_spherical(vector)`

`vector cartesian_to_spherical(float, float, float)`

Converts Cartesian to Spherical corrdinates, duh !