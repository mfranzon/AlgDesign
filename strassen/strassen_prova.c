#include <stdlib.h>

#include "matrix.h"
#include <stdbool.h>



void sum_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n);


void sub_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n);


void naive_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n);


void strassen_aux_prova(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n)


{
  if (n < (1<<6)) {
    naive_aux(C, C_f_row, C_f_col,
              A, A_f_row, A_f_col,
              B, B_f_row, B_f_col,
              n);
    return;
  }

  const size_t n2=n/2;


  const size_t C1X = C_f_row;
  const size_t C2X = C_f_row + n2;
  const size_t CX1 = C_f_col;
  const size_t CX2 = C_f_col + n2;

  const size_t A1X = A_f_row;
  const size_t A2X = A_f_row + n2;
  const size_t AX1 = A_f_col;
  const size_t AX2 = A_f_col + n2;

  const size_t B1X = B_f_row;
  const size_t B2X = B_f_row + n2;
  const size_t BX1 = B_f_col;
  const size_t BX2 = B_f_col + n2;


  float ***D=(float ***)malloc(sizeof(float **)*4);
        for (int i=0; i<4; i++) {
              D[i] = allocate_matrix(n2, n2);
            }
  //rephrase the alghoritm in order to avoid memory consuming


  sub_matrix_blocks(C, C2X, CX2, //S7
                    A,A1X,AX2,
                    A,A2X,AX2,
                    n2);

  sum_matrix_blocks(C, C1X, CX2, //S8
                    B,B2X,BX1,
                    B,B2X,BX2,
                    n2);

  strassen_aux_prova(D[0], 0, 0, //P6
             C, C2X, CX2, //S7
             C, C1X, CX2, //S8
             n2);


  sum_matrix_blocks(C, C2X, CX2, //S2
                   A,A1X,AX1,
                   A,A1X,AX2,
                   n2);

  strassen_aux_prova(C, C1X, CX2, //P2
               C, C2X, CX2, //S2
               B, B2X, BX2,
               n2);


  sum_matrix_blocks(C, C2X, CX2, //S5
                    A,A1X,AX1,
                    A,A2X,AX2,
                    n2);


  sum_matrix_blocks(C, C2X, CX1, //S6
                    B,B1X,BX1,
                    B,B2X,BX2,
                    n2);

  strassen_aux_prova(D[1], 0, 0, // P5
                        C, C2X, CX2, //S5
                        C, C2X, CX1, //S6
                        n2);


  sub_matrix_blocks(C, C2X, CX2, //S4
                    B,B2X,BX1,
                    B,B1X,BX1,
                    n2);

  strassen_aux_prova(D[2], 0, 0, // P4 //M2XMX1
               A, A2X, AX2,
               C, C2X, CX2, //S4
               n2);

  sum_matrix_blocks(C, C1X, CX1,
              D[1], 0, 0, //P5
              D[2], 0, 0, //P4
              n2);

  sub_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  C, C1X, CX2, //P2
                  n2);

  sum_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  D[0], 0, 0, //P6
                  n2);




  sub_matrix_blocks(C, C2X, CX1, //S1
                  B, B1X,BX2,
                  B, B2X,BX2,
                  n2);

  strassen_aux_prova(C, C2X, CX2, //P1
             A, A1X, AX1,
             C, C2X, CX1, //S1
             n2);


      sum_matrix_blocks(C, C1X, CX2,
                        C, C2X, CX2, //P1
                        C, C1X, CX2, //P2
                        n2);



  sum_matrix_blocks(C, C2X, CX1, //S3
                     A, A2X, AX1,
                     A, A2X, AX2,
                     n2);

   strassen_aux_prova(D[0], 0, 0, //P3
              C, C2X, CX1, //S3
              B, B1X, BX1,
              n2);


       sum_matrix_blocks(C, C2X, CX1,
                         D[0], 0, 0, //P3
                         D[2], 0, 0, //P4
                         n2);



  // P1 + P5
  sum_matrix_blocks(C, C2X, CX2,
                  C, C2X, CX2, //P1
                  D[1], 0, 0, //P5
                  n2);

  // (P5 + P1) - P3
  sub_matrix_blocks(C, C2X, CX2,
                  C, C2X, CX2,
                  D[0], 0, 0, //P3
                  n2);

  
  sub_matrix_blocks( D[0], 0, 0, //S9
                    A,A1X,AX1,
                    A,A2X,AX1,
                    n2);

   sum_matrix_blocks( D[1], 0, 0, //S10
                    B,B1X,BX1,
                    B,B1X,BX2,
                    n2);

   strassen_aux_prova(D[2], 0, 0, //P7
              D[0], 0, 0, //S9
              D[1], 0, 0, //S10
              n2);

  // ((P5 + P1) - P3) - P7
  sub_matrix_blocks(C, C2X, CX2,
                  C, C2X, CX2,
                  D[2], 0, 0, //P7
                  n2);




