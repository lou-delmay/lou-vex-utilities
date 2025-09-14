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

void octree_build(int octree[]; int parent_octree[]; int maxdepth)
{
    resize(octree,0);
    resize(parent_octree,0);
    for(int i = 0; i < 8; i++)
    {
        append(octree,-1);
        append(parent_octree,-1);
    }
    int np = npoints(0);
    int max_depth = 0;
    vector bboxmin, bboxmax;
    getbbox(0,bboxmin,bboxmax);
    vector bboxcenter = (bboxmin+bboxmax)/2.0;
    vector lowbbox = bboxcenter-max(bboxmax-bboxmin)*.5;
    vector highbbox = bboxcenter+max(bboxmax-bboxmin)*.5;
    for(int i = 0; i < np; i++)
    {
        vector pos = point(0,"P",i);
        int current = 0;
        int current_depth = 0;
        vector low = lowbbox;
        vector high = highbbox;
        while(1)
        {
            int target=0;
            vector mid = (low+high)/2.0;
            if(pos.x>mid.x) {target+=1;low.x=mid.x;}
            else {high.x=mid.x;}
            if(pos.y>mid.y) {target+=2;low.y=mid.y;}
            else {high.y=mid.y;}
            if(pos.z>mid.z) {target+=4;low.z=mid.z;}
            else {high.z=mid.z;}
            int cellcontent = octree[current+target];
            if(cellcontent<-1)
            {
                //IF BRANCH KEEPS GOING CONTINUE TO DESCEND
                current = -cellcontent;
                current_depth++;
                max_depth=max(max_depth,current_depth);
            }
            else if(cellcontent==-1)
            {
                //IF NEITHER POINT NOR FURTHER BRANCH WRITE POINT NUMBER TO LEAF
                octree[current+target] = i;
                break;
            }
            else
            {
                //IF A POINT IS ALREADY IN THE LEAF, BRANCH THE LEAF
                vector first_pos = point(0,"P",cellcontent);
                octree[current+target] = -len(octree);
                int newleaf[];
                int newparentleaf[];
                for(int l = 0; l < 8; l++)
                {
                    append(newleaf,-1);
                    append(newparentleaf,current+target);
                }
                mid = (low+high)/2.0;
                target=0;
                if(first_pos.x>mid.x) {target+=1;}
                if(first_pos.y>mid.y) {target+=2;}
                if(first_pos.z>mid.z) {target+=4;}
                int newtarget=0;
                if(pos.x>mid.x) {newtarget+=1;}
                if(pos.y>mid.y) {newtarget+=2;}
                if(pos.z>mid.z) {newtarget+=4;}
                if(newtarget!=target)
                {
                    //PUT BOTH POINTS IN THE LEAF AND ADD LEAD TO THE BRANCH
                    newleaf[target]=cellcontent;
                    newleaf[newtarget]=i;
                    append(octree,newleaf);
                    append(parent_octree,newparentleaf);
                    break;
                }
                else
                {
                    //IF BOTH POINTS ARE STILL IN THE SAME CELL KEEP GOING DOWN
                    newleaf[target]=cellcontent;
                    current=len(octree);
                    current_depth++;
                    max_depth=max(max_depth,current_depth);
                    append(octree,newleaf);
                    append(parent_octree,newparentleaf);
                }
            }
        }
    }
    maxdepth = max_depth;
    return;
}

