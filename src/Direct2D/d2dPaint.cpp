/*
 *  d2dPaint.cpp
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#include "d2dPaint.h"
//#include <cmath>
//#include <assert.h>
#include "d2dContext.h"

using namespace std;

namespace MonkVG {

	Direct2DPaint::Direct2DPaint()
		: IPaint()
		, _isDirty(true)
		, _gradientImage(VG_INVALID_HANDLE)
	{

	}

	Direct2DPaint::~Direct2DPaint() {
		if (_gradientImage != VG_INVALID_HANDLE) {
			vgDestroyImage(_gradientImage);
		}
	}

	void Direct2DPaint::setGLState() {
		
	}

	void Direct2DPaint::buildLinearGradientImage(VGfloat pathWidth, VGfloat pathHeight) {


	}

	void Direct2DPaint::buildRadialGradientImage(VGfloat pathWidth, VGfloat pathHeight) {
		

	}

	void Direct2DPaint::buildLinear2x3GradientImage(VGfloat pathWidth, VGfloat pathHeight) {
		

	}

	void Direct2DPaint::buildRadial2x3GradientImage(VGfloat pathWidth, VGfloat pathHeight) {
		

	}

	void Direct2DPaint::buildGradientImage(VGfloat pathWidth, VGfloat pathHeight) {
		
	}

}