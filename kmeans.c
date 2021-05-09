# include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int mainFuncV2 (int K,  int max_iter);
double CreateVector();
double distanceFromMean(int i1, int j1, int n,double vec [], double mean [] );
void updateMean (int j, int place, int n,double vec [], double mean [], int numOfVec);
void updateCheck (int n,double vec [], double mean []);
int toStop (int n,double vec [], double mean []);

int main (int argc, char *argv[])
{
    if(argc==2){
            mainFuncV2 (atoi(argv[1]),200); }
    if(argc==3){
            mainFuncV2 (atoi(argv[1]),atoi(argv[2])); }
    assert(argc==2||argc==3);
    return (0);
}


double distanceFromMean(int i1, int j1, int n,double vec [], double mean [] ){
    double d=0;
    double meanI;
    double x;
    double distance;
    int i;
    for ( i = 0; i < n; i++)
    {
        meanI= mean[n*j1+i];
        x=vec[n*i1+i];
        distance= (x-meanI)*(x-meanI);
        d=d+distance;         
    }
    return (d);
}

void updateMean (int j, int place, int n,double vec [], double mean [], int numOfVec){
    int i;
    for ( i = 0; i < n; i++)
    {
        double meanI= mean[i+place*n];
        double sum;
        if (numOfVec>0){
            sum= meanI*numOfVec+vec[i+j*n];
        }
        else{
            sum= vec[i+j*n];
        }
        mean[i+place*n]= sum/(numOfVec+1); 
    }
}
void updateCheck (int n,double vec [], double mean []){
    int i;
    for ( i = 0; i < n; i++)
    {
        vec[i]=mean[i];
    }   
}

int toStop (int n,double vec [], double mean []){
    int i;
    for ( i = 0; i < n; i++){
        if(vec[i]!=mean[i]){
            return (0);
        }
    }
    return (1);
}


int mainFuncV2 (int K,  int max_iter) {
int i,j,cc,row,columns,b1,k1,k2,lines,iter,place,d,dim,i1,j1;
double distance,curDistance,cur;
char * token;
double *vecOfMeansOld;
double *vecOfMeansNew;
double *vector;
char *singleLine;
int *numberOfVecPerGroup;
char line[1000];
assert(K>0);
assert(max_iter>0);
numberOfVecPerGroup=(int *)malloc(sizeof(int)*K);
assert(numberOfVecPerGroup!=NULL);
lines=0;
i=0;
dim=1;
    while (scanf("%s",line)!=EOF){
        if (dim==1){
            while (line[i]!='\0'){
                if (line[i]==','){
    
                    dim++;
                }
                i++;
            }
        }
            lines++;
        }
    assert(K<lines);
    rewind(stdin);
    vector = (double *)malloc(sizeof(double)*(lines+1)*(dim+1));
    assert(vector!=NULL);
    i1=0;
    j1=0;
    singleLine=(char *)malloc(sizeof(char)*dim*64);
    assert(singleLine!=NULL);
    while(scanf("%s",singleLine)!=EOF){
        assert(singleLine!=NULL);
        token = strtok(singleLine, ",");
        while( token != NULL ) {
            cur=atof(token);
            vector[dim*i1+j1]=cur;
            token = strtok(NULL, ",");
            j1++;
        }
        i1++;
        j1=0;
    }
free(singleLine);
iter=0;
for ( iter = 0; iter < K; iter++)
{
    numberOfVecPerGroup[iter]=0;

}
iter=0;
vecOfMeansOld = (double *)malloc(sizeof(double)*(K+1)*(dim+1));
assert(vecOfMeansOld!=NULL);
vecOfMeansNew = (double *)malloc(sizeof(double)*(K+1)*(dim+1));
assert(vecOfMeansNew!=NULL);

for ( i = 0; i < K; i++)
{
    for ( cc = 0; cc < dim; cc++)
    {
        vecOfMeansOld[i*dim+cc]= vector[i*dim+cc];
        
    }
    
}
d=dim;
while(iter<max_iter){
        
        for ( i = 0; i < lines ; i++)
        {
            distance=0;
            place=0;
            
            for (  j = 0; j < K; j++)
            {
                curDistance= distanceFromMean(i,j, d, vector, vecOfMeansOld );
                if (j==0){
                        distance=curDistance;
                }
                if(curDistance< distance){
                    distance=curDistance;
                    place=j;
                } 
            }
            updateMean (i,place,d, vector, vecOfMeansNew , numberOfVecPerGroup[place]);
            numberOfVecPerGroup[place]=numberOfVecPerGroup[place]+1;
        }

        b1=1;
        for (k1=0; k1<K; k1++)
        {
            for (k2 = 0; k2 < dim; k2++)
            {
                if(vecOfMeansOld[k1*dim+k2]!=vecOfMeansNew[k1*dim+k2]){
                    b1=0;
                }
            }    
        }
        if (b1==1){
            break;
        }
        for (k1=0; k1<K; k1++)
        {
            for (k2 = 0; k2 < dim; k2++)
            {
                vecOfMeansOld[k1*dim+k2]=vecOfMeansNew[k1*dim+k2];
                vecOfMeansNew[k1*dim+k2]=0;
            }
            
        }
        for ( i = 0; i < K; i++)
        {
            numberOfVecPerGroup[i]=0;
        }
        iter++;
    }
    for (row=0; row<K; row++)
    {
        for(columns=0; columns<dim; columns++)
        {
         printf("%.4f", vecOfMeansOld[row*dim+columns]);
         if (columns!=(dim-1)){
             printf(",");
         }
        }
        printf("\n");
    }
    
    free(vector);
    free(vecOfMeansOld);
    free(numberOfVecPerGroup);
    free(vecOfMeansNew);
    return (0);
}