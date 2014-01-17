#include <assert.h>
#include "fixmatrix.h"

#include "fixmatrixadditions.h"

/**
* \brief Tests matrix inversion using Cholesky decomposition
*/
void test_matrix_inverse()
{
    // the original matrix
    mf16 d = { 3, 3, 0, 0 };
    mf16_fill_diagonal(&d, fix16_one);
    d.data[0][1] = F16(0.5);
    d.data[1][0] = F16(0.5);

    // the decomposed and inverted matrix 
    mf16 m = { 3, 3, 0, 0 };
    mf16_fill(&m, 0);

    // decompose matrix to lower triangular
    mf16_cholesky(&m, &d);

    // invert matrix using lower triangular
    mf16_invert_lt(&m, &m);

    // test the result
    fix16_t test = m.data[1][1];
    float testf = fix16_to_float(test);
    assert(testf >= 1.3 && testf <= 1.4);
}

/**
* \brief Tests matrix inversion using Cholesky decomposition
*/
void test_matrix_abat()
{
    // data buffer for the original and decomposed matrix
    mf16 a = { 3, 3, 0 };
    mf16_fill_diagonal(&a, fix16_one);
    a.data[0][1] = F16(0.5);
    a.data[0][2] = F16(0.5);
    a.data[1][0] = F16(0.5);

    // data buffer for the inverted matrix
    mf16 b = { 3, 3, 0 };
    b.data[0][0] = F16(1);
    b.data[0][1] = F16(2);
    b.data[0][2] = F16(3);
    b.data[1][0] = F16(4);
    b.data[1][1] = F16(5);
    b.data[1][2] = F16(6);
    b.data[2][0] = F16(7);
    b.data[2][1] = F16(8);
    b.data[2][2] = F16(9);

    mf16 m = { 3, 3, 0 };
    
    mf16_mul(&b, &a, &b);
    mf16_mul_bt(&m, &b, &a);

    fix16_t test = m.data[0][0];
    float testf = fix16_to_float(test);

    assert(testf == 16);
}

void main() 
{
    test_matrix_inverse();
    test_matrix_abat();
}