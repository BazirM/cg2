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

using namespace std;
#define POINT_COUNT 5
float alfa = M_PI/2, beta = M_PI/6, raio = 200.0;
vector< std::vector<long double> > vert;
float y[3]={0,-1,0};
vector<std::string> modelos;
vector<float> pontosT;
vector<float> pontosLuz;
int nvertices, nvertices2, tess, cont, contSoma, nverticesN;
float timer, ang, tempo = 1.0, temp = 0.0;

vector<GLfloat> norm;
vector<GLfloat> normP;

vector<GLfloat> vertices, verticesTP;

GLuint buffer, buffer2, buffer3, buffer4;


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
  case 'w': if((beta+0.1<=M_PI/2) && (beta+0.1>=-M_PI/2)) beta+=0.1; break;
  case 's': if((beta-0.1<=M_PI/2) && (beta-0.1>=-M_PI/2)) beta-=0.1; break;
  case 'm': alfa+=0.1; break;
  case 'n': alfa-=0.1; break;
  default: break;
  }
  glutPostRedisplay();
}

/*void desenhaModelo(){

	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexPointer(3,GL_FLOAT,0,0);
    glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);

}*/

void desenhaModelo(int v, int mv){

	//GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
	//GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
	//GLfloat pos[4] = {0.0, 0.0 ,1.0, 0.0};

	/*float pos[4] = {1.0, 1.0, 1.0, 0.0};
	float grena[4] = {153.0/255.0, 0.0, 51.0/255.0, 1.0};

	GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
	float red[4] = {0.8f, 0.2f, 0.2f, 1.0f};

	glMaterialfv(GL_FRONT, GL_SPECULAR, red);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);*/

	//float purple[4] = { 1.0f,0.0f,1.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);


	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer4);
	glNormalPointer(GL_FLOAT, 0, 0);	

	glDrawArrays(GL_TRIANGLES, mv, (mv + v));

}

void desenhaTeap(int v, int mv){


	/*float pos[4] = {1.0, 1.0, 1.0, 0.0};
	float grena[4] = {153.0/255.0f, 0.0f, 51.0/255.0f, 1.0f};

	GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
	float red[4] = {0.8f, 0.2f, 0.2f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, grena);
	glMaterialfv(GL_FRONT, GL_SPECULAR, diff);
*/
	//glMaterialf(GL_FRONT, GL_SHININESS, 1.0);

	//float purple[4] = { 1.0f,0.0f,1.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);

	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glVertexPointer(3,GL_FLOAT,0,0);

	//glBindBuffer(GL_ARRAY_BUFFER, buffer3);
	//glNormalPointer(GL_FLOAT, 0, 0);	


	/*glBindBuffer(GL_ARRAY_BUFFER, buffer4);
	glNormalPointer(GL_FLOAT, 0, 0);*/

	glDrawArrays(GL_TRIANGLES, mv, (mv + v));

}

/*void desenhaTeap(){

	/*glGenBuffers(1,&buffer2);
	glBindBuffer(GL_ARRAY_BUFFER, buffer2);
	glBufferData(GL_ARRAY_BUFFER, verticesTP.size() * sizeof(float), &verticesTP[0], GL_STATIC_DRAW);

	glVertexPointer(3,GL_FLOAT,0,0);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, verticesTP.size()/3);

}*/


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



