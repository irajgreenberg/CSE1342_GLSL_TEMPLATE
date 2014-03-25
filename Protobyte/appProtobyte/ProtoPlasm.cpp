//
//  ProtoPlasm.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoPlasm.h"

using namespace ijg;


ProtoPlasm::ProtoPlasm(ProtoBaseApp* baseApp):
baseApp(baseApp), appWidth(1920), appHeight(1080), appTitle("Protobyte App")
{
    // init app and call init() and run() to activate functions in user defined BaseApp derived class
    init();
    run();
}

ProtoPlasm:: ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp):
appWidth(appWidth), appHeight(appHeight), appTitle(appTitle), baseApp(baseApp){

    baseApp->setWidth(appWidth);
    baseApp->setHeight(appHeight);
    baseApp->setSize(Dim2i(appWidth, appHeight));    
    
    // Create GL context and call init() and run() to activate functions in user defined BaseApp derived class
    init();
    run();
}


void ProtoPlasm::init(){

	baseApp->setFrameCount(0);
	baseApp->setFrameRate(60.0f);


  srand (static_cast <unsigned> (time(0)));
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    // uncomment for 3.2+ context (OS X)
    // need to check this on WIN
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    // anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 8);
    
    window = glfwCreateWindow(appWidth, appHeight, appTitle.c_str(), /*glfwGetPrimaryMonitor()*/NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    // end GLFW setup
    
    
    // set gl states
    glClearColor(0, 0, 0, 1.0f);
    glShadeModel(GL_SMOOTH);
    // enable specualrity on textures
    glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_LIGHTING);
    glFrontFace(GL_CCW); // default
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glDisable(GL_CULL_FACE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glShadeModel(GL_FLAT); // option
    glEnable(GL_COLOR_MATERIAL); // incorporates per vertex color with lights
    
    // global ambient unrelated to lights
    float globalAmbient[4] = {.3, .3, .3, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  globalAmbient);
    
    // let glColor control diffues and ambient material values
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    
    //
    glEnable(GL_BLEND);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    //glBlendFunc (GL_ONE, GL_ONE);
    
    //glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_GREATER,0.0f);
    
    // for best antialiasing
    // http://bankslab.berkeley.edu/members/chris/AntiAliasing/AntiAliasingInOpenGL.html
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE); //  good for uniform scaling
    glClearStencil(0); // clear stencil buffer
    glClearDepth(1.0f); // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
    
    //int w = 0;
    //int h = 0;
    //glfwGetFramebufferSize(window, &w, &h);
    //std::cout << "Framewbuffer: w = " << w <<std::endl;
    //std::cout << "FrameBuffer h = " << h <<std::endl;
    
    
    // Activate init function in user derived class.n.
    baseApp->init();
}

// activate animation thread and run() function in user defined BaseApp derived class
void ProtoPlasm::run(){
    
    while (!glfwWindowShouldClose(window))
    {
        
        // Activate derived user class implementation.
		baseApp->setFrameCount(frameCount);
        baseApp->run();

        
        // handle GLFW events
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        frameCount++;
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

