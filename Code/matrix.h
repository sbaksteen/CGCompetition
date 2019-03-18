#ifndef MATRIX_H_
#define MATRIX_H_

#include "triple.h"

// 4x4 transformation matrix
class Matrix44 {
	public:
		double data[4][4];
		
		Matrix44();
		
		// operators
		
		Matrix44 operator +(Matrix44 const &m) const; // add two matrices
		
		Matrix44 operator -() const;                  // negate
		Matrix44 operator -(Matrix44 const &m) const; // subtract two matrices
		
		Matrix44 operator *(Matrix44 const &m) const; // multiply two matrices (right-multiplication by m)
		Triple operator *(Triple const &t) const;     // multiply the matrix with a vector
		Matrix44 operator *(double f) const;          // multiply every element by f
		
		Matrix44 operator /(double f) const;          // divide every element by f
		
		// compound operators
		
		Matrix44 &operator +=(Matrix44 const &m);
		Matrix44 &operator -=(Matrix44 const &m);
		Matrix44 &operator *=(Matrix44 const &m);
		Matrix44 &operator *=(double f);
		Matrix44 &operator /=(double f);
		
		// index operator
		double* operator [](int i);
		
		// Matrix operations
		
		Matrix44 noTranslation() const;
		
		Matrix44 transposed() const;
		void transpose();
		
		Matrix44 inverse() const;
		void invert();
		
		Matrix44 translated(Vector const &v) const;
		void translate(Vector const &v);
		
		Matrix44 rotated(Vector const &axis, double angle) const;
		void rotate(Vector const &axis, double angle);
		
		Matrix44 scaled(Vector const &s) const;
		void scale(Vector const &s);
		
};

#endif