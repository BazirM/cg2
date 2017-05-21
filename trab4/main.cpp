#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tinyxml.h"
#include "tinystr.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <IL/il.h>

using namespace std;
#define POINT_COUNT 5
float alfa = M_PI/2, beta = M_PI/6, raio = 200.0;
vector< std::vector<long double> > vert;
float y[3]={0,-1,0};
vector<std::string> modelos;
vector<float> pontosT;
vector<float> pontosLuz;
vector<GLfloat> textP;
int nvertices, nvertices2, tess, cont, contSoma, nverticesN, nverticesT, nverticesNP;
float timer, ang, tempo = 1.0, temp = 0.0;

int specular, ambient, emission, diffuse, diffuseL, specularL, emissionL, ambientL;

int nv = 0;
int nvp = 0;

	int frame = 0;

vector<GLfloat> norm;
vector<GLfloat> normP;
vector<GLfloat> normT;
vector<std::string> strLuzes;
vector<std::string> strLuzesMod;

vector<GLfloat> vertices, verticesTP;

GLuint buffer, buffer2, buffer3, buffer4, buffer5, buffer6;
GLuint texID;


void normalize(float *a) { 
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]); 
	a[0] = a[0]/l; 
	a[1] = a[1]/l; 
	a[2] = a[2]/l;
}

void cross(float *a, float *b, float *res) { 
	res[0] = a[1]*b[2] - a[2]*b[1]; 
	res[1] = a[2]*b[0] - a[0]*b[2]; 
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {
	m[0] = x[0];
	m[1] = x[1]; 
	m[2] = x[2]; 
	m[3] = 0; 
	m[4] = y[0]; 
	m[5] = y[1];
	m[6] = y[2];
	m[7] = 0;
	m[8] = z[0]; 
	m[9] = z[1];
	m[10] = z[2];
	m[11] = 0; 
	m[12] = 0;
	m[13] = 0; 
	m[14] = 0; 
	m[15] = 1;
}

void getCatmullRomPoint(float t, int *indices, float *res,float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
						
	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
	deriv[0] = 0.0; deriv[1] = 0.0; deriv[2] = 0.0;	
	float ax[4];
	float ay[4];
	float az[4];

	ax[0]=m[0][0]*pontosT[indices[0]*3+0]+m[0][1]*pontosT[indices[1]*3+0]+m[0][2]*pontosT[indices[2]*3+0]+m[0][3]*pontosT[indices[3]*3+0];
	ax[1]=m[1][0]*pontosT[indices[0]*3+0]+m[1][1]*pontosT[indices[1]*3+0]+m[1][2]*pontosT[indices[2]*3+0]+m[1][3]*pontosT[indices[3]*3+0];
	ax[2]=m[2][0]*pontosT[indices[0]*3+0]+m[2][1]*pontosT[indices[1]*3+0]+m[2][2]*pontosT[indices[2]*3+0]+m[2][3]*pontosT[indices[3]*3+0];
	ax[3]=m[3][0]*pontosT[indices[0]*3+0]+m[3][1]*pontosT[indices[1]*3+0]+m[3][2]*pontosT[indices[2]*3+0]+m[3][3]*pontosT[indices[3]*3+0];

	ay[0]=m[0][0]*pontosT[indices[0]*3+1]+m[0][1]*pontosT[indices[1]*3+1]+m[0][2]*pontosT[indices[2]*3+1]+m[0][3]*pontosT[indices[3]*3+1];
	ay[1]=m[1][0]*pontosT[indices[0]*3+1]+m[1][1]*pontosT[indices[1]*3+1]+m[1][2]*pontosT[indices[2]*3+1]+m[1][3]*pontosT[indices[3]*3+1];
	ay[2]=m[2][0]*pontosT[indices[0]*3+1]+m[2][1]*pontosT[indices[1]*3+1]+m[2][2]*pontosT[indices[2]*3+1]+m[2][3]*pontosT[indices[3]*3+1];
	ay[3]=m[3][0]*pontosT[indices[0]*3+1]+m[3][1]*pontosT[indices[1]*3+1]+m[3][2]*pontosT[indices[2]*3+1]+m[3][3]*pontosT[indices[3]*3+1];

	az[0]=m[0][0]*pontosT[indices[0]*3+2]+m[0][1]*pontosT[indices[1]*3+2]+m[0][2]*pontosT[indices[2]*3+2]+m[0][3]*pontosT[indices[3]*3+2];
	az[1]=m[1][0]*pontosT[indices[0]*3+2]+m[1][1]*pontosT[indices[1]*3+2]+m[1][2]*pontosT[indices[2]*3+2]+m[1][3]*pontosT[indices[3]*3+2];
	az[2]=m[2][0]*pontosT[indices[0]*3+2]+m[2][1]*pontosT[indices[1]*3+2]+m[2][2]*pontosT[indices[2]*3+2]+m[2][3]*pontosT[indices[3]*3+2];
	az[3]=m[3][0]*pontosT[indices[0]*3+2]+m[3][1]*pontosT[indices[1]*3+2]+m[3][2]*pontosT[indices[2]*3+2]+m[3][3]*pontosT[indices[3]*3+2];	

	// resultado final do produto de matrizes
	res[0]=pow(t,3)*ax[0]+pow(t,2)*ax[1]+t*ax[2]+ax[3];
	res[1]=pow(t,3)*ay[0]+pow(t,2)*ay[1]+t*ay[2]+ay[3];
	res[2]=pow(t,3)*az[0]+pow(t,2)*az[1]+t*az[2]+az[3];

	deriv[0]=3*pow(t,2)*ax[0]+2*t*ax[1]+ax[2];
	deriv[1]=3*pow(t,2)*ay[0]+2*t*ay[1]+ay[2];
	deriv[2]=3*pow(t,2)*az[0]+2*t*az[1]+az[2];
}

void getGlobalCatmullRomPoint(float gt, float *res, float *deriv) {

	float t = gt * cont; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = ((index + cont-1)%cont) + contSoma;	
	indices[1] = ((indices[0]+1)%cont) + contSoma;
	indices[2] = ((indices[1]+1)%cont) + contSoma; 
	indices[3] = ((indices[2]+1)%cont) + contSoma;

	getCatmullRomPoint(t, indices, res, deriv);
}

void renderCatmullRomCurve() {
// desenhar a curva usando segmentos de reta - GL_LINE_LOOP
	float res[3];
	float deriv[3];
	
	//gera a linha a partir dos pontos gerados acima
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<100; i++){
		getGlobalCatmullRomPoint(i/100.0,res,deriv);
		glVertex3f(res[0],res[1],res[2]);
	}
	glEnd();
}

