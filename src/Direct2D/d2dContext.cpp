/*
 *  d2dContext.cpp
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#include "d2dContext.h"
#include "d2dPath.h"
//#include "d2dPaint.h"
//#include "d2dBatch.h"
//#include "d2dImage.h"
//#include "d2dFont.h"
//#include "mkCommon.h"


namespace MonkVG {

	//// singleton implementation ////
	static Direct2DContext g_context;
	IContext& IContext::instance()
	{
		return g_context;
	}


	Direct2DContext::Direct2DContext()
		: IContext()
	{
	}



	bool Direct2DContext::Initialize() {


		return true;
	}

	void Direct2DContext::resize() {

	}


	bool Direct2DContext::Terminate() {
		return true;
	}


	void Direct2DContext::beginRender() {

	}
	void Direct2DContext::endRender() {

	}


	/// factories

	IPath* Direct2DContext::createPath(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities) {

		Direct2DPath *path = new Direct2DPath(pathFormat, datatype, scale, bias, segmentCapacityHint, coordCapacityHint, capabilities &= VG_PATH_CAPABILITY_ALL);
		if (path == 0)
			setError(VG_OUT_OF_MEMORY_ERROR);

		return (IPath*)path;
	}

	void Direct2DContext::destroyPath(IPath* path) {
		
		delete (Direct2DPath*)path;
	}

	void Direct2DContext::destroyPaint(IPaint* paint) {
		
		//delete (MonkVG::Direct2DPaint*)paint;
	}

	IPaint* Direct2DContext::createPaint() {
		
		void * paint;
		/*MonkVG::Direct2DPaint *paint = new MonkVG::Direct2DPaint();
		if (paint == 0)
			setError(VG_OUT_OF_MEMORY_ERROR);*/
		return (IPaint*)paint;
	}

	IBatch* Direct2DContext::createBatch() {
		void * batch;
		/*MonkVG::Direct2DBatch *batch = new MonkVG::Direct2DBatch();
		if (batch == 0)
			setError(VG_OUT_OF_MEMORY_ERROR);*/
		return (IBatch*)batch;
	}

	void Direct2DContext::destroyBatch(IBatch* batch) {
		if (batch) {
			delete batch;
		}
	}

	IImage* Direct2DContext::createImage(VGImageFormat format,
		VGint width, VGint height,
		VGbitfield allowedQuality) {
		return nullptr;
		//return new Direct2DImage(format, width, height, allowedQuality);
	}
	void Direct2DContext::destroyImage(IImage* image) {
		if (image) {
			delete image;
		}
	}

	IFont* Direct2DContext::createFont() {
		return nullptr;
		//return new MonkVG::Direct2DFont();
	}
	void Direct2DContext::destroyFont(IFont* font) {
		if (font) {
			delete font;
		}
	}



	/// state 
	void Direct2DContext::setStrokePaint(IPaint* paint) {

	}

	void Direct2DContext::setFillPaint(IPaint* paint) {


	}


	void Direct2DContext::stroke() {

	}

	void Direct2DContext::fill() {



	}

	void Direct2DContext::startBatch(IBatch* batch) {
		assert(_currentBatch == 0);	// can't have multiple batches going on at once
		_currentBatch = batch;
	}
	void Direct2DContext::dumpBatch(IBatch *batch, void **vertices, size_t *size) {
		_currentBatch->dump(vertices, size);
	}
	void Direct2DContext::endBatch(IBatch* batch) {
		_currentBatch->finalize();
		_currentBatch = 0;
	}


	void Direct2DContext::clear(VGint x, VGint y, VGint width, VGint height) {
		// TODO:
	}


	void Direct2DContext::loadGLMatrix() {
		

	}


	void Direct2DContext::setIdentity() {

	}

	void Direct2DContext::transform(VGfloat* t) {
		// a	b	0
		// c	d	0
		// tx	ty	1
		Matrix33* active = getActiveMatrix();
		for (int i = 0; i < 9; i++)
			t[i] = active->m[i];

	}

	void Direct2DContext::setTransform(const VGfloat* t)  {
		//	OpenVG:
		//	sh	shx	tx
		//	shy	sy	ty
		//	0	0	1
		//
		// OpenGL
		// a	b	0
		// c	d	0
		// tx	ty	1

		Matrix33* active = getActiveMatrix();
		for (int i = 0; i < 9; i++)
			active->m[i] = t[i];
		loadGLMatrix();
	}


	void Direct2DContext::multiply(const VGfloat* t) {
		Matrix33 m;
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				m.set(y, x, t[(y * 3) + x]);
			}
		}
		Matrix33* active = getActiveMatrix();
		active->postMultiply(m);
		loadGLMatrix();
	}

	void Direct2DContext::scale(VGfloat sx, VGfloat sy) {
		Matrix33* active = getActiveMatrix();
		Matrix33 scale;
		scale.setIdentity();
		scale.setScale(sx, sy);
		Matrix33 tmp;
		Matrix33::multiply(tmp, scale, *active);
		active->copy(tmp);
		loadGLMatrix();
	}
	void Direct2DContext::translate(VGfloat x, VGfloat y) {

		Matrix33* active = getActiveMatrix();
		Matrix33 translate;
		translate.setTranslate(x, y);
		Matrix33 tmp;
		tmp.setIdentity();
		Matrix33::multiply(tmp, translate, *active);
		active->copy(tmp);
		loadGLMatrix();
	}
	void Direct2DContext::rotate(VGfloat angle) {
		Matrix33* active = getActiveMatrix();
		Matrix33 rotate;
		rotate.setRotation(radians(angle));
		Matrix33 tmp;
		tmp.setIdentity();
		Matrix33::multiply(tmp, rotate, *active);
		active->copy(tmp);
		loadGLMatrix();
	}

	void Direct2DContext::setImageMode(VGImageMode im) {
		/*IContext::setImageMode( im );
		switch ( im ) {
		case VG_DRAW_IMAGE_NORMAL:
		gl()->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		break;
		case VG_DRAW_IMAGE_MULTIPLY:
		gl()->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		break;
		case VG_DRAW_IMAGE_STENCIL:
		break;
		default:
		break;
		}*/
	}
}