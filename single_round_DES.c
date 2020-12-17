/*
TOPIC			: SINGLE ROUND D.E.S 
PRACTICAL		: 10
GROUP MEMBERS	:Joshi Chintan(170450107010)
				:Khatri Jayesh(170450107014)
				:Natali Utkarsh(170450107020)
				:Padhiyar Dipen(170450107021)
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
//(1)Initial permutation........
int initialPermutation(int x[]);
	//Decimal to binary
	void decitobin(int decivalue,char hexavalue[]);
	//Hexa value to binary
	void hextobin(char pt[],int x[]);
	//store data
	int ipval[64],lpart[32],rpart[32];

//(2)Expansion permutation.......
int expansionPermutation(int rightbox[32]);
	//EXPANSION values
	int expansion[48];
	
//(3)s-box declaration...........
int s_box(int xoroutput[48]);
	//convert binary to deccimal
	int BinaryToDecimal(int n);
	//convert decimal to binary
	void DecimalToBinary(int n);
	// S-Box Output array
	int OUTPUT[4];
	// Output array(result)
	int OUTPUT_BINARY[32];
	
//(4)Final permutation P
int f_permutatioin(int sbox_output[32]);
	//result
	int final_per[32];

//(5)Final XOR rightbox  with Leftbox
int f_xor32(int fp[32],int leftbox[32]);
	//result
	int resulte32xor[32];

int main()
{
	system("color f0");
	//indexes
	int i,j=0,k,n;
	//counter
	int count=0;
	//key
	int key48[48]={0,0,0,0,0,0,0,0,0,0,0,0,
				   1,1,1,1,1,1,1,1,1,1,1,1,
				   0,1,0,1,0,1,0,1,0,1,0,1,
				   1,1,1,1,1,1,1,1,1,1,1,1};//key56[56]={0},c[32]={0},d[32]={0};
	//initial permutation
	char hexavalue[16];
  	int binvalue[64],decivalue;
  	int x[8][8],choice;
	//Expansion_permutation				       
	int arr[8][4],counter=0;
	//XOR 48-bit
	int xorfinal[48];
	//32-bit permutsion
	printf("____________________SINGLE ROUND DES____________________\n\n");  
	//1.Key.....................................................
	printf("(1).KEY 48-bit is :\n\t");
	for(i=0;i<48;i++){
		if(i==12 ||i==24 ||i==36){printf("\n\t");}
		printf("%d ",key48[i]);
	}
	//2.Operation on Input 64-bit...............................
	 //2.1. Find initial permutation of 64-bit key.
	 printf("\n\n(2).Initial Permutation of PLAIN TEXT :\n");
  	 printf("\nEnter plain text in decimal system:-");
	 scanf("%d",&decivalue);
	 decitobin(decivalue,hexavalue);
	 hextobin(hexavalue,binvalue);
	 printf("\nThe Value of X:-\n\t");
	   for(i=0;i<8;i++){
   			for(j=0;j<8;j++){
   				x[i][j]=binvalue[count++];
   				printf("%d ",x[i][j]);
	 		}
	   		printf("\n\t");
   		}
   		initialPermutation(binvalue);
	 //2.2. Now divide 64-bit into 32-bit left box and 32-bit right box.
	 printf("\nDivide 64-bit into Initial Permutation :\n");
	 k=0;
	 for(i=0;i<64;i++){
	 	if(i<32){lpart[i]=ipval[i];}
	 	if(i>31){rpart[k]=ipval[i];
		 k++;}
	}
	 printf("LEFT-BOX :-->\n");
	 for(i=0;i<32;i++){
	 	if(i==8||i==16||i==24){printf("\n");}
	 	printf("%d ",lpart[i]);
	 }
	printf("\n\nRIGHT-BOX :-->\n");
	 for(i=0;i<32;i++){
	 	if(i==8||i==16||i==24){printf("\n");}
	 	printf("%d ",rpart[i]);
	 }
	 //2.3.	Now apply operation on right-box.
	  //2.3.1. Apply expansion and permutation on right box output is 48-bit.
	  expansionPermutation(rpart);
	  //2.3.2. Generated output of expansion box and 48-bit key is XOR.
	  printf("\n\n(4).Apply XOR operation on expansion_Box and 48-bit key :\n\t");
	  for(i=0;i<48;i++){
	  	//xor operation
	  	xorfinal[i]=key48[i]^expansion[i];
	  	if(i==12 ||i==24 ||i==36){printf("\n\t");}
		printf("%d ",xorfinal[i]);
	  }
	  //2.3.3. After XOR output is go to S-box; S-box convert 48-bit input into 32-bit.
	  s_box(xorfinal);
	  //2.3.4. 32-bit of s-box output is again permuted.
	  f_permutatioin(OUTPUT_BINARY);
	//3.Now generated right-box is XOR with Left-box.
	f_xor32(final_per,lpart);
	//4.Now rightBox is LeftBox for next round and right box is output of final XOR 32-bit.
	
	printf("\n\n(8).Final Result is :\n");
	printf("\n\t\tNEW LEFT-BOX is:");
	for(i=0;i<32;i++){
		lpart[i]=rpart[i];
		if(i==8 ||i==16 ||i==24){printf("\n\t\t\t\t");}
		printf("%d ",lpart[i]);
	}
	printf("\n\n\t\tNEW RIGHT-BOX is:");
	for(i=0;i<32;i++){
		rpart[i]=resulte32xor[i];
		if(i==8 ||i==16 ||i==24){printf("\n\t\t\t\t ");}
		printf("%d ",rpart[i]);
	}
	return 0;
}

//functions
	//initial permutation....
	int initialPermutation(int x[]){
		int ip[8][8]={{58,50,42,34,26,18,10,2},
					  {60,52,44,36,28,20,12,4},
					  {62,54,46,38,30,22,14,6},
					  {64,56,48,40,32,24,16,8},
					  {57,49,41,33,25,17,9,1},
					  {59,51,43,35,27,19,11,3},
					  {61,53,45,37,29,21,13,5},
					  {63,55,47,39,31,23,15,7}};
	int loc[64],k,counter=0,i,j,count;
	int ip_x[8][8]={0};
		for(i=0;i<64;i++){
		   if(x[i]==1){
		   	 loc[counter]=i+1;
		   	 counter++;
		   }
		}
		for(i=0;i<64;i++)
		   x[i]=0;
  
		count=0; 
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				for(k=0;k<counter;k++){	
				   if(loc[k]==ip[i][j]){
				   	ip_x[i][j]=1;
				   	x[8*i+j]=1;
				   	break;
				   }
				}	
			}
		}
	   	printf("\nThe Value of IP(X):-\n\t");
	   	k=0;
	   	for(i=0;i<8;i++){
	   		for(j=0;j<8;j++){
	   			ipval[k]=ip_x[i][j];
	   			k++;
		 	}
   		}
   		for(i=0;i<64;i++){
   			if(i==8||i==16||i==24||i==32||i==40||i==48||i==56){printf("\n\t");}
   		printf("%d ",ipval[i]);	
		}
		return 0;
	}
	void decitobin(int decivalue,char hexavalue[]){
	 int i,quotient,remainder,index=15;
	 for(i=0;i<16;i++) 
		 hexavalue[i]='0';	
	  
		while (decivalue != 0)
	    {
	        remainder = decivalue % 16;
	        if (remainder < 10)
	            hexavalue[index--] = 48 + remainder;
	        else
	            hexavalue[index--] = 55 + remainder;
	        decivalue = decivalue / 16;
	    }	
	    printf("\nThe X(in hexa)=0x:-\t");
		for(i=0;i<16;i++){
		  printf("%c",hexavalue[i]);
		}
	}	
	void hextobin(char pt[],int x[]){
	int i=0;
	int count=0;
		while(pt[i]){
			switch(pt[i]){
			case '0':x[count]=0;x[count+1]=0;x[count+2]=0;x[count+3]=0;break;
			case '1':x[count]=0;x[count+1]=0;x[count+2]=0;x[count+3]=1;break;
			case '2':x[count]=0;x[count+1]=0;x[count+2]=1;x[count+3]=0;break;
			case '3':x[count]=0;x[count+1]=0;x[count+2]=1;x[count+3]=1;break;
			case '4':x[count]=0;x[count+1]=1;x[count+2]=0;x[count+3]=0;break;
			case '5':x[count]=0;x[count+1]=1;x[count+2]=0;x[count+3]=1;break;
			case '6':x[count]=0;x[count+1]=1;x[count+2]=1;x[count+3]=0;break;
			case '7':x[count]=0;x[count+1]=1;x[count+2]=1;x[count+3]=1;break;
			case '8':x[count]=1;x[count+1]=0;x[count+2]=0;x[count+3]=0;break;
			case '9':x[count]=1;x[count+1]=0;x[count+2]=0;x[count+3]=1;break;
			case 'A':
			case 'a':x[count]=1;x[count+1]=0;x[count+2]=1;x[count+3]=0;break;
			case 'B':
			case 'b':x[count]=1;x[count+1]=0;x[count+2]=1;x[count+3]=1;break;
			case 'C':
			case 'c':x[count]=1;x[count+1]=1;x[count+2]=0;x[count+3]=0;break;
			case 'D':
			case 'd':x[count]=1;x[count+1]=1;x[count+2]=0;x[count+3]=1;break;
			case 'E':
			case 'e':x[count]=1;x[count+1]=1;x[count+2]=1;x[count+3]=0;break;
			case 'F':
			case 'f':x[count]=1;x[count+1]=1;x[count+2]=1;x[count+3]=1;break;
			}
			count+=4;
			 i++;
		}
	}
	
	//Expansion and Parmutation.....
	int expansionPermutation(int rightbox[32])
	{
		// The array elements denote the bit numbers
	int i;
	int expansion_table[48]={32,1,2,3,4,5,4,5, 
		  					6,7,8,9,8,9,10,11, 
						    12,13,12,13,14,15,16,17, 
						    16,17,18,19,20,21,20,21, 
						    22,23,24,25,24,25,26,27, 
						    28,29,28,29,30,31,32,1}; 	
		for(i=0;i<48;i++){
    		expansion[i]=rightbox[(expansion_table[i])-1];
		}
		printf("\n\n(3).Expansion of 32-bit right box into 48-bit is :\n\t");
		for(i=0;i<48;i++){
		if(i==12 ||i==24 ||i==36){printf("\n\t");}
		printf("%d ",expansion[i]);
		}
		return 0;
	}
	//S-BOX......
	int s_box(int xoroutput[48])
	{
		int j=0,temp=0;										// Initials
		int row,m,col,r1,c1,l,i;							// Local variables
		int binary_input[48], binary_sbox_output[8][4];		// Binary arrays
		int S_BOX [8][4][16]={								// 3d Array to store 8 Substituion boxes of size 4 X 16
			{
				{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
				{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
				{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
				{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
			},
			{
				{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
				{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
				{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
				{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
			},
			{
				{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
				{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
				{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
				{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
			},
			{
				{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
				{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
				{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
				{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
			},
			{
				{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
				{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
				{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
				{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
			},
			{
				{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
				{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
				{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
				{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
			},
			{
				{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
				{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
				{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
				{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
			},
			{
				{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
				{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
				{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
				{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
			},
		};
		//printf("\nXOR output:\n");
		for (l = 0; l < 48; l++){
			binary_input[l] = xoroutput[l];
		//	if(l==12 ||l==24 ||l==36){printf("\n");}
		//	printf("%d ",binary_input[l]);
		}
		printf("\n\n(5).\t::::::S-BOX::::::\n");
		for (l = 0; l < 8; l++)
		{
			// First and Last digit of number to identify row
			r1 = binary_input[j+0] * 10 + binary_input[j+5] * 1;
			
			// Remaining digits to identify column
			c1 = binary_input[j+1] * 1000 + binary_input[j+2] * 100 + binary_input[j+3] * 10 + binary_input[j+4] * 1;
			
			// Converting to decimal because our array cannot be read with binary values
			row = BinaryToDecimal(r1);
			col = BinaryToDecimal(c1);
			
			// Displaying the result of above operations
			printf("\tS-Box %d ->",l+1);
			printf("\n\t Row: %d, Col: %d",row,col);
			printf("\n\t S-Box value: %d\n", S_BOX[l][row][col]);
			
			// Converting the values back to binary and storing it in the OUTPUT array
			DecimalToBinary(S_BOX[l][row][col]);
			
			for(i=0;i<4;i++)
			{
				binary_sbox_output[l][i] = OUTPUT[i];
			}
			
			j=j+6;
		}
		
		i=0;
		printf("\t Binary Value OUTPUT(S-BOX): \n\t\t");
		for (l = 0; l < 8; l++)
			for(j=0;j<4;j++)
			OUTPUT_BINARY[i++] = binary_sbox_output[l][j];
		
		for(i=0; i < 32; i++)
		{
			if(i==8 ||i==16 ||i==24){printf("\n\t\t");}
			printf(" %d",OUTPUT_BINARY[i]);
		}
		return 0;
	}
	//(s-box)Converting Binary values to Decimal values for calculations
	int BinaryToDecimal(int n)
	{
		int sum = 0, i = 0, r;
		while (n!=0)
		{
			r = n % 10;
			n = n / 10;
			sum = sum + r * pow(2,i);
			i++;
		}
		return sum;
	}
	//(s-box)Converting Decimal values to Binary for the final output
	void DecimalToBinary(int n)
	{
		int i=3,k=0;
		for (i = 3; i >= 0; i--)
		{
			OUTPUT[k+3]=n%2;
			n=n/2;
			k--;
		}
		printf("\n\tBinary output from S-Box: ");
		
		for(i=0;i<4;i++)
		{
			printf(" %d",OUTPUT[i]);
		}
		printf("\n\n");
		k=k+7;
	}
	//Final permutation.....
	int f_permutatioin(int sbox_output[32]){
		int i;
		//permutation table for positioning
		int permutation_table[32] = {16,7,20,21,29,12,28,17, 
   								 	 1,15,23,26,5,18,31,10, 
							    	 2,8,24,14,32,27,3,9, 
							         19,13,30,6,22,11,4,25};
    	for(i=0;i<32;i++){
    		final_per[i]=sbox_output[(permutation_table[i])-1];
		}
		printf("\n\n(6).Final permutation of S-BOX is :\n\t");
		for(i=0;i<32;i++){
			if(i==8 ||i==16 ||i==24){printf("\n\t");}
			printf(" %d",final_per[i]);
		}
		return 0;
	}
	//32bit of rightbox-final permutation and 32-bit leftbox is XOR......
	int f_xor32(int fp[32],int leftbox[32]){
		int i;
		
		printf("\n\n(7).Apply XOR operation on Final_permutation and leftbox(initial permutation):\n\t");
	  	for(i=0;i<32;i++){
	  		//xor operation
	  		resulte32xor[i]=fp[i]^leftbox[i];
	  		if(i==8 ||i==16 ||i==24){printf("\n\t");}
			printf("%d ",resulte32xor[i]);
	  }
	  return 0;
	}
