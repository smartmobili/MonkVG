/*
 *  d2dImage.cpp
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#include "d2dImage.h"
#include "d2dContext.h"

namespace MonkVG {

	Direct2DImage::Direct2DImage(VGImageFormat format,
		VGint width, VGint height,
		VGbitfield allowedQuality)
		: IImage(format, width, height, allowedQuality)
	{
		
	}

	Direct2DImage::Direct2DImage(Direct2DImage& other)
		: IImage(other)
	{

	}

	Direct2DImage::~Direct2DImage() {
		
	}

	IImage* Direct2DImage::createChild(VGint x, VGint y, VGint w, VGint h)
	{
		return (IImage *)0;
	}

	// drawing
	void Direct2DImage::draw()
	{

	}

	void Direct2DImage::drawSubRect(VGint ox, VGint oy, VGint w, VGint h, VGbitfield paintModes)
	{

	}

	void Direct2DImage::drawToRect(VGint x, VGint y, VGint w, VGint h, VGbitfield paintModes)
	{

	}

	void Direct2DImage::drawAtPoint(VGint x, VGint y, VGbitfield paintModes)
	{

	}

	void Direct2DImage::setSubData(const void * data, VGint dataStride,
		VGImageFormat dataFormat,
		VGint x, VGint y, VGint width, VGint height)
	{

	}

}