/*
  // S1 = B12 - B22
  sub_matrix_blocks(C, C2X, CX1,
                    B,B1X,BX2,
                    B,B2X,BX2,
                    n2);

  // P1 = A11 x S1
  strassen_aux_prova(D[2],0,0,
               A,A1X,AX1,
               C, C2X, CX1,
               n2);

  // C12 = P1
  sum_matrix_blocks(C, C1X, CX2,
                    C, C1X, CX2,
                    D[2],0,0,
                    n2);

  // C22 = P1
  sum_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    D[2],0,0,
                    n2);


  // S2 = A11 + A12
  sum_matrix_blocks(C, C2X, CX1,
                    A,A1X,AX1,
                    A,A1X,AX2,
                    n2);

// P2 = S2 x B22
strassen_aux_prova(D[0], 0, 0,
             C, C2X, CX1,
             B, B2X, BX2,
             n2);

//C11-P2
sub_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  D[0], 0, 0,
                  n2);

//C12 + P2
sub_matrix_blocks(C, C1X, CX2,
                  C, C1X, CX2,
                  D[0], 0, 0,
                  n2);

// S3 = A21 + A22
sum_matrix_blocks(C, C2X, CX1,
                  A,A2X,AX1,
                  A,A2X,AX2,
                  n2);

// P3 = S3 x B11
  strassen_aux_prova(D[1], 0, 0,
               C, C2X, CX1,
               B, B1X, BX1,
              n2);

// S4 = B21 - B11
  sub_matrix_blocks(C, C2X, CX1,
                    B,B2X,BX1,
                    B,B1X,BX1,
                    n2);

// P4 = A22 x S4
  strassen_aux_prova(D[3], 0, 0,
               A, A2X, AX2,
               C, C2X, CX1,
               n2);

//C21= P3 + P4
sum_matrix_blocks(C, C2X, CX1,
                  D[1], 0, 0,
                  D[3], 0, 0,
                  n2);


//C22+P3
sub_matrix_blocks(C, C2X, CX2,
                  C, C2X, CX2,
                  D[1], 0, 0,
                  n2);


//C11+P4
sum_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  D[3], 0, 0,
                  n2);

// S5 = A11 + A22
  sum_matrix_blocks(D[2],0,0,
                    A,A1X,AX1,
                    A,A2X,AX2,
                    n2);

// S6 = B11 + B22
  sum_matrix_blocks(D[0],0,0,
                    B,B1X,BX1,
                    B,B2X,BX2,
                    n2);


// P5 = S5 x S6
  strassen_aux_prova(D[1], 0, 0,
               D[2],0,0,
               D[0],0,0,
               n2);
//C11 + P5
sum_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  D[1], 0, 0,
                  n2);
//C22 + P5
sum_matrix_blocks(C, C2X, CX2,
                  C, C2X, CX2,
                  D[1], 0, 0,
                  n2);


// S7 = A12 - A22
  sub_matrix_blocks(D[3],0,0,
                    A,A1X,AX2,
                    A,A2X,AX2,
                    n2);
// S8 = B21 + B22
  sum_matrix_blocks(D[2],0,0,
                    B,B2X,BX1,
                    B,B2X,BX2,
                    n2);

// P6 = S7 x S8
  strassen_aux_prova(D[0], 0, 0,
               D[3],0,0,
               D[2],0,0,
               n2);


//C11+P6
sum_matrix_blocks(C, C1X, CX1,
                  C, C1X, CX1,
                  D[0], 0, 0,
                  n2);


// S9 = A11 - A21
  sub_matrix_blocks(D[1],0,0,
                    A,A1X,AX1,
                    A,A2X,AX1,
                    n2);

// S10 = B11 + B12
  sum_matrix_blocks(D[3],0,0,
                    B,B1X,BX1,
                    B,B1X,BX2,
                    n2);


// P7 = S9 x S10
  strassen_aux_prova(D[2], 0, 0,
               D[1],0,0,
               D[3],0,0,
               n2);


//C22-P7
sub_matrix_blocks (C, C2X, CX2,
                   C, C2X, CX2,
                   D[2], 0, 0,
                  n2);
*/
        for (int i=0; i<4; i++) {
        deallocate_matrix(D[i], n2);
      }
}

void strassen_prova(float **C,
      float **A, float **B, const size_t n)
{


  strassen_aux_prova(C, 0, 0, A, 0, 0, B, 0, 0, n);


}
