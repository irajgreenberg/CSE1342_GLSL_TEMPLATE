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

#ifndef PROTO_JUNCUS_EFFUSUS_H
#define PROTO_JUNCUS_EFFUSUS_H


#include <iostream>
#include <memory>
#include "ProtoShape3.h"
#include "ProtoTube.h"




namespace ijg {

	class ProtoJuncusEffusus;
	typedef ProtoJuncusEffusus Junc;

	class ProtoJuncusEffusus : public ProtoShape3{

	public:
		ProtoJuncusEffusus();
		ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4f& col4);
		ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4f& col4, const std::string& textureImageURL1);

		ProtoJuncusEffusus(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
			const ProtoColor4f& col4, const std::string& textureImageURL1, const std::string& textureImageURL2);

		// dynamics
		void breath(); 
		void pulse();
		void spring();

		void display(RenderMode render1 = WIREFRAME, RenderMode render2 = SURFACE, float pointSize1 = .5, float pointSize2 = .5);

	private:
		ProtoTube tubule, tubuleWrap;
		std::string textureImageURL1, textureImageURL2;

		// for dynamics
		int waveDirectionID;
		int tubuleCrossSectionDetail, tubuleWrapCrossSectionDetail;
		int tubuleSpineSegments, tubuleWrapSpineSegments;
		int tubuleCrossSection, tubuleWrapCrossSection;
		Spline3 tubuleSpine, tubuleWrapSpine;
		float waveSpeed, waveFrequency, waveTheta;
		int STRIDE;
		std::vector<float> vertexDataCopy; 
		
		std::vector<float> tubulePrims, tubulePrimsOrig;
		std::vector<float> tubuleWrapPrims, tubuleWrapPrimsOrig;
		
		void init();
		
	};

}

#endif // PROTO_JUNCUS_EFFUSUS_H