/*
 *  d2dImage.h
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __d2dImage_h__
#define __d2dImage_h__

#include "mkImage.h"
#include "glPlatform.h"
#include <vector>

namespace MonkVG {
	class Direct2DImage : public IImage {
	public:

		Direct2DImage(VGImageFormat format,
			VGint width, VGint height,
			VGbitfield allowedQuality);
		Direct2DImage(Direct2DImage& other);

		virtual ~Direct2DImage();

		virtual IImage* createChild(VGint x, VGint y, VGint w, VGint h);

		// drawing
		virtual void draw();
		virtual void drawSubRect(VGint ox, VGint oy, VGint w, VGint h, VGbitfield paintModes);
		virtual void drawToRect(VGint x, VGint y, VGint w, VGint h, VGbitfield paintModes);
		virtual void drawAtPoint(VGint x, VGint y, VGbitfield paintModes);

		virtual void setSubData(const void * data, VGint dataStride,
			VGImageFormat dataFormat,
			VGint x, VGint y, VGint width, VGint height);

		//void bind();
		//void unbind();

	private:
		//GLuint		_name;
	};
}

#endif // __d2dImage_h__
