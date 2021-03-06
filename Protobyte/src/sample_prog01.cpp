/*!  \brief  sample_prog01.h:
Form study 3 for Zhulong Sattellite Exhibition: 4/2014
Protobyte Library v02

Created by Ira on 3/26/14.
Copyright (c) 2014 Ira Greenberg. All rights reserved.

Library Usage:
This work is licensed under the Creative Commons
Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit
http://creativecommons.org/licenses/by-nc-sa/3.0/
or send a letter to Creative Commons,
444 Castro Street, Suite 900,
Mountain View, California, 94041, USA.

This notice must be retained any source distribution.
Some help from:http://www.opengl.org/discussion_boards/showthread.php/171184-GLM-to-create-gl_NormalMatrix

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "sample_prog01.h"

void sample_prog01::init() {

	// light0
	light0.setPosition(Vec3f(0, 0, 1));
	light0.setDiffuse(Col4f(1, 1, 1, 1.0f));
	light0.setAmbient(Col4f(.5, .3, .3, 1.0));
	light0.setSpecular(Col4f(1, 1, 1, 1.0));
	light0.on();

	t = Toroid(Vec3(0, 0, 0), Vec3f(), Dim3f(2, 2, 2), Col4f(1, .65, 1, 1), 36, 12, 1, .09, "leather2.jpg");
	t2 = Toroid(Vec3(0, 0, 0), Vec3f(), Dim3f(2, 2, 2), Col4f(.3, .5, .7, 1), 36, 12, 1, .09);
}

void sample_prog01::run() {
	setBackground(.2, .2, .22);

	render();
}


void sample_prog01::render(int scaleFactor){
	rotate(90, 1, 0, 0); 
	
	push();
	scale(2.85);
	rotate(getFrameCount()*.25, .15, .2, .4);
	t2.display();
	pop(); 
	
	push();
	scale(.25);
	rotate(getFrameCount()*.9, 0, 0, 1);
	t.display();
	pop();
	
	push();
	rotate(getFrameCount()*.2, 0, 0, 1);
	push();
	translate(-1, 0, 0);
	scale(.65);
	rotate(-getFrameCount()*.8, 0, 0, 1);
	t2.display();
	pop();


	push();
	translate(1, 0, 0);
	scale(.65);
	rotate(-getFrameCount()*.4, .3, .6, 1);
	t.display();
	pop();
	pop();
}
