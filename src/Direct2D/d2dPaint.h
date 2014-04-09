/*
 *  d2dPaint.h
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __d2dPaint_h__
#define __d2dPaint_h__

#include "mkPaint.h"
#include "d2dImage.h"

namespace MonkVG {


	class Direct2DPaint : public IPaint {
	public:
		Direct2DPaint();
		virtual ~Direct2DPaint();
		void setGLState();
		void buildLinearGradientImage(VGfloat pathWidth, VGfloat pathHeight);
		void buildRadialGradientImage(VGfloat pathWidth, VGfloat pathHeight);
		void buildLinear2x3GradientImage(VGfloat pathWidth, VGfloat pathHeight);
		void buildRadial2x3GradientImage(VGfloat pathWidth, VGfloat pathHeight);
		void buildGradientImage(VGfloat pathWidth, VGfloat pathHeight);
		virtual bool isDirty() { return _isDirty; }
		virtual void setIsDirty(bool b) { _isDirty = b; }

		Direct2DImage* getGradientImage() { return (Direct2DImage*)_gradientImage; }

	private:
		bool		_isDirty;
		VGImage		_gradientImage;


	};
}

#endif // __d2dPaint_h__