void changeSize(int w, int h) {
    
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;
    
    // compute window's aspect ratio
    float ratio = w * 1.0 / h;
    
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char c, int xx, int yy) {
  switch (c){
  case 'q': raio=raio+10.0; break;
  case 'e': raio=raio-10.0; break;
  case 'w': if((beta+0.1<M_PI/2) && (beta+0.1>-M_PI/2)) beta+=0.1; break;
  case 's': if((beta-0.1<M_PI/2) && (beta-0.1>-M_PI/2)) beta-=0.1; break;
  case 'm': alfa+=0.1; break;
  case 'n': alfa-=0.1; break;
  default: break;
  }
  glutPostRedisplay();
}

void desenhaModelo(int v, int mv){

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer4);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER,buffer5);
	glTexCoordPointer(2,GL_FLOAT,0,0);
(
	glDrawArrays(GL_TRIANGLES, mv, (mv + v)));

}

void desenhaTeap(int v, int mv){

	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer3);
	glNormalPointer(GL_FLOAT, 0, 0);	

	glBindBuffer(GL_ARRAY_BUFFER,buffer6);
	glTexCoordPointer(2,GL_FLOAT,0,0);


	glDrawArrays(GL_TRIANGLES, mv, (mv + v));

}


void prepareModels(){

	glGenBuffers(1,&buffer);
	glGenBuffers(1,&buffer2);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, verticesTP.size() * sizeof(float), &verticesTP[0], GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);

}

void prepareNormals(){

	glGenBuffers(1,&buffer3);

	glBindBuffer(GL_ARRAY_BUFFER, buffer3);
	glBufferData(GL_ARRAY_BUFFER, norm.size() * sizeof(float), &norm[0], GL_STATIC_DRAW);
	
	glGenBuffers(1,&buffer4);

	glBindBuffer(GL_ARRAY_BUFFER, buffer4);
	glBufferData(GL_ARRAY_BUFFER, normP.size() * sizeof(float), &normP[0], GL_STATIC_DRAW);

	glEnableClientState(GL_NORMAL_ARRAY);

}