void octree_build(int octree[])
{
    resize(octree,0);
    for(int i = 0; i < 8; i++)
    {
        append(octree,-1);
    }
    int np = npoints(0);
    vector bboxmin, bboxmax;
    getbbox(0,bboxmin,bboxmax);
    vector bboxcenter = (bboxmin+bboxmax)/2.0;
    vector lowbbox = bboxcenter-max(bboxmax-bboxmin)*.5;
    vector highbbox = bboxcenter+max(bboxmax-bboxmin)*.5;
    for(int i = 0; i < np; i++)
    {
        vector pos = point(0,"P",i);
        int current = 0;
        vector low = lowbbox;
        vector high = highbbox;
        while(1)
        {
            int target=0;
            vector mid = (low+high)/2.0;
            if(pos.x>mid.x) {target+=1;low.x=mid.x;}
            else {high.x=mid.x;}
            if(pos.y>mid.y) {target+=2;low.y=mid.y;}
            else {high.y=mid.y;}
            if(pos.z>mid.z) {target+=4;low.z=mid.z;}
            else {high.z=mid.z;}
            int cellcontent = octree[current+target];
            if(cellcontent<-1)
            {
                //IF BRANCH KEEPS GOING CONTINUE TO DESCEND
                current = -cellcontent;
            }
            else if(cellcontent==-1)
            {
                //IF NEITHER POINT NOR FURTHER BRANCH WRITE POINT NUMBER TO LEAF
                octree[current+target] = i;
                break;
            }
            else
            {
                //IF A POINT IS ALREADY IN THE LEAF, BRANCH THE LEAF
                vector first_pos = point(0,"P",cellcontent);
                octree[current+target] = -len(octree);
                int newleaf[];
                for(int l = 0; l < 8; l++)
                {
                    append(newleaf,-1);
                }
                mid = (low+high)/2.0;
                target=0;
                if(first_pos.x>mid.x) {target+=1;}
                if(first_pos.y>mid.y) {target+=2;}
                if(first_pos.z>mid.z) {target+=4;}
                int newtarget=0;
                if(pos.x>mid.x) {newtarget+=1;}
                if(pos.y>mid.y) {newtarget+=2;}
                if(pos.z>mid.z) {newtarget+=4;}
                if(newtarget!=target)
                {
                    //PUT BOTH POINTS IN THE LEAF AND ADD LEAD TO THE BRANCH
                    newleaf[target]=cellcontent;
                    newleaf[newtarget]=i;
                    append(octree,newleaf);
                    break;
                }
                else
                {
                    //IF BOTH POINTS ARE STILL IN THE SAME CELL KEEP GOING DOWN
                    newleaf[target]=cellcontent;
                    current=len(octree);
                    append(octree,newleaf);
                }
            }
        }
    }
    return;
}

void octree_visualize(int octree[])
{
    int saved_current[];
    int saved_target[];
    vector saved_low[];
    vector saved_high[];
    int current = 0;
    int target = 0;
    vector low=set(0.0,0.0,0.0);
    vector high=set(1.0,1.0,1.0);
    while(true)
    {
        int cellcontent = octree[current+target];
        vector mid = (low+high)/2.0;
        vector templow = low;
        vector temphigh = high;
        if(target&1){templow.x=mid.x;}else{temphigh.x=mid.x;};
        if(target&2){templow.y=mid.y;}else{temphigh.y=mid.y;};
        if(target&4){templow.z=mid.z;}else{temphigh.z=mid.z;};
        if(cellcontent>=-1)
        {
            if(cellcontent!=-1)
            {
                //probably best to do nothing here idk
            }
            if(target==7)
            {
                while(true)
                {
                    if(len(saved_current)==0){return;}
                    current=pop(saved_current);
                    target=pop(saved_target);
                    low=pop(saved_low);
                    high=pop(saved_high);
                    if(target!=7){target++;break;}
                }
            }
            else
            {
                target++;
            }
        }
        else
        {
            append(saved_current,current);
            append(saved_target,target);
            append(saved_low,low);
            append(saved_high,high);
            current=-cellcontent;
            target=0;
            low=templow;
            high=temphigh;
            vector col = hsvtorgb(len(saved_current)*.115,0.8,1.0);
            int a = addpoint(0,set(low.x,low.y,low.z));
            int b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,low.z));
            b = addpoint(0,set(low.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,low.z));
            b = addpoint(0,set(low.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(low.x,high.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(high.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(high.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,low.z));
            b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,low.y,high.z));
            b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,high.y,high.z));
            b = addpoint(0,set(low.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,high.y,low.z));
            b = addpoint(0,set(high.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,high.z));
            b = addpoint(0,set(low.x,high.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,high.z));
            b = addpoint(0,set(high.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
        }
    }
    return;
}

