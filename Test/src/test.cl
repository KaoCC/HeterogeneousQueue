


__kernel void add(__global int* arrayA) {


    int gid = get_global_id(0);

    arrayA[gid] += 1;


}