#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include<math.h>

void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void bubbleSort(float arr[3731][2]){
	for(int i = 0; i < 3731; i++){
		for(int j = 0; j < 3730;j++){
			if(arr[j][0]>arr[j+1][0]){
				float temp = arr[j][0];
				float temp2 = arr[j][1];
				arr[j][0] = arr[j+1][0];
				arr[j+1][0] = temp;
				arr[j][1] = arr[j+1][1];
				arr[j+1][1] = temp2;
			}
		}
	}
}
void randomize ( int arr[], int n ) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap(&arr[i], &arr[j]); 
    } 
}

void populate(int *arr, int num){
	for(int i = 0 ; i < num; i++){
		arr[i] = i;
	}
}


float distanceformula(float *row1,float *row2, int p){
	float sum = 0;
	float fp = (float)p;
	for(int i = 0; i<64; i++){
		sum+=pow(fabs(row1[i]-row2[i]),fp);
	}
	return pow(sum,1/fp);
}

void calculateDistance(float arr[][3822][3822],float arr2[3822][65], int size){
	for(int i = 0; i < size; i++){
		for(int j = i; j < size; j++){
			for(int p = 0; p < 5; p++){
				arr[p][i][j] = distanceformula(arr2[i],arr2[j],p+1);
				arr[p][j][i] = arr[p][i][j];
			}
		}
	}
}


float knnClass(float arr[3731][2],int k){

	int carr[10] = {0};
	for(int i = 0 ; i < 3731;i++ ){
		carr[(int)arr[i][1]]++;
	}
	
	int max = 0;
	for(int i = 0; i < 10; i++){
		if(carr[i]>carr[max]){
			max = i;
		}

	}

	return max;
}


int main(int argc, char const *argv[]) {

	//creating new array from 0 to 209 and shuffle it
	int shufflearr[3822];
	populate(shufflearr, 3822);
	randomize(shufflearr, 3822);


	FILE *fp;
	fp = fopen("optdigits.tra", "r");
	char c[1000]; //c is the line read from the file

	float data[3822][65]; //initialize the data array .. complete data will be strored here
	int count = 0;
	int row = -1;
	while(fgets(c, 1000, fp)){ //c is the line read from the file
		//printf("%s",c );
		char *token = strtok(c,","); // Splitting the line in different values.
		
		while(token){
			
			
			//----------Input In the matrix----------------
			if (token!='\n'){   //Checking for the new line
				float temp = atof(token);
				int column = count % 65;  //Modifying the column if the count is 8 column becomes 0
				if(column == 0){
					row++;
					//printf("row = %d---------------------------- \n",row );
				} 
				data[shufflearr[row]][column] = temp;
				count++; //Counts the element going inside the matrix
				//printf("%f\t%d\t %d\n",temp,row,column );
			}
			
			token = strtok(NULL, ",");
		}
		
	
	}

	fclose(fp);


	float distances[5][3822][3822];
	calculateDistance(distances,data,3822);

	float dist[3731][2];
	float rkp[42][10][5] = {0};
	for(int r = 0; r < 42; r++ ){
		for(int p = 0; p < 5; p++){
			for(int temp1 = 91*r; temp1 < 91*(r+1); temp1++){
				int count = 0;
				{
					for(int utemp = 0; utemp < 91*r; utemp++){
						dist[count][0] = distances[p][temp1][utemp];
						dist[count++][1] = data[utemp][64];
					}
					for(int dtemp = 91*(r+1); dtemp < 3822; dtemp++){
						dist[count][0] = distances[p][temp1][dtemp];
						dist[count++][1] = data[dtemp][64];
					}
					bubbleSort(dist);
					for(int k = 0 ; k < 10; k++){
						//printf("%f\t%f\n", data[temp1][7],knnClass(dist,k));
						if(data[temp1][64] != knnClass(dist,k)){
							rkp[r][k][p]+=1;
						}
					}
				}
			}
		}
	}


	// -----------------------------------------Printing of the array--------------------

	// for(int j = 0;j <3822;j++){
	// 	for (int i = 0; i < 65; ++i){
	// 		printf("%.1f\t",data[j][i] );
	// 	}
	// 	printf("\n");
	// }

	//------------------------------------------printing of the array closed...---------------


float kp[10][5] = {0};
	for(int r= 0; r< 42;r++){
		for(int i = 0; i < 10; i++){
			for(int j = 0; j< 5; j++){
				kp[i][j]+=rkp[r][i][j];
			}
			
		}
		
	}
	float min = 999999;
	int k = 1;
	int p = 1;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j<5; j++){
			if(kp[i][j]<min){
				k = i+1;
				p = j+1;
				min = kp[i][j];
			}
			//printf("%f\t",kp[i][j] );
		}
		//printf("\n");
	}
	printf("We will get different value of K and P because\ndata is shuffeled every time.\n");
	printf("K = %d\tP = %d",k,p );
	return 0;

}