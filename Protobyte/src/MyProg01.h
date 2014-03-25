/*!  \brief  MyProg01.h: 

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

#ifndef MYPROG_01_H
#define MYPROG_01_H

#include <iostream>
#include "appProtobyte/ProtoBaseApp.h"


using namespace ijg;

class MyProg01 : public ProtoBaseApp {

public:

	ProtoLight globalAmbient;
	ProtoShader shader;

	Toroid toroid;
	
	void init(); // required
	void run(); // required

	void initUniforms(); // convenience
	void render(); // convenience
	

private:

};

#endif // MYPROG_01_H
