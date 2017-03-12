#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;
float alfa = M_PI/2, beta = M_PI/6, raio = 20.0;
vector< std::vector<long double> > vert;
int i = 0;
float x,y,z;
vector<std::string> modelos;

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
  case 'q': raio=raio+0.1; break;
  case 'e': raio=raio-0.1; break;
  case 'w': if((beta+0.1<=M_PI/2) && (beta+0.1>=-M_PI/2)) beta+=0.1; break;
  case 's': if((beta-0.1<=M_PI/2) && (beta-0.1>=-M_PI/2)) beta-=0.1; break;
  case 'm': alfa+=0.1; break;
  case 'n': alfa-=0.1; break;
  default: break;
  }
  glutPostRedisplay();
}


void renderScene(void) {
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the camera
    glLoadIdentity();
    gluLookAt(raio*sin(alfa)*cos(beta),raio*sin(beta),raio*cos(beta)*cos(alfa),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    
    //glPolygonMode(GL_FRONT,GL_LINE);
    glColor3f(17.0/255.0,154.9/255.0,205.0/255.0);

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
			float x = atof(modelos.at(i+1).c_str());
			float y = atof(modelos.at(i+2).c_str());
			float z = atof(modelos.at(i+3).c_str());
			glTranslatef(x,y,z);
			i+=4;
		}

		else if(strcmp("rotate",modelos.at(i).c_str())==0){
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

		else if(strcmp("model",modelos.at(i).c_str())==0){
			int nvertices;
			long double f1;
			long double f2;
			long double f3;

			long double f4;
			long double f5;
			long double f6;

			long double f7;
			long double f8;
			long double f9;
			ifstream modelo;
			modelo.open(modelos.at(i+1).c_str());
    			if (modelo.is_open()){
			modelo >> nvertices;
        		for(int k = 0; k < nvertices; k=k+3){
				modelo >> f1;
				modelo >> f2;
				modelo >> f3;

				modelo >> f4;
				modelo >> f5;
				modelo >> f6;

				modelo >> f7;
				modelo >> f8;
				modelo >> f9;
				glBegin(GL_TRIANGLES);
				glVertex3f(f1, f2, f3);
				glVertex3f(f4, f5, f6);
				glVertex3f(f7, f8, f9);
				glEnd();
			}
		     	}
		 modelo.close();
		 i=i+2;
	     }
    }

    // End of frame
    glutSwapBuffers();
}


void lerXML(TiXmlElement* e){

	while(e){				
			if(strcmp("group",e->Value()) == 0){
				if(e==NULL) printf("Erro no group.\n");
				else{ modelos.push_back(e->Value()); lerXML(e->FirstChildElement()); modelos.push_back("/group"); e=e->NextSiblingElement(); }
			}
				
				
			else if(strcmp("models",e->Value()) == 0){
				if(e==NULL) printf("Erro no models.\n");
				TiXmlElement* m = e->FirstChildElement("model");
				while(m){
					modelos.push_back(m->Value());
					TiXmlAttribute* pA=m->FirstAttribute();
					modelos.push_back(pA->Value());
					m=m->NextSiblingElement();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("translate",e->Value()) == 0){
				if(e==NULL) printf("Erro no translate.\n");
				modelos.push_back(e->Value());
				TiXmlAttribute* pAttrib=e->FirstAttribute();
				while(pAttrib){
					modelos.push_back(pAttrib->Value());
					pAttrib=pAttrib->Next();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("scale",e->Value()) == 0){
				if(e==NULL) printf("Erro no scale.\n");
				modelos.push_back(e->Value());
				TiXmlAttribute* pAttrib=e->FirstAttribute();
				while(pAttrib){
					modelos.push_back(pAttrib->Value());
					pAttrib=pAttrib->Next();
				}
				e=e->NextSiblingElement();
			}

			else if(strcmp("rotate",e->Value()) == 0){
				if(e==NULL) printf("Erro no rotate.\n");
				modelos.push_back(e->Value());
				TiXmlAttribute* pAttrib=e->FirstAttribute();
				while(pAttrib){
					modelos.push_back(pAttrib->Value());
					pAttrib=pAttrib->Next();
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
	else
	{
		printf("Failed to load file\n");
	}


	for(int i=0;i<modelos.size();i++) printf("%s\n",modelos.at(i).c_str());	

    	/*int nvertices;
    	ifstream modelo;
    	for(int j = 0; j<modelos.size(); j++){
    		modelo.open(modelos.at(j).c_str());
    		if (modelo.is_open()){
		modelo >> nvertices;
        	for(int i = 0; i < nvertices; i++){
	      	vector <long double> verTri;
	      	long double f;
	      	modelo >> f;
	      	verTri.push_back(f);
	      	modelo >> f;
	      	verTri.push_back(f);
	      	modelo >> f;
              	verTri.push_back(f);

              	vert.push_back(verTri);
        }
	nv+=nvertices;
	modelo.close();
    }
    }*/
    
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
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
    
    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}