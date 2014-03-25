/*!  \brief  MyProg01.h

Protobyte Library v02
Created by Ira on 3/3/14.
Copyright (c) 2013 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "MyProg01.h"



void MyProg01::init() {

	// background color
	glClearColor(.2, .2, .2, 1);

	// some global ambience
	globalAmbient = ProtoLight(Col4f(.25f, .19f, .27f, 1)); // slight violet color

	// light0
	light0.setPosition(Vec3f(0, 0, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.3, .3, .3, 1.0));
	light0.setSpecular(Col4f(1, 1, 1, 1.0));
	light0.on();

	toroid = Toroid(Vec3f(), Vec3f(), Dim3f(10, 10, 10), Col4f(.87, .43, .99, 1), 36, 36, .5f, .2f, "pebbles.jpg");
	shader = ProtoShader("shader1.vert", "shader1.frag");

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 8.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;
	N = glm::transpose(glm::inverse(glm::mat3(MV)));

	// projection matrix and MVP Matrix
	float viewAngle = 65.0f;
	float aspect = width / height;
	float nearDist = .1f;
	float farDist = 2000.0f;

	P = glm::perspective(viewAngle, aspect, nearDist, farDist);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);

	// initialize Uniform variables for shaders
	initUniforms();

	// get some info about GLSL state
	GLSLInfo(&shader);

	// permanently bind shader
	shader.bind();
}


void MyProg01::initUniforms(){
	// lighting
	lightPos0_U = glGetUniformLocation(shader.getID(), "light0Position");
	lightDiffuse0_U = glGetUniformLocation(shader.getID(), "light0Diffuse");
	lightAmbient0_U = glGetUniformLocation(shader.getID(), "light0Ambient");
	lightSpecular0_U = glGetUniformLocation(shader.getID(), "light0Specular");

	//matrices
	MV_U = glGetUniformLocation(shader.getID(), "modelViewMatrix");
	MVP_U = glGetUniformLocation(shader.getID(), "modelViewProjectionMatrix");
	N_U = glGetUniformLocation(shader.getID(), "normalMatrix");
}

void MyProg01::run() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glViewport(0, 0, width, height);

	// update shader uniforms
	// Lighting  
	glUniform3fv(lightPos0_U, 1, &light0.getPosition().x);
	glUniform4fv(lightDiffuse0_U, 1, &light0.getDiffuse().r);
	glUniform4fv(lightAmbient0_U, 1, &light0.getAmbient().r);
	glUniform4fv(lightSpecular0_U, 1, &light0.getSpecular().r);

	render();
}


void MyProg01::render(){
	// transfomation matrices
	// reset transformation matrices to identity
	R = glm::mat4(1.0);
	T = glm::mat4(1.0);
	S = glm::mat4(1.0f);
	
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -8));
	R = glm::rotate(glm::mat4(1.0f), float(frameCount*.06), glm::vec3(.75f, 1, .25f));


	V = glm::lookAt(glm::vec3(0.0, 0.0, 8.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	
	// update MVP matrice for shader
	M = T * R * S;
	MV = V * M;
	MVP = P * MV;

	// some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix
	// update shader universal vars
	N = glm::transpose(glm::inverse(glm::mat3(MV)));
	glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
	glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(N_U, 1, GL_FALSE, &N[0][0]);

	toroid.display();
}



