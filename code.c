#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char** argv)
{
	int size,rank,sum,k,t;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int i;
	float riat[100],rst[100];
//Generating Random numbers for IAT
	for(i=0;i<20;i++)
	{
		riat[i]=rand()%100;
	}
//Generating Random numbers for ST
        for(i=0;i<20;i++)
        {
                rst[i]=rand()%100;
        }

	//for(i=0;i<20;i++)
	//{
	//	printf("\n%f",riat[i]);
	//}
	float sciat[10],scst[10];
//Scattering 10 IAT RandNumbers
	MPI_Scatter(riat,10,MPI_FLOAT,sciat,10,MPI_FLOAT,0,MPI_COMM_WORLD);
//Scattering 10 ST RandNumbers
	MPI_Scatter(rst,10,MPI_FLOAT,scst,10,MPI_FLOAT,0,MPI_COMM_WORLD);
	float iat[10],aat[10],st[10],start[10],end[10],wt[10],idle[10];
	if(rank==0)
	{
		//printf("\nIAT RANDOM NUMBERS ARE:");
		for(i=0;i<10;i++)
		{
//		//	printf("\n%f",sciat[i]);
		}
                //printf("\nST RANDOM NUMBERS ARE:");
                for(i=0;i<10;i++)
                {
  //              //        printf("\n%f",scst[i]);
                }
		for(i=0;i<10;i++)
		{
			if(sciat[i]<=20)
			{
				iat[i]=2.0;
			}
			else if(sciat[i]>20 && sciat[i]<=50)
			{
				iat[i]=2.5;
			}
			 else if(sciat[i]>50 && sciat[i]<=70)
                        {
                                iat[i]=3.0;
                        }
			else
			{
				iat[i]=4.0;
			}
                
                        if(scst[i]<=20)
                        {
                                st[i]=1.0;
                        }
                        else if(scst[i]>20 && scst[i]<=40)
                        {
                                st[i]=2.0;
                        }
                         else if(scst[i]>40 && scst[i]<=70)
                        {
                                st[i]=4.0;
                        }
                        else
                        {
                                st[i]=4.0;
                        }
			//printf("\nIIAT:%f",iat[i]);
			
			
			
		}
		aat[0]=iat[0];
		start[0]=aat[0];
		end[0]=st[0]+start[0];
		wt[0]=0;
		idle[0]=aat[0];
		float swt,sit;
		for(i=1;i<10;i++)
		{
			aat[i]=iat[i]+aat[i-1];
			start[i]=aat[i];
			end[i]=st[i]+start[i];
			wt[i]=aat[i]-start[i];
			swt=swt+wt[i];
			idle[i]=end[i-1]-start[i];
			if(idle[i]<0)
			{
				idle[i]=idle[i]*-1;
			}
			sit=sit+idle[i];
			
		}	
		printf("\nRD\t\tIAT\t\tAAT\t\tRD\t\tST\t\tStart\t\tEnd\t\tWT\t\tIDLE");
		for(i=0;i<10;i++)		
		{
			printf("\n%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f",riat[i],iat[i],aat[i],rst[i],st[i],start[i],end[i],wt[i],idle[i]);
		}
		float awt=swt/10;
		float ait=sit/10;
		printf("\nAverage Waiting Time:%f",awt);
                printf("\nAverage Idle  Time:%f",ait);


		

	}
	MPI_Finalize();
return 0;
}
	