void prepareTexturas(){

	glGenBuffers(1, &buffer5);
	glBindBuffer(GL_ARRAY_BUFFER, buffer5);
	glBufferData(GL_ARRAY_BUFFER, normT.size() * sizeof(float), &normT[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffer6);
	glBindBuffer(GL_ARRAY_BUFFER, buffer6);
	glBufferData(GL_ARRAY_BUFFER, textP.size() * sizeof(float), &textP[0], GL_STATIC_DRAW);


	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
}


void renderScene(void) {

	static float t = 0;
	float res[3];
	float deriv[3];
	float m[16]; 
	float z[3];

    float amM[3];
    float emiM[3];
    float difM[3];
    float specM[3];  

	contSoma = 0;
	cont = 0;

	specular = 0;
	diffuse = 0;
	emission = 0;
	ambient = 0;

	specularL = 0;
	diffuseL = 0;
	emissionL = 0;
	ambientL = 0;

	nv = 0;


	nv = 0;
	nvp = 0;

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the camera
    glLoadIdentity();
    gluLookAt(raio*sin(alfa)*cos(beta),raio*sin(beta),raio*cos(beta)*cos(alfa),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

	glEnable(GL_COLOR_MATERIAL);

    for(int i=0;i<modelos.size();){
		if(strcmp("group",modelos.at(i).c_str())==0){
			glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			i++;
		}
		
		else if(strcmp("/group",modelos.at(i).c_str())==0){
			glPopMatrix();
			i++;
		}

		else if(strcmp("translate",modelos.at(i).c_str())==0){
			contSoma = contSoma + cont;
			timer = glutGet(GLUT_ELAPSED_TIME);
			tempo = atof(modelos.at(i+1).c_str());
			cont = atoi(modelos.at(i+2).c_str());
			renderCatmullRomCurve();
			getGlobalCatmullRomPoint(timer/(tempo*1000),res,deriv);
			normalize(deriv);
			cross(deriv,y,z);
			normalize(z);
			cross(z,deriv,y);
			glTranslatef(res[0],res[1],res[2]);
			buildRotMatrix(deriv,y,z,m);
			glMultMatrixf(m);
			i+=3;
		}

		else if(strcmp("rotate",modelos.at(i).c_str())==0){
			timer = glutGet(GLUT_ELAPSED_TIME);
			temp = atof(modelos.at(i+1).c_str());
			float x = atof(modelos.at(i+2).c_str());
			float y = atof(modelos.at(i+3).c_str());
			float z = atof(modelos.at(i+4).c_str());
			glRotatef(timer/(temp*1000)*360,x,y,z);
			i+=5;
		}

		else if(strcmp("rotateA",modelos.at(i).c_str())==0){
			float ang = atof(modelos.at(i+1).c_str());
			float x = atof(modelos.at(i+2).c_str());
			float y = atof(modelos.at(i+3).c_str());
			float z = atof(modelos.at(i+4).c_str());
			glRotatef(ang,x,y,z);
			i+=5;
		}

		else if(strcmp("scale",modelos.at(i).c_str())==0){
			float sx = atof(modelos.at(i+1).c_str());
			float sy = atof(modelos.at(i+2).c_str());
			float sz = atof(modelos.at(i+3).c_str());
			glScalef(sx,sy,sz);
			i+=4;
		}

		else if(strcmp("ring",modelos.at(i).c_str())==0){
            		float inr = atof(modelos.at(i+1).c_str());
            		float outr = atof(modelos.at(i+2).c_str());
            		int nside = atoi(modelos.at(i+3).c_str());
            		int ring = atoi(modelos.at(i+4).c_str());
            		glutSolidTorus(inr,outr,nside,ring);
            		i+=5;
        	}

        else if(strcmp("lights",modelos.at(i).c_str())==0){
        	int acum = 0;	//apontador para o inicio do array das luzes
        	float am[3];
        	float emi[3];
        	float dif[3];
        	float spec[3];        	
        	float nluzes = atof(modelos.at(i+1).c_str());
        	for(int j=0;j<nluzes;j++){
        		glEnable(GL_LIGHT0+j);
        		float c[4] = { pontosLuz.at((j*4)+1), pontosLuz.at((j*4)+2), pontosLuz.at((j*4)+3), pontosLuz.at((j*4)+0) };
        		glLightfv(GL_LIGHT0+j, GL_POSITION, c);
        		float nComp = atof(modelos.at(i+2+j).c_str());
        		for(int k=acum;k<acum+nComp;){
        			if(strcmp("ambient",strLuzes.at(k).c_str()) == 0){
        				am[0] = atof(strLuzes.at(k+1).c_str());
        				am[1] = atof(strLuzes.at(k+2).c_str());
        				am[2] = atof(strLuzes.at(k+3).c_str());
        				glLightfv(GL_LIGHT0+j, GL_AMBIENT, am);
        			}
        			else if(strcmp("emission",strLuzes.at(k).c_str()) == 0){
        				emi[0] = atof(strLuzes.at(k+1).c_str());
        				emi[1] = atof(strLuzes.at(k+2).c_str());
        				emi[2] = atof(strLuzes.at(k+3).c_str());
        				glLightfv(GL_LIGHT0+j, GL_EMISSION, emi);
        			}
        			else if(strcmp("specular",strLuzes.at(k).c_str()) == 0){
        				dif[0] = atof(strLuzes.at(k+1).c_str());
        				dif[1] = atof(strLuzes.at(k+2).c_str());
        				dif[2] = atof(strLuzes.at(k+3).c_str());
        				glLightfv(GL_LIGHT0+j, GL_SPECULAR, dif);
        			}
        			else if(strcmp("diffuse",strLuzes.at(k).c_str()) == 0){
        				spec[0] = atof(strLuzes.at(k+1).c_str());
        				spec[1] = atof(strLuzes.at(k+2).c_str());
        				spec[2] = atof(strLuzes.at(k+3).c_str());
        				glLightfv(GL_LIGHT0+j, GL_DIFFUSE, spec);
        			}
        			k+=4;
        		}
        		acum += nComp;
        	}
        	i+=2+nluzes;
        }

        else if(strcmp("texture",modelos.at(i).c_str())==0){
        	glEnable(GL_TEXTURE_2D);	// com o disable depois do group para nao misturar texturas
        	int idTextura = atoi(modelos.at(i+1).c_str());
        	glBindTexture(GL_TEXTURE_2D, idTextura);
        	i+=2;
        }


		else if(strcmp("color",modelos.at(i).c_str())==0){  
            	int num = atoi(modelos.at(i+1).c_str());
        		for(int k=i+2;k<i+2+num;){
        			if(strcmp("ambient",modelos.at(k).c_str()) == 0){
        				amM[0] = atof(modelos.at(k+1).c_str())/255.0;
        				amM[1] = atof(modelos.at(k+2).c_str())/255.0;
        				amM[2] = atof(modelos.at(k+3).c_str())/255.0;
						glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amM);
        			}
        			else if(strcmp("emission",modelos.at(k).c_str()) == 0){
        				emiM[0] = atof(modelos.at(k+1).c_str())/255.0;
        				emiM[1] = atof(modelos.at(k+2).c_str())/255.0;
        				emiM[2] = atof(modelos.at(k+3).c_str())/255.0;
						glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiM);
        			}
        			else if(strcmp("specular",modelos.at(k).c_str()) == 0){
        				specM[0] = atof(modelos.at(k+1).c_str())/255.0;
        				specM[1] = atof(modelos.at(k+2).c_str())/255.0;
        				specM[2] = atof(modelos.at(k+3).c_str())/255.0;
						glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specM);
						glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        			}
        			else if(strcmp("diffuse",modelos.at(k).c_str()) == 0){
        				difM[0] = atof(modelos.at(k+1).c_str())/255.0;
        				difM[1] = atof(modelos.at(k+2).c_str())/255.0;
        				difM[2] = atof(modelos.at(k+3).c_str())/255.0;
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difM);
        			}
        				k+=4;
        		}
            	i+=num+2;
		}

		else if(strcmp("patch",modelos.at(i).c_str())==0){
			desenhaTeap(atoi(modelos.at(i+1).c_str()), nvp);
			nvp += atoi(modelos.at(i+1).c_str());
		 	i=i+2;
		 	GLfloat r_emission[4] = {0.0, 0.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, r_emission);
	     }

		else if(strcmp("model",modelos.at(i).c_str())==0){
			desenhaModelo(atoi(modelos.at(i+1).c_str()), nv);
			nv += atoi(modelos.at(i+1).c_str());
		 	i=i+2;
		 	GLfloat r_emission[4] = {0.0, 0.0, 0.0, 1.0};
		 	GLfloat r_specular[4] = {0.0, 0.0, 0.0, 1.0};
		 	GLfloat r_ambient[4] = {0.2, 0.2, 0.2, 1.0};
		 	GLfloat r_diffuse[4] = {0.8, 0.8, 0.8, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, r_emission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, r_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, r_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, r_specular);
	     }
    }

    // End of frame
    glutSwapBuffers();
}





