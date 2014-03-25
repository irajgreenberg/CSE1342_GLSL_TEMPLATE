/*!  \brief  ProtoJuncusEffusus.h: (add brief description)
ProtoJuncusEffusus.h
Protobyte Library v02

Created by Ira on 03/05/14.
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

\ingroup common
This class is part of the group common (update)
\sa NO LINK
*/

#include "ProtoJuncusEffusus.h"
using namespace ijg;

// this is nasty fix eventually
namespace {
	float waveTheta = 0;
	float waveRadius = 1.85;


	std::vector<float> waveRadiusVals;
	std::vector<float> waveThetas;
	std::vector<float> waveFreqs;

}



ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4): ProtoShape3(pos,rot,  size, col4){

}
ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, const std::string& textureImageURL1) : ProtoShape3(pos, rot, size, col4), textureImageURL1(textureImageURL1), textureImageURL2(textureImageURL1){
	init();
}

ProtoJuncusEffusus::ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
	const ProtoColor4f& col4, const std::string& textureImageURL1, const std::string& textureImageURL2) : ProtoShape3(pos, rot, size, col4), textureImageURL1(textureImageURL1), textureImageURL2(textureImageURL2){
	init();
}

void ProtoJuncusEffusus::init(){
	STRIDE = 12;
	//trace("ind =", ind);
	float theta = 0.0f;
	float tubuleRadius = 2.2;//8.73f;
	float tubuleLen = 2.875;
	int tubuleSegs = 9;
	float tubuleStep = tubuleLen / tubuleSegs;
	int tubuleInterpDetail = 2;//6;
	int tubuleDetail = 12;//18;

	std::vector<Vec3f> cps;

	Vec3 pos = Vec3f(0, tubuleLen / 2, 0);
	for (int k = 0; k < tubuleSegs; ++k){
		if (k < 3){
			cps.push_back(Vec3f(pos.x + random(-.22, .22), pos.y - tubuleStep*k, pos.z + random(-.22, .22)));
		}
		else {
			cps.push_back(Vec3f(pos.x + random(-.06, .06), pos.y - tubuleStep*k, pos.z + random(-.06, .06)));
		}
	}
	// tapered
	//            tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE, Tup2f(tubuleRadius, .21), 1),true, "reptile3.jpg");

	// curvey
	tubule = Tube(Spline3(cps, tubuleInterpDetail, false, 1), random(.06, .08), tubuleDetail, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleRadius, .18), 6), true, textureImageURL1);
	tubulePrimsOrig = tubule.getInterleavedPrims();
    tubuleCrossSectionDetail = tubule.getCrossSectionDetail();
	tubuleSpineSegments = tubule.getInterleavedPrims().size() / STRIDE / tubuleCrossSectionDetail;
	trace("tubule.getInterleavedPrims().size() =", tubule.getInterleavedPrims().size());
	trace("tubulePrimsOrig.size() =", tubulePrimsOrig.size());
	trace("tubuleCrossSectionDetail =", tubuleCrossSectionDetail);
	trace("tubuleSpineSegments =", tubuleSpineSegments);

	tubule.textureOn();
	tubule.setTextureScale(1.0);
	tubule.setShininess(104);
	tubule.setColor(Col4f(1, 1, 1, 1));

	// hack - review
	float freqMax = random(1900, 3500);
	float radiusMax = random(.01, .05);
	tubuleSpine = tubule.getPath();
	for (size_t i = 0; i<tubuleSpine.getVerts().size(); ++i){
		//balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));

		waveRadiusVals.push_back((tubuleSpine.getVerts().size()-i)*radiusMax); // HACK --fix
		waveFreqs.push_back(PI / freqMax/*random(PI/1440.0, PI/360.0)*/); // HACK --fix
		waveThetas.push_back(0); // HACK --fix
	}

	//    
	std::vector<Vec3f> pts;
	float tubuleBuldgeMin = .55f, tubuleBuldgeMax = 1.95f;

	for (int i = 0; i < tubule.getVertices().size() - 2; ++i){
		pts.push_back(tubule.getVertices().at(i).pos);
	}

	Spline3 s(pts, 2, false, .5);
	tubuleWrap = Tube(s, .03, 6/*12*/, ProtoTransformFunction(ProtoTransformFunction::SINUSOIDAL, Tup2f(tubuleBuldgeMin, tubuleBuldgeMax/*2.1*/), 40), true, textureImageURL2);
	tubuleWrapPrims = tubuleWrap.getInterleavedPrims();
	tubuleWrapCrossSectionDetail = tubuleWrap.getCrossSectionDetail();
	tubuleWrapSpineSegments = tubuleWrapPrims.size() / STRIDE / tubuleWrapCrossSectionDetail;

	tubuleWrap.setColor(Col4f(.3f, .25f, .2f, 1));
	tubuleWrap.textureOn();
}

