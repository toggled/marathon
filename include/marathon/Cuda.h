/*
 * Cuda.h
 *
 * Created on: Mar 23, 2016
 * Author: Steffen Rechner <steffen.rechner@informatik.uni-halle.de>
 *
 * This file is part of the marathon software.
 *
 * Copyright (c) 2016, Steffen Rechner
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CUDAWRAPPER_H_
#define CUDAWRAPPER_H_

#include "config.h"

#include <cstdlib>

#ifdef CUDA
#include <cublas_v2.h>
#include <cublasXt.h>
#endif

namespace marathon {

	namespace cuda {

#ifdef CUDA
		// a handle for using cublas and cublasxt library
		extern cublasHandle_t cublasHandle;
		extern cublasXtHandle_t cublasXtHandle;

		/**
		 * Declare external functions that do the CUDA stuff. Mostly Wrapper around CUDA functions.
		 */
		extern void myCudaMallocPitch(void **devPtr, size_t *pitch, size_t width,
		                              size_t height);

		extern void myCudaMalloc(void **devPtr, size_t size);

		extern void myCudaFree(void *devPtr);

		extern void myCudaMemcpyHostToDevice(void *dst, const void *src,
		                                     size_t count);

		extern void myCudaMemset2D(void *devPtr, size_t pitch, int value,
		                           size_t width, size_t height);

		extern void myCudaMemcpy2DHostToDevice(void *dst, size_t dpitch,
		                                       const void *src, size_t spitch, size_t width, size_t height);

		extern void myCudaMemcpy2DDeviceToHost(void *dst, size_t dpitch,
		                                       const void *src, size_t spitch, size_t width, size_t height);

		extern void myCudaMemcpy2DDeviceToDevice(void *dst, size_t dpitch,
		                                         const void *src, size_t spitch, size_t width, size_t height);

		extern void cudaInit();

		extern void cudaFinalize();
#endif

		/**
		 * Initialize the CUDA related stuff.
		 */
		void init();

		/**
		 * Cleanup the CUDA Component.
		 **/
		void cleanup();

	}

}

#endif /* CUDAWRAPPER_H_ */
