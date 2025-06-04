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

vector spherical_to_cartesian(vector sphere)
{
    vector cart = set(0.0,0.0,0.0);
    cart.x = sphere.x*sin(sphere.y)*cos(sphere.z);
    cart.y = sphere.x*cos(sphere.y);
    cart.z = sphere.x*sin(sphere.y)*sin(sphere.z);
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


#endif