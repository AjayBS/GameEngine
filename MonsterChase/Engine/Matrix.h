#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace Engine {
	namespace Math {
		class Matrix
		{
		public:
			Matrix();
			Matrix(
				float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44);
			Matrix(const Matrix & i_other );
			~Matrix();
			// Allows us to use V = M * V (i.e. column vector)

			Matrix CreateIdentity();

			Matrix & operator=(const Matrix &i_other);
			static Matrix CreateXRotation(float i_RotationRadius);
			static Matrix CreateYRotation(float i_RotationRadius);
			static Matrix CreateZRotation(float i_RotationRadius);

			static Matrix CreateTranslation(Vector3 i_trans);
			static Matrix CreateTranslation(float i_transX, float i_transY, float i_transZ);
			static Matrix CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ);
			void Transpose();
			Matrix GetTranspose() const;

			inline Matrix operator*(const Matrix &i_other);

			Vector4 MultiplyLeft(const Vector4 &i_Vector) const;
			Vector4 MultiplyRight(const Vector4 &i_Vector) const;
			Matrix GetInverse(void) const;
			/*static const FaceMatrix Identity;*/

		private:
			float
				m_11, m_12, m_13, m_14,
				m_21, m_22, m_23, m_24,
				m_31, m_32, m_33, m_34,
				m_41, m_42, m_43, m_44;

			Matrix Multiply(const Matrix &i_other, Matrix & o_out) const;
			Matrix &InverseSSE(Matrix &o_out) const;
			Matrix &MultiplySSE(const Matrix &i_other, Matrix &o_out) const;

			void Invert(void);

			

			Matrix operator*();

		};

		inline Vector4 operator*(const Matrix &i_mtx, const Vector4 i_vec);
		inline Vector4 operator*(const Vector4 i_vec, const Matrix &i_mtx);

	}
}

#include "Matrix-inl.h"