void renderScene(void) {

	static float t = 0;
	float res[3];
	float deriv[3];
	float m[16]; 
	float z[3];
	float pos[4] = {0.0, 0.0, 0.0, 1.0};

	int nv = 0;
	int nvp = 0;

	contSoma = 0;
	cont = 0;


    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the camera
    glLoadIdentity();
    gluLookAt(raio*sin(alfa)*cos(beta),raio*sin(beta),raio*cos(beta)*cos(alfa),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    float lpos[4] = { 0.0,0.0,0.0,1.0 };
    float lpo[4] = { 0.2,0.2,0.2,1.0 };
    float lp[4] = { 1.0,1.0,1.0,1.0 };

    /*glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lpo);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lp);//apenase um exemplo*/

    for(int i=0;i<modelos.size();){
		if(strcmp("group",modelos.at(i).c_str())==0){
			glPushMatrix();
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
		    glColor3f(255.0/255.0,255.0/255.0,255.0/255.0);
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
        	float nluzes = atof(modelos.at(i+1).c_str());
        	for(int j=0;j<nluzes;j++){
        		float c[4] = { pontosLuz.at((j*4)+1), pontosLuz.at((j*4)+2), pontosLuz.at((j*4)+3), pontosLuz.at((j*4)+0) };
        		glLightfv(GL_LIGHT0+j, GL_POSITION, c);	//falta a questao das outras luzes com a position no xml(diffuse, etc..)
        		glLightfv(GL_LIGHT0+j, GL_AMBIENT, lpo);
				glLightfv(GL_LIGHT0+j, GL_DIFFUSE, lp);//apenas exemplo
        	}
        	i+=2;
        }

		else if(strcmp("color",modelos.at(i).c_str())==0){
            	float dr = atof(modelos.at(i+1).c_str());
           		float dg = atof(modelos.at(i+2).c_str());
            	float db = atof(modelos.at(i+3).c_str());
            	float sr = atof(modelos.at(i+4).c_str());
           		float sg = atof(modelos.at(i+5).c_str());
            	float sb = atof(modelos.at(i+6).c_str());
            	float er = atof(modelos.at(i+7).c_str());
           		float eg = atof(modelos.at(i+8).c_str());
            	float eb = atof(modelos.at(i+9).c_str());
            	float ar = atof(modelos.at(i+10).c_str());
           		float ag = atof(modelos.at(i+11).c_str());
            	float ab = atof(modelos.at(i+12).c_str());
				float diff[3] = {dr/255.0,dg/255.0,db/255.0};
				float amb[3] = {ar/255.0,ag/255.0,ab/255.0};
				float spec[3] = {sr/255.0,sg/255.0,sb/255.0};
				float emiss[3] = {er/255.0,eg/255.0,eb/255.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
				//glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
				glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
				glMaterialfv(GL_FRONT, GL_EMISSION, emiss);
				//glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
            	i+=13;
		}

		else if(strcmp("patch",modelos.at(i).c_str())==0){
			desenhaTeap(atoi(modelos.at(i+1).c_str()), nvp);
			nvp += atoi(modelos.at(i+1).c_str());
		 i=i+2;
	     }

		else if(strcmp("model",modelos.at(i).c_str())==0){
			desenhaModelo(atoi(modelos.at(i+1).c_str()), nv);
			nv += atoi(modelos.at(i+1).c_str());
		 	 i=i+2;
	     }
    }

    // End of frame
    glutSwapBuffers();
}

void calcularNormalTriangulo(float *a, float *b, float *c, float *res){
	float U[3] = { b[0] - a[0], b[1] - a[1], b[2] - a[2]};
	float V[3] = { c[0] - a[0], c[1] - a[1], c[2] - a[2]};

	cross(U,V,res);

	//res[0] = U[1]*V[2] - U[2]*V[1];
	//res[1] = U[2]*V[0] - U[0]*V[2];
	//res[2] = U[0]*V[1] - U[1]*V[0];


}


void lerXML(TiXmlElement* e){

	//char buff[15];
	const char* pAttrib;
	const char* l[4] = {"type", "posX", "posY", "posZ"};
	const char* s[3] = {"X", "Y", "Z"};
	const char* t[4] = {"axisX", "axisY", "axisZ"};
	const char* mod[13] = {"file", "diffR", "diffG", "diffB", "specR", "specG", "specB", "emissR", "emissG", "emissB", "ambR", "ambG", "ambB"};

	while(e){				
			if(strcmp("group",e->Value()) == 0){
				if(e==NULL) printf("Erro no group.\n");
				else{ modelos.push_back(e->Value()); lerXML(e->FirstChildElement()); modelos.push_back("/group"); e=e->NextSiblingElement(); }
			}

			else if(strcmp("lights",e->Value()) == 0){
				int n_luzes = 0;
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
					m=m->NextSiblingElement();
					}
				sprintf(str, "%d", n_luzes);
				modelos.push_back(str);
				e=e->NextSiblingElement();
			}
				
			else if(strcmp("models",e->Value()) == 0){
				char buff[15];
				if(e==NULL) printf("Erro no models.\n");
				TiXmlElement* m = e->FirstChildElement("model");
				while(m){
					modelos.push_back("color");
					for(int i=1;i<13;i++){
						pAttrib = m->Attribute(mod[i]);
						if(pAttrib)
							modelos.push_back(pAttrib);
						else modelos.push_back("0.0");
					}
					modelos.push_back(m->Value());
					long double p1,p2,p3,p4,p5,p6,p7,p8,p9;
					ifstream fich;
					//modelos.push_back(m->Attribute(mod[0]));
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
		     		}
		    	 	fich.close();
					m=m->NextSiblingElement();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("patches",e->Value()) == 0){
				char buff2[15];
				if(e==NULL) printf("Erro no patches.\n");
				TiXmlElement* m = e->FirstChildElement("patch");
				while(m){
					modelos.push_back("color");
					for(int i=1;i<13;i++){
						pAttrib = m->Attribute(mod[i]);
						if(pAttrib)
							modelos.push_back(pAttrib);
						else modelos.push_back("0.0");
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

						float v1[3] = {p1,p2,p3};
						float v2[3] = {p4,p5,p6};
						float v3[3] = {p7,p8,p9};
						float res[3];

						calcularNormalTriangulo(v1,v2,v3,res);
						normalize(res);

						norm.push_back(res[0]);
						norm.push_back(res[1]);
						norm.push_back(res[2]);

						calcularNormalTriangulo(v2,v3,v1,res);
						normalize(res);

						norm.push_back(res[0]);
						norm.push_back(res[1]);
						norm.push_back(res[2]);

						calcularNormalTriangulo(v3,v1,v2,res);
						normalize(res);

						norm.push_back(res[0]);
						norm.push_back(res[1]);
						norm.push_back(res[2]);

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

	TiXmlDocument doc(argv[1]);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement* titleElement = doc.FirstChildElement( "scene" )->FirstChildElement( "group" );
		TiXmlElement* e = titleElement->FirstChildElement();
		lerXML(e);

	}
	else printf("Failed to load file\n");


	//for(int i=0;i<normP.size();i++) printf("%f\n",normP.at(i));
	for(int i=0;i<modelos.size();i++) printf("%s\n",modelos.at(i).c_str());
    
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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    
    if( glewInit() != GLEW_OK )
    {
        printf( "Failed to init glew!\n" );
        return -1;
    }

	prepareModels();

	prepareNormals();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}
