# Lou Vex Utilities

Can I get uuuuuuh 👽

# Functions
Vex functions are snake case, I chose not to divert from this with my functions to avoid janky looking code.

## range

Functions like py range.

```cpp
int[] range(int n)
```

Giving it a single integer input n returns an array going from 0 to that n-1

```cpp
int[] range(int a, int b)
```

Giving it two integers a and b returns an array starting at min(a,b) and ending at max(a,b)-1

## build_point_attribute_array
```cpp
type[] build_point_attribute_array(int geo, string attribute_name, int pts[])
type[] build_point_attribute_array(string geo, string attribute_name, int pts[])
```
Fetches a point attribute for all ***ptnums*** specified in the `int pts[]` array.
For examples using range :
```cpp
vectors positions[] = build_point_attribute_array(0,"P",range(npoints(0)));
```

## build_prim_attribute_array
```cpp
type[] build_prim_attribute_array(int geo, string attribute_name, int prs[])
type[] build_prim_attribute_array(string geo, string attribute_name, int prs[])
```
Fetches a prim attribute for all ***primnums*** specified in the `int prs[]` array.

## swap_elements

```cpp
type[] swap_elements(type[] list, int a, int b)
```

Swaps two elements a and b of an array

For example :
```cpp
int count[] = range(3,10);
// count = [3,4,5,6,7,8,9]

count = swap_elements(count,2,5);
// count = [3,4,8,6,7,5,9]
//              ^     ^
```

## fisher_yates

```cpp
type[] fisher_yates(type[] list, int seed)
```

Shuffles an array based on the seed, single threaded

## pca
```cpp
vector[] pca(vector points[])
```
Performs Principal Component Analysis on 3d vectors.
Returns an array of 4 vectors : `[ mean , first_axis, second_axis, third_axis ]`
`mean` is the average position of all vectors and the `axes` are the main components sorted in descending order.

## remove_duplicates
```cpp
type[] remove_duplicates(type list[])
```
Removes duplicate entries from a list.

## least_squares_cubic
```cpp
vector[]  least_squares_cubic(vector pos[])
vector4[] least_squares_cubic(vector4 pos[])
```
Returns 4 cubic bezier handles that approxiamtes the input curve positions as best as possible.

## curve_aproximation_least_squares_cubic
```cpp
vector[]  curve_aproximation_least_squares_cubic(vector pos[], float error_threshold)
vector4[] curve_aproximation_least_squares_cubic(vector4 pos[], float error_threshold)
```
Given a series of positions following a rough curve (something that would come out of a sim or noisy data), and an error threshold to control when to disect the curve more. This function returns a cubic bezier curve, in the form of the handles positions.

## spherical_to_cartesian

```cpp
vector spherical_to_cartesian(vector)
vector spherical_to_cartesian(float, float, float)
```

Converts Spherical to Cartesian corrdinates.

## cartesian_to_spherical

```cpp
vector cartesian_to_spherical(vector)
vector cartesian_to_spherical(float, float, float)
```

Converts Cartesian to Spherical corrdinates.

## octree_build
```cpp
void octree_build(int &octree[], int &parent_octree[], int &maxdepth)
void octree_build(int &octree[])
```
Builds an octree (or an octree and a parent octree) of the current points in the geo.

It outputs the result(s) in the specified lists 

## build_position_mass_octree
```cpp
void build_position_mass_octree(int octree[], vector pos_octree[], float mass_octree[])
```
Given an octree of the current geo, it computes the mass and average position of each leaf and branch of the octree. And outputs the result in the given arrays.

## octree_visualize
```cpp
void octree_visualize(int octree[])
void octree_visualize(int octree[], vector bbox_min, vector bbox_max)
```
Creates a visualizer of the levels of branches of the octree, giving it the bbox vectors allows for correct super position of the data and visualizer

## robert_prim_mst
```cpp
void robert_prim_mst(int firstpoint, int seed, string cost_prim_attrib)
```
Computes a minimum spanning tree starting at the `firstpoint` using prim's algorithm. `seed` is used to randomly choose which point to consider next and the `cost_prim_attrib` is the float prim attribute that represents the cost of an edge.

The function sets an `active` attribute on the prims that are part of the tree to `1`, and `0`to those that aren't.

# Quality of Life

## Constructors

Constructors for vectors have been created, to avoid using the highly overloaded set which confuses the compiler when data type isn't obvious 🤦 :

```cpp
//vector2
vector2 vector2(float a)
vector2 vector2(float a,float b)

//vector
vector vector(float a)
vector vector(float a, float b, float c)
vector vector(float a, vector2 b)
vector vector(vector2 a, float b)

//vector4
vector4 vector4(float a)
vector4 vector4(float a,float b, float c, float d)
vector4 vector4(vector2 a, float b, float c)
vector4 vector4(float a, vector2 b, float c)
vector4 vector4(float a, float b, vector2 c)
vector4 vector4(vector2 a, vector2 b)
vector4 vector4(vector a, float b)
vector4 vector4(float a, vector b)
```

## Constants

Some needlessly long constants even for 64bit floats

```cpp
#define PI 3.141592653589793238462643383279
#define PI_2 1.570796326794896619231321691640
#define PI_3 1.047197551196597746154214461093
#define PI_4 0.785398163397448309615660845820
#define PI_5 0.628318530717958647692528676656
#define PI_6 0.523598775598298873077107230547
#define PI_7 0.448798950512827605494663340469
#define PI_8 0.392699081698724154807830422910
#define PI_9 0.349065850398865915384738153698
#define PI_10 0.314159265358979323846264338328
#define TAU 6.283185307179586476925286766559
```