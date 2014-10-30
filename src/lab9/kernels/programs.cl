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
    int i = get_global_id(0);

    if (i < n) {
        float yi = b[i];
        for (int j = 0; j < m; j++) {
            yi += A[j + i * m] * x[j];
        }
        y[i] = yi;
    }
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
    int i = get_group_id(0);
    int j = get_local_id(0);

    Q[j] = A[i * M + j] * x[j];

    for (int stride = M / 2; stride > 0; stride /= 2) {
        barrier(CLK_LOCAL_MEM_FENCE);

        if (j + stride < M) {
            Q[j] += Q[j + stride];
        }
    }

    if (j == 0) {
        y[i] = Q[0] + b[i];
    }
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
    int t = get_local_id(0) / Z;
    int z = get_local_id(0) % Z;

    for (int i = t; i < n; i += T) {
        Q[t * Z + z] = 0;
        for (int j = z; j < m; j += Z) {
            Q[t * Z + z] += A[j + i * m] * x[j];
        }

        for (int stride = Z / 2; stride > 0; stride /= 2) {
            barrier(CLK_LOCAL_MEM_FENCE);
            if (z + stride < Z) {
                Q[t * Z + z] += Q[t * Z + z + stride];
            }
        }

        if (z == 0) {
            y[i] = Q[t * Z + 0] + b[i];
        }
    }
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
    int id = get_local_id(0);

    for (int ma = 0; ma < m; ma++) {
        float pivot = A[ma + ma * n];
        float coeff = A[ma + id * n] / pivot;

        barrier(CLK_GLOBAL_MEM_FENCE);

        if (id != ma) {
            for (int na = 0; na < n; na++) {
                A[na + id * n] = A[na + id * n] - coeff * A[na + n * ma];
            }
        }

        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    float coeff = A[id + id * n];
    for (int na = 0; na < n; na++) {
        A[na + id * n] = A[na +  id * n] / coeff;
    }
}
