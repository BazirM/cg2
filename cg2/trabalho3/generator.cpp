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

// falta colocar a funcao que pega nesses vertices e define as curvas (getPoints) e depois falta passar para dentro do ficheiro

// criar um buffer a parte para o patches(para nao misturar), uma funcao do tipo drawCometa (ideia)

// é desenhado asseguir ao Sol no xml


float* getPoints(int *patchs, int n_patch, float *vertices, int n_vertices, int tess, float t, float v){

	float Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz,Dx,Dy,Dz,Ex,Ey,Ez,Fx,Fy,Fz,Gx,Gy,Gz,Hx,Hy,Hz,Ix,Iy,Iz,Jx,Jy,Jz,Kx,Ky,Kz,Lx,Ly,Lz,Mx,My,Mz,Nx,Ny,Nz,Ox,Oy,Oz,Px,Py,Pz;
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

        Ax = vertices[3*patchs[(16*k)]];         Ay = vertices[3*patchs[(16*k)]+1];     Az = vertices[3*patchs[(16*k)]+2];
        Bx = vertices[3*patchs[(16*k+1)]];       By = vertices[3*patchs[(16*k+1)]+1];   Bz = vertices[3*patchs[(16*k)+1]+2];
        Cx = vertices[3*patchs[(16*k+2)]];       Cy = vertices[3*patchs[(16*k+2)]+1];   Cz = vertices[3*patchs[(16*k)+2]+2];
        Dx = vertices[3*patchs[(16*k+3)]];       Dy = vertices[3*patchs[(16*k+3)]+1];   Dz = vertices[3*patchs[(16*k)+3]+2];
        Ex = vertices[3*patchs[(16*k+4)]];       Ey = vertices[3*patchs[(16*k+4)]+1];   Ez = vertices[3*patchs[(16*k)+4]+2];
        Fx = vertices[3*patchs[(16*k+5)]];       Fy = vertices[3*patchs[(16*k+5)]+1];   Fz = vertices[3*patchs[(16*k)+5]+2];
        Gx = vertices[3*patchs[(16*k+6)]];       Gy = vertices[3*patchs[(16*k+6)]+1];   Gz = vertices[3*patchs[(16*k)+6]+2];
        Hx = vertices[3*patchs[(16*k+7)]];       Hy = vertices[3*patchs[(16*k+7)]+1];   Hz = vertices[3*patchs[(16*k)+7]+2];
        Ix = vertices[3*patchs[(16*k+8)]];       Iy = vertices[3*patchs[(16*k+8)]+1];   Iz = vertices[3*patchs[(16*k)+8]+2];
        Jx = vertices[3*patchs[(16*k+9)]];       Jy = vertices[3*patchs[(16*k+9)]+1];   Jz = vertices[3*patchs[(16*k)+9]+2];
        Kx = vertices[3*patchs[(16*k+10)]];      Ky = vertices[3*patchs[(16*k+10)]+1];  Kz = vertices[3*patchs[(16*k)+10]+2];
        Lx = vertices[3*patchs[(16*k+11)]];      Ly = vertices[3*patchs[(16*k+11)]+1];  Lz = vertices[3*patchs[(16*k)+11]+2];
        Mx = vertices[3*patchs[(16*k+12)]];      My = vertices[3*patchs[(16*k+12)]+1];  Mz = vertices[3*patchs[(16*k)+12]+2];
        Nx = vertices[3*patchs[(16*k+13)]];      Ny = vertices[3*patchs[(16*k+13)]+1];  Nz = vertices[3*patchs[(16*k)+13]+2];
        Ox = vertices[3*patchs[(16*k+14)]];      Oy = vertices[3*patchs[(16*k+14)]+1];  Oz = vertices[3*patchs[(16*k)+14]+2];
        Px = vertices[3*patchs[(16*k+15)]];      Py = vertices[3*patchs[(16*k+15)]+1];  Pz = vertices[3*patchs[(16*k)+15]+2];


        ax[0]=m[0][0]*Ax+m[0][1]*Bx+m[0][2]*Cx+m[0][3]*Dx;
		ax[1]=m[1][0]*Ax+m[1][1]*Bx+m[1][2]*Cx+m[1][3]*Dx;
		ax[2]=m[2][0]*Ax+m[2][1]*Bx+m[2][2]*Cx+m[2][3]*Dx;
		ax[3]=m[3][0]*Ax+m[3][1]*Bx+m[3][2]*Cx+m[3][3]*Dx;
		
		ay[0]=m[0][0]*Ay+m[0][1]*By+m[0][2]*Cy+m[0][3]*Dy;
		ay[1]=m[1][0]*Ay+m[1][1]*By+m[1][2]*Cy+m[1][3]*Dy;
		ay[2]=m[2][0]*Ay+m[2][1]*By+m[2][2]*Cy+m[2][3]*Dy;
		ay[3]=m[3][0]*Ay+m[3][1]*By+m[3][2]*Cy+m[3][3]*Dy;

		az[0]=m[0][0]*Az+m[0][1]*Bz+m[0][2]*Cz+m[0][3]*Dz;
		az[1]=m[1][0]*Az+m[1][1]*Bz+m[1][2]*Cz+m[1][3]*Dz;
		az[2]=m[2][0]*Az+m[2][1]*Bz+m[2][2]*Cz+m[2][3]*Dz;
		az[3]=m[3][0]*Az+m[3][1]*Bz+m[3][2]*Cz+m[3][3]*Dz;

		res[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*Ex+m[0][1]*Fx+m[0][2]*Gx+m[0][3]*Hx;
		ax[1]=m[1][0]*Ex+m[1][1]*Fx+m[1][2]*Gx+m[1][3]*Hx;
		ax[2]=m[2][0]*Ex+m[2][1]*Fx+m[2][2]*Gx+m[2][3]*Hx;
		ax[3]=m[3][0]*Ex+m[3][1]*Fx+m[3][2]*Gx+m[3][3]*Hx;
		
		ay[0]=m[0][0]*Ey+m[0][1]*Fy+m[0][2]*Gy+m[0][3]*Hy;
		ay[1]=m[1][0]*Ey+m[1][1]*Fy+m[1][2]*Gy+m[1][3]*Hy;
		ay[2]=m[2][0]*Ey+m[2][1]*Fy+m[2][2]*Gy+m[2][3]*Hy;
		ay[3]=m[3][0]*Ey+m[3][1]*Fy+m[3][2]*Gy+m[3][3]*Hy;

		az[0]=m[0][0]*Ez+m[0][1]*Fz+m[0][2]*Gz+m[0][3]*Hz;
		az[1]=m[1][0]*Ez+m[1][1]*Fz+m[1][2]*Gz+m[1][3]*Hz;
		az[2]=m[2][0]*Ez+m[2][1]*Fz+m[2][2]*Gz+m[2][3]*Hz;
		az[3]=m[3][0]*Ez+m[3][1]*Fz+m[3][2]*Gz+m[3][3]*Hz;

		res1[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res1[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res1[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*Ix+m[0][1]*Jx+m[0][2]*Kx+m[0][3]*Lx;
		ax[1]=m[1][0]*Ix+m[1][1]*Jx+m[1][2]*Kx+m[1][3]*Lx;
		ax[2]=m[2][0]*Ix+m[2][1]*Jx+m[2][2]*Kx+m[2][3]*Lx;
		ax[3]=m[3][0]*Ix+m[3][1]*Jx+m[3][2]*Kx+m[3][3]*Lx;
		
		ay[0]=m[0][0]*Iy+m[0][1]*Jy+m[0][2]*Ky+m[0][3]*Ly;
		ay[1]=m[1][0]*Iy+m[1][1]*Jy+m[1][2]*Ky+m[1][3]*Ly;
		ay[2]=m[2][0]*Iy+m[2][1]*Jy+m[2][2]*Ky+m[2][3]*Ly;
		ay[3]=m[3][0]*Iy+m[3][1]*Jy+m[3][2]*Ky+m[3][3]*Ly;

		az[0]=m[0][0]*Iz+m[0][1]*Jz+m[0][2]*Kz+m[0][3]*Lz;
		az[1]=m[1][0]*Iz+m[1][1]*Jz+m[1][2]*Kz+m[1][3]*Lz;
		az[2]=m[2][0]*Iz+m[2][1]*Jz+m[2][2]*Kz+m[2][3]*Lz;
		az[3]=m[3][0]*Iz+m[3][1]*Jz+m[3][2]*Kz+m[3][3]*Lz;

		res2[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
		res2[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
		res2[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

		ax[0]=m[0][0]*Mx+m[0][1]*Nx+m[0][2]*Ox+m[0][3]*Px;
		ax[1]=m[1][0]*Mx+m[1][1]*Nx+m[1][2]*Ox+m[1][3]*Px;
		ax[2]=m[2][0]*Mx+m[2][1]*Nx+m[2][2]*Ox+m[2][3]*Px;
		ax[3]=m[3][0]*Mx+m[3][1]*Nx+m[3][2]*Ox+m[3][3]*Px;
		
		ay[0]=m[0][0]*My+m[0][1]*Ny+m[0][2]*Oy+m[0][3]*Py;
		ay[1]=m[1][0]*My+m[1][1]*Ny+m[1][2]*Oy+m[1][3]*Py;
		ay[2]=m[2][0]*My+m[2][1]*Ny+m[2][2]*Oy+m[2][3]*Py;
		ay[3]=m[3][0]*My+m[3][1]*Ny+m[3][2]*Oy+m[3][3]*Py;

		az[0]=m[0][0]*Mz+m[0][1]*Nz+m[0][2]*Oz+m[0][3]*Pz;
		az[1]=m[1][0]*Mz+m[1][1]*Nz+m[1][2]*Oz+m[1][3]*Pz;
		az[2]=m[2][0]*Mz+m[2][1]*Nz+m[2][2]*Oz+m[2][3]*Pz;
		az[3]=m[3][0]*Mz+m[3][1]*Nz+m[3][2]*Oz+m[3][3]*Pz;

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



void patchR(FILE *f_patch, FILE *f, int tess){ // guarda o numero de patches, os vertices correspondentes das patches (patch)
	// e as coordenadas dos vertices de controlo(vertices), já funciona 

	// f é o ficheiro destinho

	//mudar as variaveis e (se houver tempo) mudar a funcao em sí

	int i=0,j=0,v=0,avanco,k,n_patch,n_vertices, *patchs=NULL;
	float *vertices=NULL,*points=NULL,x,y,z;

	fscanf(f_patch,"%d\n",&n_patch);
	patchs=(int*)malloc(16*n_patch*sizeof(int));
    
	while(i<n_patch){
		for(j=0;j<15;j++){
			fscanf(f_patch,"%d, ",&k);
			patchs[v++]=k;
		}
		fscanf(f_patch,"%d\n",&k);
		patchs[v++]=k;
		i++;
	}
    
	fscanf(f_patch,"%d\n",&n_vertices);
	vertices=(float*)malloc(3*n_vertices*sizeof(float));
	v=0;
	while(fscanf(f_patch," %f, %f, %f\n",&x,&y,&z)!=EOF){
		vertices[v++]=x;
		vertices[v++]=y;
		vertices[v++]=z;
	}

	for(int co = 0;co<n_patch;co++){
	for(int i=0; i<=tess; i++){
	for(int j=0; j<=tess; j++){
		getPoints(patchs,co,vertices,n_vertices,tess,i*1.0/tess, j*1.0/tess);
		vertV.push_back(res4[0]);
		vertV.push_back(res4[1]);
		vertV.push_back(res4[2]);
		nvPatch ++;
	}

	for(int j=0; j<=tess; j++){
		getPoints(patchs,co,vertices,n_vertices,tess,j*1.0/tess, i*1.0/tess);
		vertH.push_back(res4[0]);
		vertH.push_back(res4[1]);
		vertH.push_back(res4[2]);
		nvPatch ++;
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
	
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << x << " " << 0 << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n";
	outputFile << x << " " << 0 << " " << 0 << "\n" << x << " " << y << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n";
	outputFile << x << " " << 0 << " " << 0 << "\n" << x << " " << 0 << " " << -z << "\n" << x << " " << y << " " << 0 << "\n";
	outputFile << x << " " << 0 << " " << -z << "\n" << x << " " << y << " " << -z << "\n" << x << " " << y << " " << 0 << "\n";
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << 0 << " " << y << " " << 0 << "\n" << 0 << " " << 0 << " " << -z << "\n";
	outputFile << 0 << " " << y << " " << 0 << "\n" << 0 << " " << y << " " << -z << "\n" << 0 << " " << 0 << " " << -z << "\n";
	outputFile << x << " " << 0 << " " << -z << "\n" << 0 << " " << 0 << " " << -z << "\n" << 0 << " " << y << " " << -z << "\n";
	outputFile << x << " " << 0 << " " << -z << "\n" << 0 << " " << y << " " << -z << "\n" << x << " " << y << " " << -z << "\n";
	outputFile << 0 << " " << y << " " << -z << "\n" << 0 << " " << y << " " << 0 << "\n" << x << " " << y << " " << 0 << "\n";
	outputFile << 0 << " " << y << " " << -z << "\n" << x << " " << y << " " << 0 << "\n" << x << " " << y << " " << -z << "\n";
	outputFile << 0 << " " << 0 << " " << 0 << "\n" << 0 << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << 0 << "\n";
	outputFile << 0 << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << -z << "\n" << x << " " << 0 << " " << 0 << "\n";

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
        printf("Done\n");
        outputFile.close();}
    
    else if((strcmp(argv[1],"box")==0) && (argc!=6 || argc!=7)) cout << "Número de argumentos inválido" << "\n";
    
    if(strcmp(argv[1],"sphere")==0 && argc==6) {
    outputFile.open(argv[argc-1]);
	float stacks = atoi(argv[4]);
	float slices = atoi(argv[3]);
	float radius = atoi(argv[2]);
	
	outputFile << stacks*slices*6 << "\n";

	for(int j=0;j<stacks;j++){
        	for(int i=0;i<slices;i++){
			//primeiro triangulo
			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

			//segundo triangulo
			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

			outputFile << radius * sin((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*j);
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*i) * cos((M_PI/2)-(M_PI/stacks)*j);
			outputFile << "\n";

			outputFile << radius * sin((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * sin((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << " ";
			outputFile << radius * cos((2*M_PI/slices)*(i+1)) * cos((M_PI/2)-(M_PI/stacks)*(j+1));
			outputFile << "\n";

		}
	}
	

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
        
        a += passo;}

	for(int j=0;j<stacks;j++){
        	for(int i=0;i<slices;i++){
			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks)) * cos((2*M_PI/slices)*i);
			outputFile << "\n";

			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*(i+1));
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*(i+1));
			outputFile << "\n";

			outputFile << (radius - (radius*(j+1)/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*(j+1)/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*(j+1)/stacks)) * cos((2*M_PI/slices)*i);
			outputFile << "\n";

			outputFile << (radius - (radius*j/stacks)) * sin((2*M_PI/slices)*i);
			outputFile << " ";
			outputFile << (height*j/stacks);
			outputFile << " ";
			outputFile << (radius - (radius*j/stacks))* cos((2*M_PI/slices)*i);
			outputFile << "\n";

		}
	}
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

            
            printf("Done\n");
            outputFile.close();

    } else if(strcmp(argv[1],"plane")==0 && argc!=5) cout << "Número de argumentos inválido" << "\n";
    

        if(!(strcmp(argv[1],"box")==0) && !(strcmp(argv[1],"plane")==0) && !(strcmp(argv[1],"sphere")==0) && !(strcmp(argv[1],"cone")==0) && !(strcmp(argv[1],"patch")==0)) cout << "Não é possível criar o modelo.\n";
    
}
