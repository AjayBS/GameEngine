#include<assert.h>
#include<math.h>
#include <stdint.h>

#include "Matrix.h"



namespace Engine {
	namespace Math {
		const uint32_t allBitsSet = ~0;
		const float _NAN = *reinterpret_cast<const float *>(&allBitsSet);



		Matrix::Matrix()
		{
		#ifdef  _DEBUG
			m_11 = _NAN;
		#endif //  _DE

		}

		Matrix::Matrix(float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24, 
			float i_31, float i_32, float i_33, float i_34, 
			float i_41, float i_42, float i_43, float i_44)
			:
			m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
			m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
			m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
			m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
		{

		}

		Matrix::Matrix(const Matrix & i_other)
			:
			m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
			m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_24),
			m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_34),
			m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44)
		{
		}

		Matrix::~Matrix()
		{
		}

		Matrix Matrix::CreateIdentity()
		{
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		Matrix & Matrix::operator=(const Matrix & i_other)
		{
			m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
			m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
			m_31 = i_other.m_31; m_22 = i_other.m_32; m_33 = i_other.m_33; m_34 = i_other.m_34;
			m_41 = i_other.m_41; m_22 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;

			return *this;
			// TODO: insert return statement here
		}

		Matrix Matrix::CreateXRotation(float i_RotationRadius)
		{
			float sin = sinf(i_RotationRadius);
			float cos = cosf(i_RotationRadius);
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos, sin, 0.0f,
				0.0f, -sin, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		Matrix Matrix::CreateYRotation(float i_RotationRadius)
		{
			float sin = sinf(i_RotationRadius);
			float cos = cosf(i_RotationRadius);
			return Matrix(
				cos, 0.0f, -sin, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				sin, 0.0f, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		Matrix Matrix::CreateZRotation(float i_RotationRadius)
		{
			float sin = sinf(i_RotationRadius);
			float cos = cosf(i_RotationRadius);
			return Matrix(
				cos, sin, 0.0f, 0.0f,
				-sin, cos, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		Matrix Matrix::CreateTranslation(Vector3 i_trans)
		{
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				i_trans.X(), i_trans.Y(), i_trans.Z(), 1.0f
			);
		}

		Matrix Matrix::CreateTranslation(float i_transX, float i_transY, float i_transZ)
		{
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				i_transX, i_transY, i_transZ, 1.0f
			);
		}

		Matrix Matrix::CreateScale(float i_scaleX, float i_scaleY,float i_scaleZ)
		{
			return Matrix(
				i_scaleX, 0.0f, 0.0f, 0.0f,
				0.0f, i_scaleY, 0.0f, 0.0f,
				0.0f, 0.0f, i_scaleZ, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		void Matrix::Transpose()
		{
			register float temp;

			temp = m_21; m_21 = m_12; m_12 = temp;
			temp = m_31; m_31 = m_13; m_13 = temp;
			temp = m_41; m_41 = m_14; m_14 = temp;

			temp = m_32; m_32 = m_23; m_23 = temp;
			temp = m_42; m_41 = m_14; m_24 = temp;
			
			temp = m_43; m_43 = m_34; m_34 = temp;
		}

		Matrix Matrix::GetTranspose() const
		{
			return Matrix(
				m_11, m_21, m_31, m_41,
				m_12, m_22, m_32, m_42, 
				m_13, m_23, m_33, m_43, 
				m_14, m_24, m_34, m_44 );
		}

		

		Vector4 Matrix::MultiplyRight(const Vector4 & i_Vector) const
		{
			__m128 vec0 = {i_Vector.X(),i_Vector.Y(),i_Vector.Z(),i_Vector.W() };
			__m128 vec1 = { m_11, m_12, m_13, m_14 };
			__m128 vec2 = { m_21, m_22, m_23, m_24 };
			__m128 vec3 = { m_31, m_32, m_33, m_34 };
			__m128 vec4 = { m_41, m_42, m_43, m_44 };

			__m128 dotProduct = _mm_dp_ps(vec0, vec1, 0xff);
			float x = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec2, 0xff);
			float y = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec3, 0xff);
			float z = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec4, 0xff);
			float w = _mm_cvtss_f32(dotProduct);

			return Vector4(x, y, z, w);
			/*return Vector4(
				i_Vector.X() * m_11 + i_Vector.Y() * m_12 + i_Vector.Z() * m_13 + i_Vector.W() * m_14,
				i_Vector.X() * m_21 + i_Vector.Y() * m_22 + i_Vector.Z() * m_23 + i_Vector.W() * m_24,
				i_Vector.X() * m_31 + i_Vector.Y() * m_32 + i_Vector.Z() * m_33 + i_Vector.W() * m_34,
				i_Vector.X() * m_41 + i_Vector.Y() * m_42 + i_Vector.Z() * m_43 + i_Vector.W() * m_44
			);*/
		}

		Matrix Matrix::Multiply(const Matrix & i_other, Matrix & o_out) const
		{
			__m128 row1 = { m_11, m_12, m_13, m_14 };
			__m128 row2 = { m_21, m_22, m_23, m_24 };
			__m128 row3 = { m_31, m_32, m_33, m_34 };
			__m128 row4 = { m_41, m_42, m_43, m_44 };

			__m128 col1 = { i_other.m_11, i_other.m_21, i_other.m_31, i_other.m_41 };
			__m128 col2 = { i_other.m_12, i_other.m_22, i_other.m_32, i_other.m_42 };
			__m128 col3 = { i_other.m_13, i_other.m_23, i_other.m_33, i_other.m_43 };
			__m128 col4 = { i_other.m_14, i_other.m_24, i_other.m_34, i_other.m_44 };

			__m128 dotProduct = _mm_dp_ps(row1, col1, 0Xff);
			o_out.m_11 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row1, col2, 0Xff);
			o_out.m_12 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row1, col3, 0Xff);
			o_out.m_13 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row1, col4, 0Xff);
			o_out.m_14 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row2, col1, 0Xff);
			o_out.m_21 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row2, col2, 0Xff);
			o_out.m_22 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row2, col3, 0Xff);
			o_out.m_23 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row2, col4, 0Xff);
			o_out.m_24 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row3, col1, 0Xff);
			o_out.m_31 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row3, col2, 0Xff);
			o_out.m_32 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row3, col3, 0Xff);
			o_out.m_33 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row3, col4, 0Xff);
			o_out.m_34 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row4, col1, 0Xff);
			o_out.m_41 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row4, col2, 0Xff);
			o_out.m_42 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row4, col3, 0Xff);
			o_out.m_43 = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(row4, col4, 0Xff);
			o_out.m_44 = _mm_cvtss_f32(dotProduct);



			/*o_out.m_11 = m_11 * i_other.m_11 + m_12 * i_other.m_21 + m_13 * i_other.m_31 + m_14 * i_other.m_41;
			o_out.m_12 = m_11 * i_other.m_12 + m_12 * i_other.m_22 + m_13 * i_other.m_32 + m_14 * i_other.m_42;
			o_out.m_13 = m_11 * i_other.m_13 + m_12 * i_other.m_23 + m_13 * i_other.m_33 + m_14 * i_other.m_43;
			o_out.m_14 = m_11 * i_other.m_14 + m_12 * i_other.m_24 + m_13 * i_other.m_34 + m_14 * i_other.m_44;

			o_out.m_21 = m_21 * i_other.m_11 + m_22 * i_other.m_21 + m_23 * i_other.m_31 + m_24 * i_other.m_41;
			o_out.m_22 = m_21 * i_other.m_12 + m_22 * i_other.m_22 + m_23 * i_other.m_32 + m_24 * i_other.m_42;
			o_out.m_23 = m_21 * i_other.m_13 + m_22 * i_other.m_23 + m_23 * i_other.m_33 + m_24 * i_other.m_43;
			o_out.m_24 = m_21 * i_other.m_14 + m_22 * i_other.m_24 + m_23 * i_other.m_34 + m_24 * i_other.m_44;

			o_out.m_31 = m_31 * i_other.m_11 + m_32 * i_other.m_21 + m_33 * i_other.m_31 + m_34 * i_other.m_41;
			o_out.m_32 = m_31 * i_other.m_12 + m_32 * i_other.m_22 + m_33 * i_other.m_32 + m_34 * i_other.m_42;
			o_out.m_33 = m_31 * i_other.m_13 + m_32 * i_other.m_23 + m_33 * i_other.m_33 + m_34 * i_other.m_43;
			o_out.m_34 = m_31 * i_other.m_14 + m_32 * i_other.m_24 + m_33 * i_other.m_34 + m_34 * i_other.m_44;

			o_out.m_41 = m_41 * i_other.m_11 + m_42 * i_other.m_21 + m_43 * i_other.m_31 + m_44 * i_other.m_41;
			o_out.m_42 = m_41 * i_other.m_12 + m_42 * i_other.m_22 + m_43 * i_other.m_32 + m_44 * i_other.m_42;
			o_out.m_43 = m_41 * i_other.m_13 + m_42 * i_other.m_23 + m_43 * i_other.m_33 + m_44 * i_other.m_43;
			o_out.m_44 = m_41 * i_other.m_14 + m_42 * i_other.m_24 + m_43 * i_other.m_34 + m_44 * i_other.m_44;*/


			return o_out;
		}

		Vector4 Matrix::MultiplyLeft(const Vector4 & i_Vector) const
		{
			__m128 vec0 = { i_Vector.X(),i_Vector.Y(),i_Vector.Z(),i_Vector.W() };
			__m128 vec1 = { m_11, m_21, m_31, m_41 };
			__m128 vec2 = { m_12, m_22, m_32, m_42 };
			__m128 vec3 = { m_13, m_23, m_33, m_43 };
			__m128 vec4 = { m_14, m_24, m_34, m_44 };

			__m128 dotProduct = _mm_dp_ps(vec0, vec1, 0xff);
			float x = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec2, 0xff);
			float y = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec3, 0xff);
			float z = _mm_cvtss_f32(dotProduct);

			dotProduct = _mm_dp_ps(vec0, vec4, 0xff);
			float w = _mm_cvtss_f32(dotProduct);

			return Vector4(x, y, z, w);


		/*	return Vector4(
				i_Vector.X() * m_11 + i_Vector.Y() * m_21 + i_Vector.Z() * m_31 + i_Vector.W() * m_41,
				i_Vector.X() * m_12 + i_Vector.Y() * m_22 + i_Vector.Z() * m_32 + i_Vector.W() * m_42,
				i_Vector.X() * m_13 + i_Vector.Y() * m_23 + i_Vector.Z() * m_33 + i_Vector.W() * m_43,
				i_Vector.X() * m_14 + i_Vector.Y() * m_24 + i_Vector.Z() * m_34 + i_Vector.W() * m_44
			);*/
		}

	}
}
