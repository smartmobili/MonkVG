/*
 *  d2dContext.h
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __d2dContext_h__
#define __d2dContext_h__

#include "mkContext.h"
#include "glPlatform.h"

// Os specific
//#include <atlbase.h> // for CComPtr
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


namespace MonkVG {

	//#define D2D (((OpenGLContext*)&IContext::instance())->gl())

	class Direct2DContext : public IContext {
	public:

		Direct2DContext();

		virtual bool Initialize(VGHandle reserved);
		virtual bool Terminate();

		//// factories ////
		virtual IPath* createPath(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities);
		virtual void destroyPath(IPath* path);
		virtual void destroyPaint(IPaint* paint);
		virtual IPaint* createPaint();
		virtual IImage* createImage(VGImageFormat format,
			VGint width, VGint height,
			VGbitfield allowedQuality);
		virtual void destroyImage(IImage* image);
		virtual IBatch* createBatch();
		virtual void destroyBatch(IBatch* batch);
		virtual IFont* createFont();
		virtual void destroyFont(IFont* font);


		/// paint overrides
		virtual void setStrokePaint(IPaint* paint);
		virtual void setFillPaint(IPaint* paint);

		//// platform specific execution of stroke and fill ////
		virtual void stroke();
		virtual void fill();

		//// platform specific execution of Masking and Clearing ////
		virtual void clear(VGint x, VGint y, VGint width, VGint height);

		//// platform specific implementation of transform ////
		virtual void setIdentity();
		virtual void transform(VGfloat* t);
		virtual void scale(VGfloat sx, VGfloat sy);
		virtual void translate(VGfloat x, VGfloat y);
		virtual void rotate(VGfloat angle);
		virtual void setTransform(const VGfloat* t);
		virtual void multiply(const VGfloat* t);
		virtual void setMatrixMode(VGMatrixMode mode) {
			IContext::setMatrixMode(mode);
			loadGLMatrix();
		}
		void loadGLMatrix();




		void beginRender();
		void endRender();


		virtual void resize();


		static void checkGLError();

		/// batch drawing
		virtual void startBatch(IBatch* batch);
		virtual void dumpBatch(IBatch* batch, void **vertices, size_t *size);
		virtual void endBatch(IBatch* batch);

		/// image
		virtual void setImageMode(VGImageMode im);


	private:
		HWND m_hwnd;
		//CComPtr<ID2D1Factory> m_d2dFactory;
		//CComPtr<ID2D1HwndRenderTarget> m_renderTarget;
	
		ID2D1Factory* _pDirect2dFactory;
		ID2D1HwndRenderTarget* _pRenderTarget;
		


		// restore values to play nice with other apps
		int		_viewport[4];
		float	_projection[16];
		float	_modelview[16];
		float	_color[4];

		ID2D1HwndRenderTarget* d2dRenderTarget() { return _pRenderTarget; }
	};
}

#endif // __d2dContext_h__
