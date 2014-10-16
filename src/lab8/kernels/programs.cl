// TODO
//
// ID := get_global_id(0)
// data[ID] := square(data[ID])
__kernel
void map(__global float* data) {

}

// TODO
//
// histogram[data[id]] := histogram[data[id]] + 1
//
// SYNCHRONIZATION!
__kernel
void histogram_global(__global int* data, __global int* histogram) {

}

// TODO
//
// ID  := get_global_id(0)
// LID := get_local_id(0)
//
// IF LID < histogramSize DO:
//  lhistogram[LID] := 0
// BARRIER
//
// Add data to local histogram
//
// BARRIER
//
// IF LID < histogramSize DO:
//  histogram[LID] = lhistogram[LID]
__kernel
void histogram_local(__global int* data, __global int* histogram, __local int* lhistogram, const int histogramSize) {

}

// TODO
//
// ID := get_global_id(0)
//
// FOR s = get_global_size(0) / 2 ; s > 0 ; s >>= 1 DO:
//  IF (ID < s)
//    data[ID] = max(data[ID], data[ID + s])
//  BARRIER
//
__kernel
void reduce_global(__global float* data) {

}

// TODO
//
// ID := get_global_id(0)
// IF ID > 0 THEN data[ID] = data[ID - 1]
//           ELSE data[ID] = 0
// BARRIER
//
// FOR s = 1; s < get_global_size(0); s *= 2 DO:
//   tmp := data[ID]
//   IF ( ID + s < get_global_size(0) THEN
//     data[ID + s] += tmp;
//   BARRIER
//
// IF(ID = 0) THEN data[ID] = 0;
__kernel
void exscan_global(__global int* data) {

}

// TODO
// ID := get_global_id(0)
// IF data[id] < 50 THEN
//   predicate = 1
// ELSE
//   predicate = 0
__kernel
void compact_predicate(__global int* data, __global int* pred) {

}

// TODO
//
// exclusive scan pred to prefSum
__kernel
void compact_exscan(__global int* pred, __global int* prefSum) {

}

// TODO
//
// ID := get_global_id(0)
// VALUE := data[ID]
// BARRIER
// IF pred[ID] == 1 THEN
//  data[prefSum[ID]] = VALUE
__kernel
void compact_compact(__global int* data, __global int* pred, __global int* prefSum) {

}
