#include "matrix.h"
#include "triple.h"

#include <cmath>

Matrix44::Matrix44() {
	// Construct identity matrix.
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			if (j == k) {
				data[j][k] = 1;
			} else {
				data[j][k] = 0;
			}
		}
	}
}

Matrix44 Matrix44::operator +(Matrix44 const &m) const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			r[j][k] = data[j][k] + m.data[j][k];
		}
	}
	return r;
}

Matrix44 Matrix44::operator -() const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			r[j][k] = -data[j][k];
		}
	}
	return r;
}

Matrix44 Matrix44::operator -(Matrix44 const &m) const {
	return *this + (-m);
}

Matrix44 Matrix44::operator *(Matrix44 const &m) const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			r[j][k] = 0;
			for (int n = 0; n < 4; n++) {
				r[j][k] += data[j][n] * m.data[n][k];
			}
		}
	}
	return r;
}

Triple Matrix44::operator *(Triple const &t) const {
	Triple r = Triple(0, 0, 0);
	r.x = data[0][0] * t.x + data[0][1] * t.y + data[0][2] * t.z + data[0][3];
	r.y = data[1][0] * t.x + data[1][1] * t.y + data[1][2] * t.z + data[1][3];
	r.z = data[2][0] * t.x + data[2][1] * t.y + data[2][2] * t.z + data[2][3];
	return r;
}

Matrix44 Matrix44::operator *(double f) const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			r[j][k] = data[j][k] * f;
		}
	}
	return r;
}

Matrix44 Matrix44::operator /(double f) const {
	return *this * (1/f);
}

Matrix44 &Matrix44::operator +=(Matrix44 const &m) {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] += m.data[j][k];
		}
	}
	return *this;
}

Matrix44 &Matrix44::operator -=(Matrix44 const &m) {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] -= m.data[j][k];
		}
	}
	return *this;
}

Matrix44 &Matrix44::operator *=(Matrix44 const &m) {
	Matrix44 r = *this * m;
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] = r[j][k];
		}
	}
	return *this;
}

Matrix44 &Matrix44::operator *=(double f) {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] *= f;
		}
	}
	return *this;
}

Matrix44 &Matrix44::operator /=(double f) {
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] /= f;
		}
	}
	return *this;
}

double* Matrix44::operator [](int j) {
	return data[j];
}

Matrix44 Matrix44::noTranslation() const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			r[j][k] = data[j][k];
		}
	}
	return r;
}

Matrix44 Matrix44::transposed() const {
	Matrix44 r = Matrix44();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			r[j][k] = data[k][j];
		}
	}
	return r;
}

void Matrix44::transpose() {
	Matrix44 r = this->transposed();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] = r[j][k];
		}
	}
}