void ProtoJuncusEffusus::display(RenderMode render1, RenderMode render2, float pointSize1, float pointSize2){
	tubule.display(render1, pointSize1);
	//tubuleWrap.display(render2, pointSize2);
}

void ProtoJuncusEffusus::breath(){

	waveDirectionID = int(random(4));
	glBindBuffer(GL_ARRAY_BUFFER, tubule.getVboID());
	float t = PI / 360.0;
	float x = 0;
	float y = 0;
	float z = 0;
	float ny = 0;
	int cntr = 0;
	//trace(" tubuleSpineSegments =", tubuleSpineSegments);
	int xCntr = 0;
	//int id = int(random(4));
	for (int i = 0; i < tubuleSpineSegments; ++i) {
		for (int j = 0; j < tubuleCrossSectionDetail; ++j) {
			for (int k = 0; k < STRIDE; ++k) {
				//trace(" i*tubuleCrossSectionDetail + j*STRIDE + k =", i*tubuleCrossSectionDetail + j    j*STRIDE + k);
				//trace("cntr =", cntr);
				if (k == 0){
					x = tubulePrimsOrig.at(cntr);
					y = tubulePrimsOrig.at(cntr+1);
					z = tubulePrimsOrig.at(cntr + 2);
					int index = i*tubuleCrossSection + j;
					//switch (0/*waveDirectionID*/){
					switch (1){

					case 0:
						x = tubulePrimsOrig.at(cntr) + cos(waveThetas.at(i))*waveRadiusVals.at(i);
						ny = tubulePrimsOrig.at(cntr + 3) + cos(waveThetas.at(i))*waveRadiusVals.at(i);
						/*if (ciliaNodeIDs.at(index) != -1){
							cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
						}*/
						break;
					case 1:
						x = tubulePrimsOrig.at(cntr) + sin(waveThetas.at(i))*waveRadiusVals.at(i);
						ny = tubulePrimsOrig.at(cntr + 3) + sin(waveThetas.at(i))*waveRadiusVals.at(i);
						/*if (ciliaNodeIDs.at(index) != -1){
							cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
						}*/
						break;
					case 2:
						x = tubulePrimsOrig.at(cntr) - cos(waveThetas.at(i))*waveRadiusVals.at(i);
						ny = tubulePrimsOrig.at(cntr + 3) - cos(waveThetas.at(i))*waveRadiusVals.at(i);
						/*if (ciliaNodeIDs.at(index) != -1){
							cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
						}*/
						break;
					case 3:
						x = tubulePrimsOrig.at(cntr) - sin(waveThetas.at(i))*waveRadiusVals.at(i);
						ny = tubulePrimsOrig.at(cntr + 3) - sin(waveThetas.at(i))*waveRadiusVals.at(i);
						/*if (ciliaNodeIDs.at(index) != -1){
							cilia.at(xCntr++)->setAnchorPt(Vec3f(x, y, z));
						}*/
						break;
					}

					
					//trace("y =", y);
					if (i == 12){
						tubule.interleavedPrims.at(cntr) = x;
					}

						if (i == tubuleSpineSegments - 1 && j == tubuleCrossSectionDetail - 1 && k == STRIDE - 1){
							x = tubulePrimsOrig.at(cntr + 12) - sin(waveThetas.at(i))*waveRadiusVals.at(i);
							tubule.interleavedPrims.at(cntr+12) = x;
						}
					

				}


				//interleavedPrims.at(cntr+3) = ny;


				//                if(ciliaNodeIDs.at(cntr) != -1){
				//                    cilia.at(cntr)->setAnchorPt(Vec3f(*ciliaAnchors.at(cntr).x_p, *ciliaAnchors.at(cntr).y_p, *ciliaAnchors.at(cntr).z_p));
				//                }


				//vnorms
				//ny = vertexDataCopy.at(i + 4) + cos(waveTheta)*waveRadius;
				//interleavedPrims.at(i + 4) = ny;
				cntr++;
			}
		}
		//if(age>20){
		//  waveThetas.at(i) += waveFreqs.at(i)*(.99-age*.01);
		// } else {
		waveThetas.at(i) += waveFreqs.at(i);
		//}
	}

	int primsID = tubule.interleavedPrims.size() - 14;
	int nodeID = tubule.interleavedPrims.size() / 12 / tubuleCrossSectionDetail / tubuleSpineSegments - 24;


	int vertsDataSize = sizeof (float)*tubule.interleavedPrims.size();
	// upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &tubule.interleavedPrims[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// move cilia
	/*if (getHasCilia()){
		for (size_t i = 0; i<cilia.size(); ++i){
			if (age<lifeSpan){
				cilia.at(i)->run();
			}

		}
	}*/
}

void ProtoJuncusEffusus::pulse(){
}
void ProtoJuncusEffusus::spring(){
}