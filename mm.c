// Matrix Multiplication


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>


double ** mm_alloc( int xy_size )
{
  //Make a matrix pointer and allocate pointers to it
  double** matrix_ptr=calloc(xy_size,sizeof(double*));
  //Allocate each of those pointers to doubles
  int i;
  for(i=0;i<xy_size;i++)
    {
      matrix_ptr[i]=calloc(xy_size,sizeof(double));
    }
  //return pointer
  return(matrix_ptr);
}

void mm_free( int xy_size, double **matrix  )
{
  int i;
  for(i=0;i<xy_size;i++)
    {
      free(matrix[i]);
    }
  free(matrix);
}

void mm_read( char *filename, int *xy_size, double ***x_matrix, double ***y_matrix) 
{
  //Open the file for reading
  FILE* stream;
  stream=fopen(filename,"r");
  //Make buffer for holding data
  char* line;
  line=(char*)malloc(256);
  //Read the first line, the xy matrix size, and store
  fgets(line,256,stream);
  *xy_size=atoi(line);
  //We now have to allocate the matrices
  *x_matrix=mm_alloc(*xy_size);
  *y_matrix=mm_alloc(*xy_size);
  //Now we put the data in the matrices
  int i;
  int j;
  int entry;
  for(i=0;i<(*xy_size);i++)
    {
      for(j=0;j<(*xy_size);j++)
	{
	  fgets(line,256,stream);
	  //Figuring out this sscanf thing was hard
	  sscanf(line,"%d",&entry);
	  x_matrix[0][i][j]=(double)entry;
	}
    }
  for(i=0;i<(*xy_size);i++)
    {
      for(j=0;j<(*xy_size);j++)
	{
	  fgets(line,256,stream);
	  sscanf(line,"%d",&entry);
	  y_matrix[0][i][j]=(double)entry;
	}
    }
}

double ** mm_matrix_mult( int xy_size, double **x, double **y )
{
  //allocate results matrix
  double** myresult;
  myresult=mm_alloc(xy_size);
  //triple loop
  int i;
  int j;
  int k;
  int entry;
  for(i=0;i<xy_size;i++)
    {
      for(j=0;j<xy_size;j++)
	{
	  entry=0;
	  for (k=0;k<xy_size;k++)
	    {
	      //took a while to figure out the indices
	      //	      entry=entry+((x[i][k])*(y[k][j]));
	      entry+=x[i][k]*y[k][j];
	    }
	  myresult[i][j]=entry;
	}
    }
  return(myresult);
}

void mm_print( int xy_size, double **matrix )
{
  int i;
  int j;
  for(i=0;i<xy_size;i++)
    {
      for(j=0;j<xy_size;j++)
	{
	  printf("%d ",(int)matrix[i][j]);
	}
      printf("\n");
    }
}

int main()
{
    /*
     * you must keep this function AS IS. 
     * you cannot modify it!
     */
    char filename[256];
    double **x_matrix=NULL;
    double **y_matrix=NULL;
    double **results_matrix=NULL;
    int xy_size=0;

    printf("Please enter the matrix data file name: ");
    scanf( "%s", filename );

    mm_read( filename, &xy_size, &x_matrix, &y_matrix );

    results_matrix = mm_matrix_mult( xy_size, x_matrix, y_matrix );

    mm_print( xy_size, results_matrix );

    mm_free( xy_size, x_matrix );
    mm_free( xy_size, y_matrix );
    mm_free( xy_size, results_matrix );

    return( 0 ); 
}