void octree_visualize(int octree[]; vector bbox_min; vector bbox_max)
{
    int saved_current[];
    int saved_target[];
    vector saved_low[];
    vector saved_high[];
    int current = 0;
    int target = 0;
    vector bboxcenter = (bbox_min+bbox_max)/2.0;
    vector lowbbox = bboxcenter-max(bbox_max-bbox_min)*.5;
    vector highbbox = bboxcenter+max(bbox_max-bbox_min)*.5;
    vector low=lowbbox;
    vector high=highbbox;
    while(true)
    {
        int cellcontent = octree[current+target];
        vector mid = (low+high)/2.0;
        vector templow = low;
        vector temphigh = high;
        if(target&1){templow.x=mid.x;}else{temphigh.x=mid.x;};
        if(target&2){templow.y=mid.y;}else{temphigh.y=mid.y;};
        if(target&4){templow.z=mid.z;}else{temphigh.z=mid.z;};
        if(cellcontent>=-1)
        {
            if(cellcontent!=-1)
            {
                //probably best to do nothing here idk
            }
            if(target==7)
            {
                while(true)
                {
                    if(len(saved_current)==0){return;}
                    current=pop(saved_current);
                    target=pop(saved_target);
                    low=pop(saved_low);
                    high=pop(saved_high);
                    if(target!=7){target++;break;}
                }
            }
            else
            {
                target++;
            }
        }
        else
        {
            append(saved_current,current);
            append(saved_target,target);
            append(saved_low,low);
            append(saved_high,high);
            current=-cellcontent;
            target=0;
            low=templow;
            high=temphigh;
            vector col = hsvtorgb(len(saved_current)*.115,0.8,1.0);
            int a = addpoint(0,set(low.x,low.y,low.z));
            int b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,low.z));
            b = addpoint(0,set(low.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,low.z));
            b = addpoint(0,set(low.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(low.x,high.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(high.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,high.z));
            b = addpoint(0,set(high.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,high.y,low.z));
            b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(high.x,low.y,high.z));
            b = addpoint(0,set(high.x,low.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,high.y,high.z));
            b = addpoint(0,set(low.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,high.y,low.z));
            b = addpoint(0,set(high.x,high.y,low.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,high.z));
            b = addpoint(0,set(low.x,high.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
            a = addpoint(0,set(low.x,low.y,high.z));
            b = addpoint(0,set(high.x,low.y,high.z));
            setprimattrib(0,"Cd",addprim(0,"polyline",a,b),col);
        }
    }
    return;
}

void robert_prim_mst(int firstpoint; int seed; string cost_prim_attrib)
{
    setpointgroup(0,"prim_mst_start",firstpoint,1);
    int inforest[];
    resize(inforest,npoints(0));
    inforest[firstpoint]=1;
    int points_to_treat[] = neighbours(0,firstpoint);

    for(int i = 0; i < npoints(0)-1; i++)
    {
        //pick a random point from list
        int ptinlist = sample_discrete(len(points_to_treat),rand(seed,i));
        //construct a list of neighbours that are in the forest
        int allpaths[] = pointprims(0,points_to_treat[ptinlist]);
        int posssible_paths[];
        foreach(int path; allpaths)
        {
            int pts[] = primpoints(0,path);
            if(inforest[pts[0]]==1 || inforest[pts[1]]==1)
            {
                append(posssible_paths,path);
            }
        }
        //find path with lower cost
        float lowest_cost = 1e12;
        int lowest_cost_path = len(posssible_paths);
        foreach(int path; posssible_paths)
        {
            float cost = prim(0,cost_prim_attrib,path);
            if(cost<lowest_cost)
            {
                lowest_cost=cost;
                lowest_cost_path=path;
            }
        }
        //Add current point to the forest
        inforest[points_to_treat[ptinlist]]=1;
        int to_append_to_be_treated[];
        //Construct a list of neighbours that are not in the forest or already in the list to be treated
        foreach(int nei; neighbours(0,points_to_treat[ptinlist]))
        {
            if(! (inforest[nei]==1 || find(points_to_treat,nei)>-1))
            {
                append(to_append_to_be_treated,nei);
            }
        }
        //Remove the current point from the list to be treated
        removeindex(points_to_treat,ptinlist);
        //Add all neighbours not in the forest to to be treated
        append(points_to_treat,to_append_to_be_treated);
        //Set the path as active
        setprimattrib(0,"active",lowest_cost_path,1);
    }
}

void build_position_mass_octree(int octree[]; vector pos_octree[]; float mass_octree[])
{
    for(int i = 0; i < len(octree); i++)
    {
        append(mass_octree,0.0);
        append(pos_octree,set(0.0,0.0,0.0));
    }
    for(int i = 0; i < len(octree); i++)
    {
        int cellcontent = octree[len(octree)-1-i];
        if(cellcontent>-1)
        {
            mass_octree[len(octree)-1-i] = point(0,"mass",cellcontent);
            pos_octree[len(octree)-1-i]  = point(0,"P",cellcontent);
        }
        if(cellcontent<-1)
        {
            for(int j = 0; j < 8; j++)
            {
                mass_octree[len(octree)-1-i] += mass_octree[-cellcontent+j];
                pos_octree[len(octree)-1-i] += mass_octree[-cellcontent+j]*pos_octree[-cellcontent+j];
            }
            pos_octree[len(octree)-1-i]/=mass_octree[len(octree)-1-i];
        }
    }
    return;
}

#endif