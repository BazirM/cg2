#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>

using namespace std;

float res[3];
float res1[3];
float res2[3];
float res3[3];

float res4[3];

int nvPatch = 0;

vector<float> vertV;
vector<float> vertH;
vector<float> vert;

vector<float> normalV;
vector<float> textV;


float* getPoints(int *patchs, int n_patch, float *vertices, int n_vertices, int tess, float t, float v){

	float P1x,P1y,P1z,P2x,P2y,P2z,P3x,P3y,P3z,P4x,P4y,P4z,P5x,
	P5y,P5z,P6x,P6y,P6z,P7x,P7y,P7z,P8x,P8y,P8z,P9x,P9y,P9z,P10x,
	P10y,P10z,P11x,P11y,P11z,P12x,P12y,P12z,P13x,P13y,P13z,P14x,
	P14y,P14z,P15x,P15y,P15z,P16x,P16y,P16z;
	float a,b,c,d;
	int i,j,k;

	float m[4][4] = {	{-1.0f,  3.0f, -3.0f,  1.0f},
						{ 3.0f, -6.0f,  3.0f,  0.0f},
						{-3.0f,  3.0f,  0.0f,  0.0f},
						{ 1.0f,  0.0f,  0.0f,  0.0f}};
						
	float mt[4][4] = {	{-1.0f,  3.0f, -3.0f,  1.0f},
						{ 3.0f, -6.0f,  3.0f,  0.0f},
						{-3.0f,  3.0f,  0.0f,  0.0f},
						{ 1.0f,  0.0f,  0.0f,  0.0f}};

	float ax[4];
	float ay[4];
	float az[4];

	float ax1[4];
	float ay1[4];
	float az1[4];

    k = n_patch;

        P1x = vertices[3*patchs[(16*k)]];         
        P1y = vertices[3*patchs[(16*k)]+1];     
        P1z = vertices[3*patchs[(16*k)]+2];
        P2x = vertices[3*patchs[(16*k+1)]];       
        P2y = vertices[3*patchs[(16*k+1)]+1];  
        P2z = vertices[3*patchs[(16*k)+1]+2];
        P3x = vertices[3*patchs[(16*k+2)]];       
        P3y = vertices[3*patchs[(16*k+2)]+1];   
        P3z = vertices[3*patchs[(16*k)+2]+2];
        P4x = vertices[3*patchs[(16*k+3)]];       
        P4y = vertices[3*patchs[(16*k+3)]+1];   
        P4z = vertices[3*patchs[(16*k)+3]+2];
        P5x = vertices[3*patchs[(16*k+4)]];       
        P5y = vertices[3*patchs[(16*k+4)]+1];   
        P5z = vertices[3*patchs[(16*k)+4]+2];
        P6x = vertices[3*patchs[(16*k+5)]];       
        P6y = vertices[3*patchs[(16*k+5)]+1];   
        P6z = vertices[3*patchs[(16*k)+5]+2];
        P7x = vertices[3*patchs[(16*k+6)]];       
        P7y = vertices[3*patchs[(16*k+6)]+1];   
        P7z = vertices[3*patchs[(16*k)+6]+2];
        P8x = vertices[3*patchs[(16*k+7)]];       
        P8y = vertices[3*patchs[(16*k+7)]+1];   
        P8z = vertices[3*patchs[(16*k)+7]+2];
        P9x = vertices[3*patchs[(16*k+8)]];       
        P9y = vertices[3*patchs[(16*k+8)]+1];   
        P9z = vertices[3*patchs[(16*k)+8]+2];
        P10x = vertices[3*patchs[(16*k+9)]];       
        P10y = vertices[3*patchs[(16*k+9)]+1];   
        P10z = vertices[3*patchs[(16*k)+9]+2];
        P11x = vertices[3*patchs[(16*k+10)]];      
        P11y = vertices[3*patchs[(16*k+10)]+1];  
        P11z = vertices[3*patchs[(16*k)+10]+2];
        P12x = vertices[3*patchs[(16*k+11)]];      
        P12y = vertices[3*patchs[(16*k+11)]+1];  
        P12z = vertices[3*patchs[(16*k)+11]+2];
        P13x = vertices[3*patchs[(16*k+12)]];     
        P13y = vertices[3*patchs[(16*k+12)]+1];  
        P13z = vertices[3*patchs[(16*k)+12]+2];
        P14x = vertices[3*patchs[(16*k+13)]];      
        P14y = vertices[3*patchs[(16*k+13)]+1];  
        P14z = vertices[3*patchs[(16*k)+13]+2];
        P15x = vertices[3*patchs[(16*k+14)]];      
        P15y = vertices[3*patchs[(16*k+14)]+1];  
        P15z = vertices[3*patchs[(16*k)+14]+2];
        P16x = vertices[3*patchs[(16*k+15)]];      
        P16y = vertices[3*patchs[(16*k+15)]+1];  
        P16z = vertices[3*patchs[(16*k)+15]+2];


        ax[0]=m[0][0]*P1x+m[0][1]*P2x+m[0][2]*P3x+m[0][3]*P4x;
		ax[1]=m[1][0]*P1x+m[1][1]*P2x+m[1][2]*P3x+m[1][3]*P4x;
		ax[2]=m[2][0]*P1x+m[2][1]*P2x+m[2][2]*P3x+m[2][3]*P4x;
		ax[3]=m[3][0]*P1x+m[3][1]*P2x+m[3][2]*P3x+m[3][3]*P4x;
		
		ay[0]=m[0][0]*P1y+m[0][1]*P2y+m[0][2]*P3y+m[0][3]*P4y;
		ay[1]=m[1][0]*P1y+m[1][1]*P2y+m[1][2]*P3y+m[1][3]*P4y;
		ay[2]=m[2][0]*P1y+m[2][1]*P2y+m[2][2]*P3y+m[2][3]*P4y;
		ay[3]=m[3][0]*P1y+m[3][1]*P2y+m[3][2]*P3y+m[3][3]*P4y;

		az[0]=m[0][0]*P1z+m[0][1]*P2z+m[0][2]*P3z+m[0][3]*P4z;
		az[1]=m[1][0]*P1z+m[1][1]*P2z+m[1][2]*P3z+m[1][3]*P4z;
		az[2]=m[2][0]*P1z+m[2][1]*P2z+m[2][2]*P3z+m[2][3]*P4z;
		az[3]=m[3][0]*P1z+m[3][1]*P2z+m[3][2]*P3z+m[3][3]*P4z;

		res[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*P5x+m[0][1]*P6x+m[0][2]*P7x+m[0][3]*P8x;
		ax[1]=m[1][0]*P5x+m[1][1]*P6x+m[1][2]*P7x+m[1][3]*P8x;
		ax[2]=m[2][0]*P5x+m[2][1]*P6x+m[2][2]*P7x+m[2][3]*P8x;
		ax[3]=m[3][0]*P5x+m[3][1]*P6x+m[3][2]*P7x+m[3][3]*P8x;
		
		ay[0]=m[0][0]*P5y+m[0][1]*P6y+m[0][2]*P7y+m[0][3]*P8y;
		ay[1]=m[1][0]*P5y+m[1][1]*P6y+m[1][2]*P7y+m[1][3]*P8y;
		ay[2]=m[2][0]*P5y+m[2][1]*P6y+m[2][2]*P7y+m[2][3]*P8y;
		ay[3]=m[3][0]*P5y+m[3][1]*P6y+m[3][2]*P7y+m[3][3]*P8y;

		az[0]=m[0][0]*P5z+m[0][1]*P6z+m[0][2]*P7z+m[0][3]*P8z;
		az[1]=m[1][0]*P5z+m[1][1]*P6z+m[1][2]*P7z+m[1][3]*P8z;
		az[2]=m[2][0]*P5z+m[2][1]*P6z+m[2][2]*P7z+m[2][3]*P8z;
		az[3]=m[3][0]*P5z+m[3][1]*P6z+m[3][2]*P7z+m[3][3]*P8z;

		res1[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res1[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res1[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*P9x+m[0][1]*P10x+m[0][2]*P11x+m[0][3]*P12x;
		ax[1]=m[1][0]*P9x+m[1][1]*P10x+m[1][2]*P11x+m[1][3]*P12x;
		ax[2]=m[2][0]*P9x+m[2][1]*P10x+m[2][2]*P11x+m[2][3]*P12x;
		ax[3]=m[3][0]*P9x+m[3][1]*P10x+m[3][2]*P11x+m[3][3]*P12x;
		
		ay[0]=m[0][0]*P9y+m[0][1]*P10y+m[0][2]*P11y+m[0][3]*P12y;
		ay[1]=m[1][0]*P9y+m[1][1]*P10y+m[1][2]*P11y+m[1][3]*P12y;
		ay[2]=m[2][0]*P9y+m[2][1]*P10y+m[2][2]*P11y+m[2][3]*P12y;
		ay[3]=m[3][0]*P9y+m[3][1]*P10y+m[3][2]*P11y+m[3][3]*P12y;

		az[0]=m[0][0]*P9z+m[0][1]*P10z+m[0][2]*P11z+m[0][3]*P12z;
		az[1]=m[1][0]*P9z+m[1][1]*P10z+m[1][2]*P11z+m[1][3]*P12z;
		az[2]=m[2][0]*P9z+m[2][1]*P10z+m[2][2]*P11z+m[2][3]*P12z;
		az[3]=m[3][0]*P9z+m[3][1]*P10z+m[3][2]*P11z+m[3][3]*P12z;

		res2[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res2[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res2[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*P13x+m[0][1]*P14x+m[0][2]*P15x+m[0][3]*P16x;
		ax[1]=m[1][0]*P13x+m[1][1]*P14x+m[1][2]*P15x+m[1][3]*P16x;
		ax[2]=m[2][0]*P13x+m[2][1]*P14x+m[2][2]*P15x+m[2][3]*P16x;
		ax[3]=m[3][0]*P13x+m[3][1]*P14x+m[3][2]*P15x+m[3][3]*P16x;
		
		ay[0]=m[0][0]*P13y+m[0][1]*P14y+m[0][2]*P15y+m[0][3]*P16y;
		ay[1]=m[1][0]*P13y+m[1][1]*P14y+m[1][2]*P15y+m[1][3]*P16y;
		ay[2]=m[2][0]*P13y+m[2][1]*P14y+m[2][2]*P15y+m[2][3]*P16y;
		ay[3]=m[3][0]*P13y+m[3][1]*P14y+m[3][2]*P15y+m[3][3]*P16y;

		az[0]=m[0][0]*P13z+m[0][1]*P14z+m[0][2]*P15z+m[0][3]*P16z;
		az[1]=m[1][0]*P13z+m[1][1]*P14z+m[1][2]*P15z+m[1][3]*P16z;
		az[2]=m[2][0]*P13z+m[2][1]*P14z+m[2][2]*P15z+m[2][3]*P16z;
		az[3]=m[3][0]*P13z+m[3][1]*P14z+m[3][2]*P15z+m[3][3]*P16z;

		res3[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res3[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res3[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax1[0]=mt[0][0]*res[0]+m[0][1]*res1[0]+m[0][2]*res2[0]+m[0][3]*res3[0];
		ax1[1]=mt[1][0]*res[0]+m[1][1]*res1[0]+m[1][2]*res2[0]+m[1][3]*res3[0];
		ax1[2]=mt[2][0]*res[0]+m[2][1]*res1[0]+m[2][2]*res2[0]+m[2][3]*res3[0];
		ax1[3]=m[3][0]*res[0]+m[3][1]*res1[0]+m[3][2]*res2[0]+m[3][3]*res3[0];
		
		ay1[0]=m[0][0]*res[1]+m[0][1]*res1[1]+m[0][2]*res2[1]+m[0][3]*res3[1];
		ay1[1]=m[1][0]*res[1]+m[1][1]*res1[1]+m[1][2]*res2[1]+m[1][3]*res3[1];
		ay1[2]=m[2][0]*res[1]+m[2][1]*res1[1]+m[2][2]*res2[1]+m[2][3]*res3[1];
		ay1[3]=m[3][0]*res[1]+m[3][1]*res1[1]+m[3][2]*res2[1]+m[3][3]*res3[1];

		az1[0]=m[0][0]*res[2]+m[0][1]*res1[2]+m[0][2]*res2[2]+m[0][3]*res3[2];
		az1[1]=m[1][0]*res[2]+m[1][1]*res1[2]+m[1][2]*res2[2]+m[1][3]*res3[2];
		az1[2]=m[2][0]*res[2]+m[2][1]*res1[2]+m[2][2]*res2[2]+m[2][3]*res3[2];
		az1[3]=m[3][0]*res[2]+m[3][1]*res1[2]+m[3][2]*res2[2]+m[3][3]*res3[2];


		res4[0]=pow(v,3)*ax1[0]+pow(v,2)*ax1[1]+v*ax1[2]+ax1[3];
		res4[1]=pow(v,3)*ay1[0]+pow(v,2)*ay1[1]+v*ay1[2]+ay1[3];
		res4[2]=pow(v,3)*az1[0]+pow(v,2)*az1[1]+v*az1[2]+az1[3];

}



void patchR(FILE *f_patch, FILE *f, int tess){

	int cont=0;
	int k,n_patch,n_vertices;
	int *patchs=NULL;
	float *vertices=NULL,*points=NULL;
	float x,y,z;

	fscanf(f_patch,"%d\n",&n_patch);
	patchs=(int*)malloc(16*n_patch*sizeof(int));
    
    for(int i=0;i<n_patch;i++){
		for(int j=0;j<15;j++){
			fscanf(f_patch,"%d, ",&k);
			patchs[cont++]=k;
		}
		fscanf(f_patch,"%d\n",&k);
		patchs[cont++]=k;
	}
    
	fscanf(f_patch,"%d\n",&n_vertices);
	vertices=(float*)malloc(3*n_vertices*sizeof(float));
	cont=0;
	while(fscanf(f_patch," %f, %f, %f\n",&x,&y,&z)!=EOF){
		vertices[cont++]=x;
		vertices[cont++]=y;
		vertices[cont++]=z;
	}

	for(int co = 0;co<n_patch;co++){
	for(int i=0; i<tess; i++){
	for(int j=0; j<tess; j++){
		getPoints(patchs,co,vertices,n_vertices,tess,i*1.0/tess, j*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

		getPoints(patchs,co,vertices,n_vertices,tess,(i+1)*1.0/tess, j*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

		getPoints(patchs,co,vertices,n_vertices,tess,(i+1)*1.0/tess, (j+1)*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

		getPoints(patchs,co,vertices,n_vertices,tess,(i+1)*1.0/tess, (j+1)*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

		getPoints(patchs,co,vertices,n_vertices,tess,i*1.0/tess, (j+1)*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

		getPoints(patchs,co,vertices,n_vertices,tess,i*1.0/tess, j*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch++;

	}
	}
	}

}


int main(int argc, char* argv[]) {
    
	FILE *f=NULL, *patch=NULL;

    ofstream outputFile;

    if(strcmp(argv[1],"patch")==0 && argc == 5){
    	outputFile.open(argv[argc-1]);

    	patch = fopen(argv[2],"r");
    	f = fopen(argv[argc-1],"w");

    	float tess = atoi(argv[3]);

    	patchR(patch,f,tess);

	vert.reserve( vertH.size() + vertV.size() ); // preallocate memory
	vert.insert( vert.end(), vertH.begin(), vertH.end() );
	vert.insert( vert.end(), vertV.begin(), vertV.end() );

	outputFile << nvPatch << "\n";

	outputFile << tess << "\n";

	for(int i=0;i<vert.size();i += 3){
		outputFile << vert.at(i);
		outputFile << " ";
		outputFile << vert.at(i+1);
		outputFile << " ";
		outputFile << vert.at(i+2);
		outputFile << "\n";
	}

    }

    else if(strcmp(argv[1],"box")==0 && argc==6) {
    outputFile.open(argv[argc-1]);
	float x = atof(argv[2]);
	float y = atof(argv[3]);
	float z = atof(argv[4]);

	outputFile << 36 << "\n";
	
	//lado
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << x << " " << 0 << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n";
	outputFile << x << " " << 0 << " " << 0 << "\n" << x << " " << y << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n";
	
	//lado
	outputFile << x << " " << 0 << " " << 0 << "\n" << x << " " << 0 << " " << -z << "\n" << x << " " << y << " " << 0 << "\n";
	outputFile << x << " " << 0 << " " << -z << "\n" << x << " " << y << " " << -z << "\n" << x << " " << y << " " << 0 << "\n";
	
	//lado
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n" << 0 << " " << 0 << " " << -z << "\n";
	outputFile << 0 << " " << y << " " << 0 << "\n" << 0 << " " << y << " " << -z << "\n" << 0 << " " << 0 << " " << -z << "\n";
	
	//atras
	outputFile << x << " " << 0 << " " << -z << "\n" << 0 << " " << 0 << " " << -z << "\n" << 0 << " " << y << " " << -z << "\n";
	outputFile << x << " " << 0 << " " << -z << "\n" << 0 << " " << y << " " << -z << "\n" << x << " " << y << " " << -z << "\n";
	
	//topo
	outputFile << 0 << " " << y << " " << -z << "\n" << 0 << " " << y << " " << 0 << "\n" << x << " " << y << " " << 0 << "\n";
	outputFile << 0 << " " << y << " " << -z << "\n" << x << " " << y << " " << 0 << "\n" << x << " " << y << " " << -z << "\n";
	
	//base
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << 0 << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << 0 << "\n";
	outputFile << 0 << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << 0 << "\n";




	//normais
	outputFile << 36 << "\n";

	//lado
	outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";
	outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";

	//lado
	outputFile << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n";
	outputFile << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n";

	//lado
	outputFile << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n";
	outputFile << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n";

	//atras
	outputFile << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n";
	outputFile << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n";

	//topo
	outputFile << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n";
	outputFile << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n";

	//base
	outputFile << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n";
	outputFile << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n";	





	printf("Done\n");
	outputFile.close();

    }
    else if (strcmp(argv[1],"box")==0 && argc==7) {
        outputFile.open(argv[argc-1]);
        float x = atof(argv[2]);
        float y = atof(argv[3]);
        float z = atof(argv[4]);
        int divisoes = atoi(argv[5]);
        
        outputFile << 36*(divisoes+1)*(divisoes+1) << "\n";
        
        for(int i = divisoes+1;i>0;i--){
            float x1 = (x/(divisoes + 1))*i;
            float xs1 = (x/(divisoes + 1))*(i-1);
            for(int j=divisoes+1;j>0;j--) {
            float ys1 = (y/(divisoes +1))*(j-1);
            float y1 = (y/(divisoes +1))*j;

            outputFile << xs1 << " " << ys1 << " " << 0 << "\n" << x1 << " " << ys1 << " " << 0 << "\n" << xs1 << " " << y1 << " " << 0 << "\n";
            outputFile << x1 << " " << ys1 << " " << 0 << "\n" << x1 << " " << y1 << " " << 0 << "\n" << xs1 << " " << y1 << " " << 0 << "\n";

            outputFile << x1 << " " << ys1 << " " << 0 << "\n" << x1 << " " << ys1 << " " << -z << "\n" << x1 << " " << y1 << " " << 0 << "\n";
            outputFile << x1 << " " << ys1 << " " << -z << "\n" << x1 << " " << y1 << " " << -z << "\n" << x1 << " " << y1 << " " << 0 << "\n";

            outputFile << xs1 << " " << ys1 << " " << 0 << "\n" << xs1 << " " << y1 << " " << 0 << "\n" << xs1 << " " << ys1 << " " << -z << "\n";
            outputFile << xs1 << " " << y1 << " " << 0 << "\n" << xs1 << " " << y1 << " " << -z << "\n" << xs1 << " " << ys1 << " " << -z << "\n";

            outputFile << x1 << " " << ys1 << " " << -z << "\n" << xs1 << " " << ys1 << " " << -z << "\n" << xs1 << " " << y1 << " " << -z << "\n";
            outputFile << x1 << " " << ys1 << " " << -z << "\n" << xs1 << " " << y1 << " " << -z << "\n" << x1 << " " << y1 << " " << -z << "\n";

            outputFile << xs1 << " " << y1 << " " << -z << "\n" << xs1 << " " << y1 << " " << 0 << "\n" << x1 << " " << y1 << " " << 0 << "\n";
            outputFile << xs1 << " " << y1 << " " << -z << "\n" << x1 << " " << y1 << " " << 0 << "\n" << x1 << " " << y1 << " " << -z << "\n";

            outputFile << xs1 << " " << ys1 << " " << 0 << "\n" << xs1 << " " << ys1 << " " << -z << "\n" << x1 << " " << ys1 << " " << 0 << "\n";
            outputFile << xs1 << " " << ys1 << " " << -z << "\n" << x1 << " " << ys1 << " " << -z << "\n" << x1 << " " << ys1 << " " << 0 << "\n";
            }
        }

        outputFile << 36*(divisoes+1)*(divisoes+1) << "\n";

        for(int i = divisoes+1;i>0;i--){
            for(int j=divisoes+1;j>0;j--) {
				//lado
				outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";
				outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";

				//lado
				outputFile << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n";
				outputFile << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n" << 1 << " " << 0 << " " << 0 << "\n";

				//lado
				outputFile << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n";
				outputFile << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n" << -1 << " " << 0 << " " << 0 << "\n";

				//atras
				outputFile << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n";
				outputFile << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n" << 0 << " " << 0 << " " << -1 << "\n";

				//topo
				outputFile << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n";
				outputFile << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n" << 0 << " " << 1 << " " << 0 << "\n";

				//base
				outputFile << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n";
				outputFile << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n" << 0 << " " << -1 << " " << 0 << "\n";	
            }
        }
        printf("Done\n");
        outputFile.close();}
    
    else if((strcmp(argv[1],"box")==0) && (argc!=6 || argc!=7)) cout << "Número de argumentos inválido" << "\n";
    
    if(strcmp(argv[1],"sphere")==0 && argc==6) {
    outputFile.open(argv[argc-1]);
	float stacks = atoi(argv[4]);
	float slices = atoi(argv[3]);
	float radius = atoi(argv[2]);
	
	outputFile << stacks*slices*6 << "\n";	//6 porque e 6 vertices por cada 2 triangulos

	for(int j=0;j<stacks;j++){
        	for(int i=0;i<slices;i++){
			//primeiro triangulo
			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j));

			textV.push_back(i*1.0/slices);
			textV.push_back(j*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j)),sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*j))/M_PI) - .5);	

			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j));

			textV.push_back((i+1)*1.0/slices);
			textV.push_back(j*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j)),sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*j))/M_PI) - .5);

			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));

			textV.push_back((i+1)*1.0/slices);
			textV.push_back((j+1)*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1))),sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*(j+1)))/M_PI) - .5);

			//segundo triangulo
			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));

			textV.push_back((i+1)*1.0/slices);
			textV.push_back((j+1)*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1))),sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1)))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*(j+1)))/M_PI) - .5);

			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*(j+1)));
			normalV.push_back(cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1)));	

			textV.push_back(i*1.0/slices);
			textV.push_back((j+1)*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1))),sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1)))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*(j+1)))/M_PI) - .5);

			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(sin((M_PI/2)-(M_PI/stacks)*j));
			normalV.push_back(cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j));

			textV.push_back(i*1.0/slices);
			textV.push_back(j*1.0/stacks);

			//textV.push_back((atan2((cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j)),sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j))/(2*M_PI)) + 0.5);
			//textV.push_back((asin(sin((M_PI/2)-(M_PI/stacks)*j))/M_PI) - .5);

		}
	}

	outputFile << stacks*slices*6 << "\n";
	for(int i=0;i<normalV.size();i+=3) outputFile << normalV.at(i) << " " << normalV.at(i+1) << " " << normalV.at(i+2) << "\n";

	outputFile << stacks*slices*6 << "\n";
	for(int i=0;i<textV.size();i+=2) outputFile << textV.at(i) << " " << textV.at(i+1) <<  "\n";	

	outputFile.close();		
    	printf("Done\n");
    }
    else if (strcmp(argv[1],"sphere")==0 && argc!=6) cout << "Número de argumentos inválido" << "\n";

    
    if(strcmp(argv[1],"cone")==0 && argc==7){
    outputFile.open(argv[argc-1]);
	float stacks = atof(argv[5]);
	float slices = atof(argv[4]);
	float radius = atof(argv[2]);
	float height = atof(argv[3]);

	outputFile << stacks*slices*6 + 3*slices << "\n";

	float a = 0.0f;
    	float passo = 2*M_PI / (float)slices;

    	for (int i = 0; i < slices; i++){
        float x = sin(a) * radius;
        float z = cos(a) * radius;
        float x1 = sin(a+passo) * radius;
        float z1 = cos(a+passo) * radius;
			outputFile << x << " " << 0 << " " << z << "\n";
			outputFile << 0 << " " << 0 << " " << 0 << "\n";
			outputFile << x1 << " " << 0 << " " << z1 << "\n";
       		a += passo;
       		normalV.push_back(0.0);
			normalV.push_back(-1.0);
			normalV.push_back(0.0);
       		normalV.push_back(0.0);
			normalV.push_back(-1.0);
			normalV.push_back(0.0);
       		normalV.push_back(0.0);
			normalV.push_back(-1.0);
			normalV.push_back(0.0);			
       	}

	for(int j=0;j<stacks;j++){
        	for(int i=0;i<slices;i++){
			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks)) * cos((2*M_PI/slices)*i);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*i));

			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*(i+1)));

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*(i+1)));

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*(i+1)));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*(i+1)));

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*i);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*i));

			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks))* cos((2*M_PI/slices)*i);
			outputFile << "\n";

			normalV.push_back(sin((2*M_PI/slices)*i));
			normalV.push_back(0.0);
			normalV.push_back(cos((2*M_PI/slices)*i));

		}
	}

	outputFile << stacks*slices*6 + 3*slices << "\n";
	for(int i=0;i<normalV.size();i+=3) outputFile << normalV.at(i) << " " << normalV.at(i+1) << " " << normalV.at(i+2) << "\n";
	
	//textura

	outputFile.close();		
    	printf("Done\n");

    }
    else if(strcmp(argv[1],"cone")==0 && argc!=7) cout << "Número de argumentos inválido" << "\n";

        if(strcmp(argv[1],"plane")==0 && argc==5) {
            outputFile.open(argv[argc-1]);
            float x = atof(argv[2]);
            float z = atof(argv[3]);
            
            outputFile << 6 << "\n";
            
            outputFile << x/2 << " " << 0 << " " << z/2 << "\n" << x/2 << " " << 0 << " " << -z/2 << "\n" << -x/2 << " " << 0 << " " << -z/2 << "\n";
            outputFile << -x/2 << " " << 0 << " " << -z/2 << "\n" << -x/2 << " " << 0 << " " << z/2 << "\n" << x/2 << " " << 0 << " " << z/2 << "\n";

            outputFile << 6 << "\n";

            outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";
            outputFile << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n" << 0 << " " << 0 << " " << 1 << "\n";            

            
            printf("Done\n");
            outputFile.close();

    } else if(strcmp(argv[1],"plane")==0 && argc!=5) cout << "Número de argumentos inválido" << "\n";
    

        if(!(strcmp(argv[1],"box")==0) && !(strcmp(argv[1],"plane")==0) && !(strcmp(argv[1],"sphere")==0) && !(strcmp(argv[1],"cone")==0) && !(strcmp(argv[1],"patch")==0)) cout << "Não é possível criar o modelo.\n";
    
}
