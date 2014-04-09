/*
 *  d2dPath.h
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __d2dPath_h__
#define __d2dPath_h__

#include "mkPath.h"
#include <list>
#include <vector>



namespace MonkVG {

	//#define D2D (((OpenGLContext*)&IContext::instance())->gl())

	class Direct2DPath : public IPath {
	public:

		Direct2DPath(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities)
			: IPath(pathFormat, datatype, scale, bias, segmentCapacityHint, coordCapacityHint, capabilities)
		{

		}
		virtual ~Direct2DPath();


		virtual bool draw(VGbitfield paintModes);
		virtual void clear(VGbitfield caps);
		virtual void buildFillIfDirty();




	private:
	};
}

#endif // __d2dPath_h__
