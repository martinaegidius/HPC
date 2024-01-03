#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <cblas.h>

// allocate a double-prec m x n matrix
double **dmalloc_2d(int m, int n) {
    if (m <= 0 || n <= 0) return NULL;
    double **A = malloc(m * sizeof(double *));
    if (A == NULL) return NULL;
    A[0] = malloc(m*n*sizeof(double));
    if (A[0] == NULL) {
        free(A);
        return NULL;
    }
    for (int i = 1; i < m; i++)
        A[i] = A[0] + i * n;
    return A;
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double ** randomMatrix(const int m, const int n){
    double ** A_tmp = dmalloc_2d(m,n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            A_tmp[i][j] = randfrom(-11.0,11.0);
        }
    }
    return A_tmp;
}

double * randomVector(const int m){
    double * A_tmp = malloc(m * sizeof(double));
    for(int i=0;i<m;i++){
        A_tmp[i] = randfrom(-11.0,11.0);
    }
    return A_tmp;
}

void dfree_2d(double **A) {
    free(A[0]);
    free(A);
}

typedef struct Matrix2d_t{
    int rows;
    int cols; 
    double ** val;
} Matrix2d_t;

void dfree_Matrix2d(struct Matrix2d_t * M){
    dfree_2d(M->val);
    free(M);
}

struct Matrix2d_t * empty_matrix2d(const int m, const int n){
    double ** A_tmp = dmalloc_2d(m,n); 
    struct Matrix2d_t *M = malloc(sizeof *M);
    M->rows = m; 
    M->cols = n;
    M->val = A_tmp;
    return M;
}

struct Matrix2d_t * matrix2d(const int m, const int n){
    //double ** A_tmp = dmalloc_2d(m,n);
    double ** A_tmp = randomMatrix(m,n); 
    //M->val = dmalloc_2d(m,n);
    struct Matrix2d_t *M = malloc(sizeof *M);
    M->rows = m; 
    M->cols = n;
    M->val = A_tmp;
    return M;
}

void printMatrix(struct Matrix2d_t * M){
    printf("\n");
    for(int i=0;i<M->rows;i++){
        for(int j=0;j<M->cols;j++){
            printf("%2.2f",M->val[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    return;
}

struct Matrix2d_t * matrixAdd(struct Matrix2d_t * A, struct Matrix2d_t * B){
    struct Matrix2d_t * C = empty_matrix2d(A->rows,A->cols);
    if(A->rows!=B->rows || A->cols!=B->cols){
        printf("Mismatching shapes of matrices...");
        C->rows = 0;
        C->cols = 0;
        C->val = NULL;
        return C;
    }
    for(int i=0;i<A->rows;i++){
        for(int j=0;j<A->cols;j++){
            C->val[i][j] = A->val[i][j] + B->val[i][j];
        }
    }
    return C;
}

struct Matrix2d_t * matmul(struct Matrix2d_t * A, struct Matrix2d_t * B){
    struct Matrix2d_t * C = empty_matrix2d(A->rows,B->cols);
    if(A->cols!=B->rows){
        printf("Mismatching shapes of matrices...");
        C->rows = 0;
        C->cols = 0;
        C->val = NULL;
        return C;
    }
    double seqsum;
    //printf("\n shapes %d %d %d %d \n",A->rows, A->cols, B->rows, B->cols);
    for(int i=0;i<A->rows;i++){ //loop through i'th row of A
        for(int j=0;j<B->cols;j++){ //loop through j'th column of B
            seqsum = 0.0;
            //printf("\n i,j = %d,%d \n",i,j);
            for(int k=0;k<A->cols;k++){ //column idx of A, row idx of B
                //printf("\n k = %d \n",k);
                seqsum += A->val[i][k] * B->val[k][j];
            }
            C->val[i][j] = seqsum;
        }
    }
    return C;
}


typedef struct Vector2d_t{
    int n;
    double * val;
} Vector2d_t;

struct Vector2d_t * vector(const int n){
    double *V = randomVector(n);
    struct Vector2d_t * Vec = malloc(sizeof *Vec);
    Vec->n = n;
    Vec->val = V;
    return Vec;
}

void freeVector(struct Vector2d_t * v){
    free(v->val);
    free(v);
}

void printVector(struct Vector2d_t * V){
    printf("\n");
    for(int i=0;i<V->n;i++){
        printf("%2.2f",V->val[i]);
        if(i<V->n-1){
            printf(" , ");
        }
        else{printf("\n");}
    }
    return;
}

struct Vector2d_t * matmulV(struct Matrix2d_t * A, struct Vector2d_t * b){
    struct Vector2d_t * c = vector(A->rows);
    for(int m=0;m<A->rows;m++){
        double seqsum = 0.0;
        for (int n=0;n<A->cols;n++){
            seqsum += A->val[m][n]*b->val[n];
        }
        c->val[m] = seqsum;
    }
    return c;
}





void experiment(int num_exp, int maxVal){
    int increment = maxVal/num_exp;
    printf("Registered %d experiments with start-size %d to end-size %d",num_exp,increment,maxVal);
    clock_t start_t, end_t;
    struct Matrix2d_t * A, * B, * C;
    double time;
    FILE *file = fopen("additionResults.txt","a");
    if(file==NULL){
        printf("Error opening file. Aborted.");
        return;
    }
    for(int i=increment;i<=maxVal;i+= increment){
        printf("\n Running experiment %d \n",i);
        A = matrix2d(i,i);
        B = matrix2d(i,i);    
        start_t = clock();   
        for(int k=0;k<i/40;k++){
            C = matrixAdd(A,B);
            dfree_Matrix2d(C);
        }
        end_t = clock();    
        time = (double)(end_t-start_t)/CLOCKS_PER_SEC;
        time /= i/50;
        fprintf(file,"%d %f \n",i,time);
        dfree_Matrix2d(A);
        dfree_Matrix2d(B);
    }  
    fclose(file);
    printf("\n Finished addition experiment \n");
    return; 
}

int main(){
    //experiment(10,40000);
    struct Matrix2d_t * A, * B, * C, *D;
    int m = 3;
    int n = 2;
    A = matrix2d(m,n);
    B = matrix2d(m,n);
    printf("A is: ");
    printf("\n");
    printMatrix(A);
    printf("B is: ");
    printf("\n");
    printMatrix(B);
    C = matrixAdd(A,B);
    printf("C is: ");
    printf("\n");
    printMatrix(C);

    dfree_Matrix2d(A);
    dfree_Matrix2d(B);
    dfree_Matrix2d(C);
    

    A = matrix2d(m,n);
    B = matrix2d(n,m);
    printMatrix(A);
    printMatrix(B);
    D = matmul(A,B);


    printf("D is: ");
    printf("\n");
    printMatrix(D);

    //try doing the same thing with cblas 
    int k = A->cols; //leading dimension
    int alpha = 1;
    int beta = 0;
    DCBLAS = cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
    m, n, k, alpha, A->val, k, B->val, beta, D2->val, k); //need to init matrices as a 1d array as in https://www.intel.com/content/www/us/en/docs/onemkl/tutorial-c/2021-4/multiplying-matrices-using-dgemm.html
    
    
    return 0;
    
    
    // struct Vector2d_t * b, * c;
    // struct Matrix2d_t * A;
    // b = vector(3);
    // printVector(b);
    // A = matrix2d(2,3);
    // printMatrix(A);
    // c = matmulV(A,b);
    // printVector(c);

}