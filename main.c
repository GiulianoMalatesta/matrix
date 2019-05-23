#include <stdio.h>
#include <math.h>

int get_dim(char *filein);
int determinant(int n, double mat[n][n]);
void multiply();

int main (int argc, char *argv[]){
    
    FILE *fp;
    int i, j;
    int n; /*matrix dimension */
    int choice;    
  
    if (argc == 1){
        printf("Please enter file name\n");
        return 1;
    }    
    
    printf("Enter 1 for matrix multiplication\nEnter 2 for determinant calculation\nEnter 3 to exit\n");
    
    scanf("%d", &choice);
    
    while ( (choice <= 0) || (choice >3) ){
            printf("Enter a number between 1 and 2, 3 to end");
            scanf("%d", &choice);
    }

    if (choice == 1)
        multiply();
    
    if (choice == 2){
        n = get_dim(argv[1]);
        double mat[n][n];
        
        if( (fp = fopen(argv[1], "r")) != NULL ){
            for(i=0; i < n; i++)
                for(j=0; j < n; j++)
                    fscanf(fp, "%lf", &mat[i][j]);

            printf("Determinant: %d\n", determinant(n, mat));  
            printf("Dimension:%d\n",n);
            fclose(fp);
        }
        
        else{
          printf("I can't open file %s\n", argv[1]);
          return 1;
        }
    }   
    
    if (choice == 3)
        return 0; 
    
    return 0;    
}

int get_dim(char *filein){
    
    FILE *file_in = fopen(filein, "r");
    char c;
    int temp;
    int n = 0;
    if (file_in)
    {
        // you get the characters one by one and check if
        // if it is an end of line character or EOF
        while ((c = (char)fgetc(file_in)) != '\n' && c != EOF)
        {
            // if it wasn't, you put it back to the stream
            ungetc(c, file_in);
            // scan your number
            fscanf(file_in, "%d", &temp);
            n++;
        }

        fclose(file_in);
    }
    
    else
    {
        fprintf(stderr, "Could not open specified file.\n");
        return 1;
    }
    
    return n;    
}   

int determinant(int n, double mat[n][n]){                
                    
    int i,j,i_count,j_count, count=0;
	double array[n-1][n-1], det=0;
 
	if(n < 1)
	{
		printf("Wrong dimension");
		return 1;
	}
	if(n==1) return mat[0][0];
	if(n==2) return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);
 
	for(count=0; count<n; count++)
	{
		//Creating array of Minors
		i_count=0;
		for(i=1; i<n; i++)
		{
			j_count=0;
			for(j=0; j<n; j++)
			{
				if(j == count) continue;
				array[i_count][j_count] = mat[i][j];
				j_count++;
			}
			i_count++;
		}
		det += pow(-1, count) * mat[0][count] * determinant(n-1,array);	//Recursive call
	}
	return det;
}

void multiply(){
    printf("I'm doing nothing for the moment");
}
