/*
 * Combinatorics.cpp
 *
 * Created on: May 11, 2016
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

#include "../../include/marathon/Combinatorics.h"

int marathon::Combinatorics::_nrow;
int marathon::Combinatorics::_ncol;
marathon::integer* marathon::Combinatorics::_binom;

void marathon::Combinatorics::init() {
	// init binomial coefficients
	_nrow = 1;
	_ncol = 1;
	_binom = new integer[_nrow * _ncol];
	_binom[0] = 1;
}

void marathon::Combinatorics::cleanup() {
	delete[] _binom;
}

marathon::integer marathon::Combinatorics::binom(const int n, const int k) {

	// binom(n,k) = binom(n, n-k)
	if (k > n - k) {
		return binom(n, n - k);
	}
		// invalid parameter?
	else if (k < 0 || n < 0) {
		return 0;
	}
		// is the result already computed?
	else if (n < _nrow && k < _ncol) {
		const integer res = _binom[n * _ncol + k];
		return res;
	}
		// if not? extend the table!
	else {

		// the new table sizes (at least +20% rows)
		const int nrow = (n + 2) * 1.2;
		const int ncol = (nrow / 2) + 2;
		assert(nrow > _nrow && ncol > _ncol);

		//std::cout << "extend table from " << _nrow << "x" << _ncol << " to "
		//		<< nrow << "x" << ncol << std::endl;

		// allocate 2d array
		integer *tmp = new integer[ncol * nrow];

		// copy the old values into the new table
		for (int i = 0; i < _nrow; i++) {
			for (int j = 0; j < _ncol; j++) {
				tmp[i * ncol + j] = _binom[i * _ncol + j];
			}
		}

		// define marginals in the new table area

		// binom(i,0) = 1
		for (int i = _nrow; i < nrow; i++) {
			tmp[i * ncol + 0] = 1;
		}

		// binom(i,i) = 1
		for (int i = _ncol; i < ncol; i++) {
			tmp[i * ncol + i] = 1;
		}

		/********************************************************
		 *  fill the missing parts of the table row by row
		 *
		 *       0      _ncol  ncol
		 *     0 |------|------|
		 *       |  LU  |  RU  |
		 * _nrow |------|------|
		 *       |  LB  |  RB  |
		 *  nrow |------|------|
		 *
		 ******************************************************/

		// 1. fill RU part
		for (int i = _ncol + 1; i < _nrow; i++) {
			for (int j = _ncol; j < ncol; j++) {
				// binom(i,j) = binom(i-1, j) + binom(i-1, j-1)
				tmp[i * ncol + j] = tmp[(i - 1) * ncol + j]
				                    + tmp[(i - 1) * ncol + (j - 1)];
			}
		}

		// 2. fill LB + RB part
		for (int i = _nrow; i < nrow; i++) {
			for (int j = 1; j < ncol; j++) {
				// binom(i,j) = binom(i-1, j) + binom(i-1, j-1)
				tmp[i * ncol + j] = tmp[(i - 1) * ncol + j]
				                    + tmp[(i - 1) * ncol + (j - 1)];
			}
		}

		/*	for(int i=0; i<nrow; i++) {
		 for(int j=0; j<ncol; j++) {
		 std::cout << tmp[i*ncol+j] << " ";
		 }
		 std::cout << std::endl;
		 }*/

		// replace _binom by tmp
		delete[] _binom;
		_binom = tmp;
		_nrow = nrow;
		_ncol = ncol;

		return binom(n, k);
	}
}

marathon::integer marathon::Combinatorics::factorial(const int n) {
	integer res = 1;
	for (int i = 1; i <= n; i++) {
		res = res * integer(i);
	}
	return res;
}