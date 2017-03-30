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
float alfa = M_PI/2, beta = M_PI/6, raio = 200.0;
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
  case 'q': raio=raio+1.0; break;
  case 'e': raio=raio-1.0; break;
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

		else if(strcmp("ring",modelos.at(i).c_str())==0){
            		float inr = atof(modelos.at(i+1).c_str());
            		float outr = atof(modelos.at(i+2).c_str());
            		int nside = atoi(modelos.at(i+3).c_str());
            		int ring = atoi(modelos.at(i+4).c_str());
            		glutSolidTorus(inr,outr,nside,ring);
            		i+=5;
        	}

		else if(strcmp("color",modelos.at(i).c_str())==0){
            		float r = atof(modelos.at(i+1).c_str());
           		float g = atof(modelos.at(i+2).c_str());
            		float b = atof(modelos.at(i+3).c_str());
            		glColor3f(r/255.0,g/255.0,b/255.0);
            		i+=4;
		}

		else if(strcmp("model",modelos.at(i).c_str())==0){
			int nvertices;
			long double v1,v2,v3,v4,v5,v6,v7,v8,v9;
			ifstream fich;
			fich.open(modelos.at(i+1).c_str());
    			if (fich.is_open()){
			fich >> nvertices;
        		for(int k = 0; k < nvertices; k=k+3){
				fich >> v1;
				fich >> v2;
				fich >> v3;

				fich >> v4;
				fich >> v5;
				fich >> v6;

				fich >> v7;
				fich >> v8;
				fich >> v9;
				glBegin(GL_TRIANGLES);
				glVertex3f(v1, v2, v3);
				glVertex3f(v4, v5, v6);
				glVertex3f(v7, v8, v9);
				glEnd();
			}
		     	}
		 fich.close();
		 i=i+2;
	     }
    }

    // End of frame
    glutSwapBuffers();
}


void lerXML(TiXmlElement* e){

	const char* pAttrib;
	const char* s[3] = {"X", "Y", "Z"};
	const char* t[4] = {"angle", "axisX", "axisY", "axisZ"};
	const char* mod[4] = {"file", "diffR", "diffG", "diffB"};

	while(e){				
			if(strcmp("group",e->Value()) == 0){
				if(e==NULL) printf("Erro no group.\n");
				else{ modelos.push_back(e->Value()); lerXML(e->FirstChildElement()); modelos.push_back("/group"); e=e->NextSiblingElement(); }
			}
				
				
			else if(strcmp("models",e->Value()) == 0){
				if(e==NULL) printf("Erro no models.\n");
				TiXmlElement* m = e->FirstChildElement("model");
				while(m){
					modelos.push_back("color");
					for(int i=1;i<4;i++){
						pAttrib = m->Attribute(mod[i]);
						if(pAttrib)
							modelos.push_back(pAttrib);
						else modelos.push_back("255");
					}
					modelos.push_back(m->Value());
					modelos.push_back(m->Attribute(mod[0]));
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
				if(e==NULL) printf("Erro no translate.\n");
				modelos.push_back(e->Value());
				for(int i=0;i<3;i++){
					pAttrib = e->Attribute(s[i]);
					if(pAttrib)
						modelos.push_back(pAttrib);
					else modelos.push_back("0.0");
				}
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
				modelos.push_back(e->Value());
				for(int i=0;i<4;i++){
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
    
    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}
