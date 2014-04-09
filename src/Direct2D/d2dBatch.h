/*
 *  d2dBatch.h
 *  MonkVG-Direct2D
 *
 *  Created by Vincent Richomme on 4/8/14.
 *  Copyright 2010 MP Engineering. All rights reserved.
 *
 */

#ifndef __d2dBatch_h__
#define __d2dBatch_h__

#include "mkBatch.h"

//#include "glPlatform.h"

#include <vector>

namespace MonkVG {
	class Direct2DBatch : public IBatch {
	public:

		Direct2DBatch();
		virtual ~Direct2DBatch();

		virtual void draw();
		virtual void dump(void **vertices, size_t *size);
		virtual void finalize();

		/*void addPathVertexData(GLfloat* fillVerts, size_t fillVertCnt, GLfloat* strokeVerts, size_t strokeVertCnt, VGbitfield paintModes);*/

	};
}


#endif // __d2dBatch_h__
