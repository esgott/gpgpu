// TODO
//
// i := get_global_id(0)
//
// IF ID < n THEN:
//   yi := b[i]
//   LOOP j := 0 .. m DO:
//     yi += A[j + i * m] * x[j]
//   END LOOP
//   y[i] := yi
// END IF
__kernel
void simpleMV(const int n, const int m, __global float* y, __global float* A, __global float* x, __global float* b) {

}

// TODO
//
// i = get_group_id(0)
// j = get_local_id(0)
//
// Q[j] := A[i * M + j] * x[j]
// BARRIER
//
// Sum scan on Q (reduction)
//
// IF j = 0 THEN:
//   y[i] = Q[0] + b[i]
//
__kernel
void reduceMV(const int n, __global float* y, __global float* A, __global float* x, __global float* b, const int M, __local float* Q) {

}

// TODO
//
// t := get_local_id(0) / Z
// z := get_local_id(0) % Z
//
// FOR i := t ; i < n ; i := i + T :
//   Q[t * Z + z] = 0
//   FOR j := z ; j < m ; j += Z :
//     Q[t * Z + z] += A[j + i * m] * x[j]
//   END FOR
// END FOR
//
// Sum scan on Q (reduction)
//
// IF z = 0 THEN:
//   y[i] = Q[t * Z + 0] + b[i]
//
__kernel
void largeMV(const int n, const int m, __global float* y, __global float* A, __global float* x, __global float* b, const int T, const int Z, __local float* Q) {

}

// TODO
//
// ID := get_local_id(0)
//
// LOOP ma := 0 .. m DO:
//   pivot := A[ma + ma * n]
//   coeff := A[ma + ID * n] / pivot
//   BARRIER
//   IF ID != ma DO:
//     LOOP na := 0 .. n DO:
//       A[na + id * n] := A[na + id * n] - coeff * A[na + n * ma];
//   ENDIF
//   BARRIER
// END LOOP
//
// coeff := A[ID + ID * n]
// LOOP na := 0 .. n DO:
//   A[na + id * n] = A[na + id * n] / coeff

__kernel void gaussian(const int n, const int m, __global float* A) {

}