void calcularNormalTriangulo(float *a, float *b, float *c, float *res){
	float U[3] = { b[0] - a[0], b[1] - a[1], b[2] - a[2]};
	float V[3] = { c[0] - a[0], c[1] - a[1], c[2] - a[2]};

	cross(U,V,res);


}


int loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}


void lerXML(TiXmlElement* e){

	//char buff[15];
	const char* pAttrib;
	const char* pAttrib2;
	const char* pAttrib3;
	const char* l[4] = {"type", "posX", "posY", "posZ"};
	const char* s[3] = {"X", "Y", "Z"};
	const char* t[4] = {"axisX", "axisY", "axisZ"};
	const char* mod[13] = {"file", "diffR", "diffG", "diffB", "specR", "specG", "specB", "emissR", "emissG", "emissB", "ambR", "ambG", "ambB"};

	int nElems = 0;


	while(e){				
			if(strcmp("group",e->Value()) == 0){
				if(e==NULL) printf("Erro no group.\n");
				else{ modelos.push_back(e->Value()); lerXML(e->FirstChildElement()); modelos.push_back("/group"); e=e->NextSiblingElement(); }
			}

			else if(strcmp("lights",e->Value()) == 0){
				int n_luzes = 0;
				int n_prop = 0;
				TiXmlElement* n;
				char str[15];
				if(e==NULL) printf("Erro no scale.\n");
				modelos.push_back(e->Value());
				TiXmlElement* m = e->FirstChildElement("light");
				while(m){
					n_luzes++;
					pAttrib = m->Attribute(l[0]);
					if(strcmp(pAttrib,"point") == 0) pontosLuz.push_back(1.0);
					else pontosLuz.push_back(0.0);
					for(int i=1;i<4;i++){
						pAttrib = m->Attribute(l[i]);
						if(pAttrib)
							pontosLuz.push_back(atof(pAttrib));
						else pontosLuz.push_back(0.0);
					}
					n = m->FirstChildElement("ambient");
					if(n!=NULL){
							strLuzes.push_back("ambient");
							pAttrib=n->Attribute("r");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("g");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("b");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
					}
					n = m->FirstChildElement("diffuse");
					if(n!= NULL){
							strLuzes.push_back("diffuse");
							pAttrib=n->Attribute("r");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("g");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("b");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
					}
					n = m->FirstChildElement("specular");
					if(n!= NULL){
							strLuzes.push_back("specular");
							pAttrib=n->Attribute("r");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("g");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("b");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
					}
					n = m->FirstChildElement("emission");
					if(n!= NULL){
							strLuzes.push_back("emission");
							pAttrib=n->Attribute("r");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("g");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
							pAttrib=n->Attribute("b");
							if(pAttrib)
								strLuzes.push_back(pAttrib);
							else strLuzes.push_back("0.0");
					}
					strLuzes.push_back("|");	//para separar as componentes de cada luz
					m=m->NextSiblingElement();
					}
				sprintf(str, "%d", n_luzes);
				modelos.push_back(str);
				int cont = 0;
				for(int i=0;i<strLuzes.size();i++){
					if(strLuzes.at(i) == "|"){
						strLuzes.erase(strLuzes.begin() + i);
						sprintf(str, "%d", cont);
						modelos.push_back(str);
						cont = 0;
						i--;
					}
					else cont++;
				}
				e=e->NextSiblingElement();
			}
				
			else if(strcmp("models",e->Value()) == 0){
				strLuzesMod.clear();
				char buff[15];
				int nPropM = 0;
				if(e==NULL) printf("Erro no models.\n");
				TiXmlElement* m = e->FirstChildElement("model");
				pAttrib = m->Attribute("texture");
				if(pAttrib){
					unsigned int texId = loadTexture(pAttrib);
					sprintf(buff, "%d", texId);
					modelos.push_back("texture");
					modelos.push_back(buff);
					//puxar o "texture" e o valor do texId
				}
				while(m){
					modelos.push_back("color");
					for(int r=1;r<13;r+=3){
						pAttrib = m->Attribute(mod[r]);
						pAttrib2 = m->Attribute(mod[r+1]);
						pAttrib3 = m->Attribute(mod[r+2]);
						if(!(pAttrib || pAttrib2 || pAttrib3)){ }
						else{
							if(r==1) strLuzesMod.push_back("diffuse");
							if(r==4) strLuzesMod.push_back("specular");
							if(r==7) strLuzesMod.push_back("emission");
							if(r==10) strLuzesMod.push_back("ambient");
							if(pAttrib)
								strLuzesMod.push_back(pAttrib);
							else strLuzesMod.push_back("0.0");
							if(pAttrib2)
								strLuzesMod.push_back(pAttrib2);
							else strLuzesMod.push_back("0.0");
							if(pAttrib3)
								strLuzesMod.push_back(pAttrib3);
							else strLuzesMod.push_back("0.0");
							nPropM += 4;
						}
					}
    				sprintf(buff, "%d", nPropM);
    				modelos.push_back(buff);
					for(int k=0; k<strLuzesMod.size(); k++){
						modelos.push_back(strLuzesMod.at(k));
					}
					modelos.push_back(m->Value());
					long double p1,p2,p3,p4,p5,p6,p7,p8,p9;
					ifstream fich;
					fich.open(m->Attribute(mod[0]));
					if (fich.is_open()){
    				fich >> nvertices;
    				sprintf(buff, "%d", nvertices);
    				modelos.push_back(buff);
        			for(int k = 0; k < nvertices; k++){
					fich >> p1;
					fich >> p2;
					fich >> p3;
					vertices.push_back(p1);
					vertices.push_back(p2);
					vertices.push_back(p3);

					}
					//normal
    				fich >> nverticesN;
        			for(int k = 0; k < nverticesN; k++){
        				fich >> p1;
						fich >> p2;
						fich >> p3;
						normP.push_back(p1);
						normP.push_back(p2);
						normP.push_back(p3);
					}
					fich >> nverticesT;
        			for(int k = 0; k < nverticesT; k++){
        				fich >> p1;
						fich >> p2;
						//fich >> p3;
						normT.push_back(p1);
						normT.push_back(p2);
						//normT.push_back(p3);
					}
		     		}
		    	 	fich.close();
					m=m->NextSiblingElement();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("patches",e->Value()) == 0){
				char buff2[15];
				strLuzesMod.clear();
				char buff[15];
				int nPropM = 0;
				if(e==NULL) printf("Erro no patches.\n");
				TiXmlElement* m = e->FirstChildElement("patch");
				while(m){
					modelos.push_back("color");
						for(int r=1;r<13;r+=3){
						pAttrib = m->Attribute(mod[r]);
						pAttrib2 = m->Attribute(mod[r+1]);
						pAttrib3 = m->Attribute(mod[r+2]);
						if(!(pAttrib || pAttrib2 || pAttrib3)){ }
						else{
							if(r==1) strLuzesMod.push_back("diffuse");
							if(r==4) strLuzesMod.push_back("specular");
							if(r==7) strLuzesMod.push_back("emission");
							if(r==10) strLuzesMod.push_back("ambient");
							if(pAttrib)
								strLuzesMod.push_back(pAttrib);
							else strLuzesMod.push_back("0.0");
							if(pAttrib2)
								strLuzesMod.push_back(pAttrib2);
							else strLuzesMod.push_back("0.0");
							if(pAttrib3)
								strLuzesMod.push_back(pAttrib3);
							else strLuzesMod.push_back("0.0");
							nPropM += 4;
						}
					}
			    	sprintf(buff, "%d", nPropM);
    				modelos.push_back(buff);
					for(int k=0; k<strLuzesMod.size(); k++){
						modelos.push_back(strLuzesMod.at(k));
					}
					modelos.push_back(m->Value());
					long double p1,p2,p3,p4,p5,p6,p7,p8,p9;
					float n1[3],n2[3],n3[3];
					ifstream fich;
					fich.open(m->Attribute(mod[0]));
		    		if (fich.is_open()){
					fich >> nvertices2;
					sprintf(buff2, "%d", nvertices2);
    				modelos.push_back(buff2);
					fich >> tess;
		        		for(int k = 0; k < nvertices2; k+=3){
						fich >> p1;
						fich >> p2;
						fich >> p3;
						fich >> p4;
						fich >> p5;
						fich >> p6;
						fich >> p7;
						fich >> p8;
						fich >> p9;

						verticesTP.push_back(p1);
						verticesTP.push_back(p2);
						verticesTP.push_back(p3);
						verticesTP.push_back(p4);
						verticesTP.push_back(p5);
						verticesTP.push_back(p6);
						verticesTP.push_back(p7);
						verticesTP.push_back(p8);
						verticesTP.push_back(p9);

						}
						fich >> nverticesNP;
        				for(int k = 0; k < nverticesNP; k++){
        					fich >> p1;
							fich >> p2;
							fich >> p3;
							norm.push_back(p1);
							norm.push_back(p2);
							norm.push_back(p3);
						}
						fich >> nverticesT;
						for(int k = 0; k < nverticesT; k++){
        				fich >> p1;
						fich >> p2;
						textP.push_back(p1);
						textP.push_back(p2);
					}
				     }
				 	fich.close();
					//modelos.push_back(m->Attribute(mod[0]));
					m=m->NextSiblingElement();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("ring",e->Value()) == 0){
				if(e==NULL) printf("Erro no translate.\n");
				modelos.push_back(e->Value());
				TiXmlAttribute* pAttrib=e->FirstAttribute();
				while(pAttrib){
					modelos.push_back(pAttrib->Value());
					pAttrib=pAttrib->Next();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("translate",e->Value()) == 0){
				char str[15];
				int cont = 0;
				if(e==NULL) printf("Erro no translate.\n");
				TiXmlElement* m = e->FirstChildElement("point");
				if(m==NULL) printf("Erro no translate \n");
				modelos.push_back(e->Value());
				modelos.push_back(e->Attribute("time"));
				while(m){
					cont++;
				for(int i=0;i<3;i++){
					pAttrib = m->Attribute(s[i]);
					if(pAttrib){
						pontosT.push_back(atof(pAttrib));}
					else pontosT.push_back(0.0);
				}
				m=m->NextSiblingElement();
				}
				sprintf(str, "%d", cont);
				modelos.push_back(str);
				e=e->NextSiblingElement();
			}

			else if(strcmp("scale",e->Value()) == 0){
				if(e==NULL) printf("Erro no scale.\n");
				modelos.push_back(e->Value());
				for(int i=0;i<3;i++){
					pAttrib = e->Attribute(s[i]);
					if(pAttrib)
						modelos.push_back(pAttrib);
					else modelos.push_back("0.0");
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("rotate",e->Value()) == 0){
				if(e==NULL) printf("Erro no rotate.\n");
				pAttrib = e->Attribute("angle");
				if(pAttrib) { modelos.push_back("rotateA"); modelos.push_back(pAttrib); }
				else { pAttrib = e->Attribute("time"); modelos.push_back("rotate"); modelos.push_back(pAttrib); }
				for(int i=0;i<3;i++){
					pAttrib = e->Attribute(t[i]);
					if(pAttrib)
						modelos.push_back(pAttrib);
					else modelos.push_back("0.0");
				}
				e=e->NextSiblingElement();
			}

	}

}


	


int main(int argc, char* argv[]) {

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1200,800);
    glutCreateWindow("Scene");
    
    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    
    // Callback registration for keyboard processing
    //glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);
    
    //  OpenGL settings
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    //glEnable(GL_CULL_FACE);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    
    if( glewInit() != GLEW_OK )
    {
        printf( "Failed to init glew!\n" );
        return -1;
    }

    TiXmlDocument doc(argv[1]);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement* titleElement = doc.FirstChildElement( "scene" )->FirstChildElement( "group" );
		TiXmlElement* e = titleElement->FirstChildElement();
		lerXML(e);

	}
	else printf("Failed to load file\n");

	prepareModels();

	prepareNormals();

	prepareTexturas();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	for(int i=0;i<modelos.size();i++) printf("%s\n",modelos.at(i).c_str());

    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}