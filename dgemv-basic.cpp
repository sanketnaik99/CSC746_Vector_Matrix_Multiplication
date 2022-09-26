/*
* Name: Sanket Sanjay Naik
* Date: 09/25/2022
* Course: CSC 746
* Assignment: HW3
* SFSU ID: 922245139
*/

const char* dgemv_desc = "Basic implementation of matrix-vector multiply.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
void my_dgemv(int n, double* A, double* x, double* y) {
   // insert your code here: implementation of basic matrix multiply
   
   // Iterate over all rows of the n*n matrix
   for (int i = 0; i < n; i++){
      // Iterate over all columns of the n*n matrix
      for (int j = 0; j < n; j++){
         // Perform dgemv operation
         y[i] += A[ (i*n) + j ] * x[j];
      }
   }
}
