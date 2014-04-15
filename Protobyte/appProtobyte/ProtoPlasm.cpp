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
    // instantiate world
    //world = std::unique_ptr<ProtoWorld>(new ProtoWorld(appWidth, appHeight));
    
    // init app and call init() and run() to activate functions in user defined BaseApp derived class
    initSFMLInit();
    initSFMLRun();
}

ProtoPlasm:: ProtoPlasm(int appWidth, int appHeight, std::string appTitle, ProtoBaseApp* baseApp):
appWidth(appWidth), appHeight(appHeight), appTitle(appTitle), baseApp(baseApp){
    // this->baseApp = baseApp;
    baseApp->setWidth(appWidth);
    baseApp->setHeight(appHeight);
    baseApp->setSize(Dim2i(appWidth, appHeight));    
    
    // Create GL context and call init() and run() to activate functions in user defined BaseApp derived class
    initSFMLInit();
    initSFMLRun();
}


void ProtoPlasm::initSFMLInit(){

//#if defined(_WIN32) || defined (_WIN64) 
//	glewExperimental = TRUE;
//	GLenum err = glewInit();
//	if (err != GLEW_OK)
//	{
//		//Problem: glewInit failed, something is seriously wrong.
//		std::cout << "glewInit failed, aborting." << std::endl;
//	}
//#endif
   



	
	
	baseApp->setFrameCount(0);
	baseApp->setFrameRate(60.0f);

	// Start GLFW setup  // NOTE: DO I need this??
	// for modern context handling
	//glfwInit();

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
    
    window = glfwCreateWindow(appWidth, appHeight, appTitle.c_str(), /*glfwGetPrimaryMonitor()*/ NULL, NULL);
    
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
 
    
    int w = 0;
    int h = 0;
    glfwGetFramebufferSize(window, &w, &h);
    std::cout << "Framewbuffer: w = " << w <<std::endl;
    std::cout << "FrameBuffer h = " << h <<std::endl;
    
                             
                             
    //baseApp->setWorld(std::move(world));
    // std::cout << "baseApp->world->fovAngle = " << baseApp->world->fovAngle << std::endl;
    
    // Activate init function in user derived class.n.
	baseApp->_init(); // base class
	baseApp->init(); // derived class
}

// activate animation thread and run() function in user defined BaseApp derived class
void ProtoPlasm::initSFMLRun(){
    
    // Activate derived user class implementations of events:
    /*
     • run
     • mouse
     • keyboard
     */
    
    // clear screen
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    while (!glfwWindowShouldClose(window))
    {
        /*
         TO DO – fix timing issues with control for users:
         From: http://stackoverflow.com/questions/2182675/how-do-you-make-sure-the-speed-of-opengl-animation-is-consistent-on-different-ma
*/
        
        
        
        
        // Activate derived user class implementation.
		baseApp->setFrameCount(frameCount);
		//baseApp->runWorld();
		baseApp->_run(); // called in base class
		baseApp->run(); // called in derived class

        
        // handle GLFW events
        
        // clear the buffers
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // end the current frame (internally swaps the front and back buffers)
        //window->display();
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        frameCount++;
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