/*
 * This function has been adapted from the open-source 3D graphics library Mesa.
Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

Matrix44 Matrix44::inverse() const {
	Matrix44 inv = Matrix44();
	
	inv[0][0] = data[1][1]  * data[2][2] * data[3][3] - 
             data[1][1]  * data[2][3] * data[3][2] - 
             data[2][1]  * data[1][2]  * data[3][3] + 
             data[2][1]  * data[1][3]  * data[3][2] +
             data[3][1] * data[1][2]  * data[2][3] - 
             data[3][1] * data[1][3]  * data[2][2];

    inv[1][0] = -data[1][0]  * data[2][2] * data[3][3] + 
              data[1][0]  * data[2][3] * data[3][2] + 
              data[2][0]  * data[1][2]  * data[3][3] - 
              data[2][0]  * data[1][3]  * data[3][2] - 
              data[3][0] * data[1][2]  * data[2][3] + 
              data[3][0] * data[1][3]  * data[2][2];

    inv[2][0] = data[1][0]  * data[2][1] * data[3][3] - 
             data[1][0]  * data[2][3] * data[3][1] - 
             data[2][0]  * data[1][1] * data[3][3] + 
             data[2][0]  * data[1][3] * data[3][1] + 
             data[3][0] * data[1][1] * data[2][3] - 
             data[3][0] * data[1][3] * data[2][1];

    inv[3][0] = -data[1][0]  * data[2][1] * data[3][2] + 
               data[1][0]  * data[2][2] * data[3][1] +
               data[2][0]  * data[1][1] * data[3][2] - 
               data[2][0]  * data[1][2] * data[3][1] - 
               data[3][0] * data[1][1] * data[2][2] + 
               data[3][0] * data[1][2] * data[2][1];

    inv[0][1] = -data[0][1]  * data[2][2] * data[3][3] + 
              data[0][1]  * data[2][3] * data[3][2] + 
              data[2][1]  * data[0][2] * data[3][3] - 
              data[2][1]  * data[0][3] * data[3][2] - 
              data[3][1] * data[0][2] * data[2][3] + 
              data[3][1] * data[0][3] * data[2][2];

    inv[1][1] = data[0][0]  * data[2][2] * data[3][3] - 
             data[0][0]  * data[2][3] * data[3][2] - 
             data[2][0]  * data[0][2] * data[3][3] + 
             data[2][0]  * data[0][3] * data[3][2] + 
             data[3][0] * data[0][2] * data[2][3] - 
             data[3][0] * data[0][3] * data[2][2];

    inv[2][1] = -data[0][0]  * data[2][1] * data[3][3] + 
              data[0][0]  * data[2][3] * data[3][1] + 
              data[2][0]  * data[0][1] * data[3][3] - 
              data[2][0]  * data[0][3] * data[3][1] - 
              data[3][0] * data[0][1] * data[2][3] + 
              data[3][0] * data[0][3] * data[2][1];

    inv[3][1] = data[0][0]  * data[2][1] * data[3][2] - 
              data[0][0]  * data[2][2] * data[3][1] - 
              data[2][0]  * data[0][1] * data[3][2] + 
              data[2][0]  * data[0][2] * data[3][1] + 
              data[3][0] * data[0][1] * data[2][2] - 
              data[3][0] * data[0][2] * data[2][1];

    inv[0][2] = data[0][1]  * data[1][2] * data[3][3] - 
             data[0][1]  * data[1][3] * data[3][2] - 
             data[1][1]  * data[0][2] * data[3][3] + 
             data[1][1]  * data[0][3] * data[3][2] + 
             data[3][1] * data[0][2] * data[1][3] - 
             data[3][1] * data[0][3] * data[1][2];

    inv[1][2] = -data[0][0]  * data[1][2] * data[3][3] + 
              data[0][0]  * data[1][3] * data[3][2] + 
              data[1][0]  * data[0][2] * data[3][3] - 
              data[1][0]  * data[0][3] * data[3][2] - 
              data[3][0] * data[0][2] * data[1][3] + 
              data[3][0] * data[0][3] * data[1][2];

    inv[2][2] = data[0][0]  * data[1][1] * data[3][3] - 
              data[0][0]  * data[1][3] * data[3][1] - 
              data[1][0]  * data[0][1] * data[3][3] + 
              data[1][0]  * data[0][3] * data[3][1] + 
              data[3][0] * data[0][1] * data[1][3] - 
              data[3][0] * data[0][3] * data[1][1];

    inv[3][2] = -data[0][0]  * data[1][1] * data[3][2] + 
               data[0][0]  * data[1][2] * data[3][1] + 
               data[1][0]  * data[0][1] * data[3][2] - 
               data[1][0]  * data[0][2] * data[3][1] - 
               data[3][0] * data[0][1] * data[1][2] + 
               data[3][0] * data[0][2] * data[1][1];

    inv[0][3] = -data[0][1] * data[1][2] * data[2][3] + 
              data[0][1] * data[1][3] * data[2][2] + 
              data[1][1] * data[0][2] * data[2][3] - 
              data[1][1] * data[0][3] * data[2][2] - 
              data[2][1] * data[0][2] * data[1][3] + 
              data[2][1] * data[0][3] * data[1][2];

    inv[1][3] = data[0][0] * data[1][2] * data[2][3] - 
             data[0][0] * data[1][3] * data[2][2] - 
             data[1][0] * data[0][2] * data[2][3] + 
             data[1][0] * data[0][3] * data[2][2] + 
             data[2][0] * data[0][2] * data[1][3] - 
             data[2][0] * data[0][3] * data[1][2];

    inv[2][3] = -data[0][0] * data[1][1] * data[2][3] + 
               data[0][0] * data[1][3] * data[2][1] + 
               data[1][0] * data[0][1] * data[2][3] - 
               data[1][0] * data[0][3] * data[2][1] - 
               data[2][0] * data[0][1] * data[1][3] + 
               data[2][0] * data[0][3] * data[1][1];

    inv[3][3] = data[0][0] * data[1][1] * data[2][2] - 
              data[0][0] * data[1][2] * data[2][1] - 
              data[1][0] * data[0][1] * data[2][2] + 
              data[1][0] * data[0][2] * data[2][1] + 
              data[2][0] * data[0][1] * data[1][2] - 
              data[2][0] * data[0][2] * data[1][1];

    double det = data[0][0] * inv[0][0] + data[0][1] * inv[1][0] + data[0][2] * inv[2][0] + data[0][3] * inv[3][0];
	// we assume that det != 0, that is: all matrices are invertible.
	// This holds for all valid transformation matrices.
	det = 1.0 / det;
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			inv[j][k] = det * inv[j][k];
		}
	}
	return inv;
}

void Matrix44::invert() {
	Matrix44 inv = inverse();
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] = inv[j][k];
		}
	}
}

Matrix44 Matrix44::translated(Vector const &v) const {
	Matrix44 translateMatrix = Matrix44();
	for (int i = 0; i < 3; i++) {
		translateMatrix[i][3] = v.data[i];
	}
	return *this * translateMatrix;
}

void Matrix44::translate(Vector const &v) {
	Matrix44 translateMatrix = Matrix44();
	for (int i = 0; i < 3; i++) {
		translateMatrix[i][3] = v.data[i];
	}
	*this *= translateMatrix;
}

Matrix44 Matrix44::rotated(Vector const &axis, double angle) const {
	Vector a = axis.normalized();
	Matrix44 r = Matrix44();
	double ac = cos(angle);
	double as = sin(angle);
	r[0][0] = ac + a.x*a.x*(1 - ac);
	r[0][1] = a.x * a.y * (1 - ac) - a.z * as;
	r[0][2] = a.x*a.z*(1-ac) + a.y*as;
	
	r[1][0] = a.y*a.x*(1-ac) + a.z*as;
	r[1][1] = ac + a.y*a.y*(1-ac);
	r[1][2] = a.y*a.z*(1-ac) - a.x*as;
	
	r[2][0] = a.z*a.x*(1-ac) - a.y*as;
	r[2][1] = a.z*a.y*(1-ac) + a.x*as;
	r[2][2] = ac + a.z*a.z*(1-ac);
	
	return *this * r;
}

void Matrix44::rotate(Vector const &axis, double angle) {
	Matrix44 r = rotated(axis, angle);
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			data[j][k] = r[j][k];
		}
	}
}

Matrix44 Matrix44::scaled(Vector const &s) const {
	Matrix44 scaleMatrix = Matrix44();
	
	scaleMatrix[0][0] = s.x;
	scaleMatrix[1][1] = s.y;
	scaleMatrix[2][2] = s.z;
	
	return *this * scaleMatrix;
}

void Matrix44::scale(Vector const &s) {
	Matrix44 scaleMatrix = Matrix44();
	
	scaleMatrix[0][0] = s.x;
	scaleMatrix[1][1] = s.y;
	scaleMatrix[2][2] = s.z;
	
	*this *= scaleMatrix;
}