#ifndef _lou_
#define _lou_

#undef PI
#define PI 3.141592653589793238462643383279
#define TAU 6.283185307179586476925286766559

int[] range(int x)
{
    int list[];
    for(int i = 0; i < x; i++)
    {
        append(list,i);
    }
    return list;
}

int[] range(int a; int b)
{
    int list[];
    for(int i = min(a,b); i < max(a,b); i++)
    {
        append(list,i);
    }
    return list;
}

#define BUILD_SWAP_ELEMENTS(type)\
    function void swap_elements(type list[]; int a; int b) \
    { \
        type temp = list[a]; \
        list[a] = list[b]; \
        list[b] = temp; \
    } \
//build swap elements
BUILD_SWAP_ELEMENTS(int)
BUILD_SWAP_ELEMENTS(float)
BUILD_SWAP_ELEMENTS(vector2)
BUILD_SWAP_ELEMENTS(vector)
BUILD_SWAP_ELEMENTS(vector4)
BUILD_SWAP_ELEMENTS(string)
BUILD_SWAP_ELEMENTS(matrix)
BUILD_SWAP_ELEMENTS(matrix3)

#define BUILD_FISHER_YATER(type)\
    type[] fisher_yates(type list[]; int seed)\
    {\
        type listr[] = list;\
        for(int i = 0; i < len(listr); i++)\
        {\
            swap_elements(listr,i,sample_discrete(len(listr),rand(seed,i)));\
        }\
        return listr;\
    }\
//build fisher yates
BUILD_FISHER_YATER(int)
BUILD_FISHER_YATER(float)
BUILD_FISHER_YATER(vector2)
BUILD_FISHER_YATER(vector)
BUILD_FISHER_YATER(vector4)
BUILD_FISHER_YATER(string)
BUILD_FISHER_YATER(matrix)
BUILD_FISHER_YATER(matrix3)

vector spherical_to_cartesian(vector sphere)
{
    vector cart = set(0.0,0.0,0.0);
    cart.x = sphere.x*sin(sphere.y)*cos(sphere.z);
    cart.y = sphere.x*cos(sphere.y);
    cart.z = sphere.x*sin(sphere.y)*sin(sphere.z);
    return cart;
}
vector spherical_to_cartesian(float sphere_x; float sphere_y; float sphere_z)
{
    vector cart = set(0.0,0.0,0.0);
    cart.x = sphere_x*sin(sphere_y)*cos(sphere_z);
    cart.y = sphere_x*cos(sphere_y);
    cart.z = sphere_x*sin(sphere_y)*sin(sphere_z);
    return cart;
}

vector cartesian_to_spherical(vector cart)
{
    vector sphere = set(0.0,0.0,0.0);
    sphere.x = length(cart);
    sphere.y = atan2(length(set(cart.x,cart.z)),cart.y);
    sphere.z = atan2(cart.z,cart.x);
    return sphere;
}
vector cartesian_to_spherical(float cart_x; float cart_y; float cart_z)
{
    vector sphere = set(0.0,0.0,0.0);
    sphere.x = length(set(cart_x,cart_y,cart_z));
    sphere.y = atan2(length(set(cart_x,cart_z)),cart_y);
    sphere.z = atan2(cart_z,cart_x);
    return sphere;
}

#endif