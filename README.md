# lou-vex-utilities

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

Converts Spherical to Cartesian corrdinates, duh !

## cartesian_to_spherical

```cpp
vector cartesian_to_spherical(vector)
vector cartesian_to_spherical(float, float, float)
```

Converts Cartesian to Spherical corrdinates, duh !

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

The function sets and `active` attribute on the prims that are part of the tree to `1`, and the `0`to those that aren't.