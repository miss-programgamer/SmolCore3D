#ifndef SMOL_CORE3D_MAT4X4_DEFINED
#define SMOL_CORE3D_MAT4X4_DEFINED


#include <cmath>
#include <numbers>
#include <array>
#include <stdexcept>
#include <compare>

#include "vec3.hpp"
#include "vec4.hpp"


namespace Smol::Core3D
{
	template<typename T>
	struct Mat4x4
	{
		friend auto operator<=>(const Mat4x4&, const Mat4x4&) = default;
		
		
		std::array<Vec4<T>, 4> rows;
		
		
	 public:
		// Construct a zero-initialized 4x4 matrix.
		constexpr Mat4x4() noexcept
		{ std::fill(&rows[0].x, &rows[0].x + 16, T(0)); }
		
		// Construct a 4x4 matrix from the given values.
		constexpr Mat4x4(Vec4<T> values[4]) noexcept
		{ std::copy(&values[0].x, &values[0].x + 16, &rows[0].x); }
		
		// Construct a 4x4 matrix from the given values.
		constexpr Mat4x4(T values[16]) noexcept
		{ std::copy(values, values + 16, &rows[0].x); }
		
		
		// Index into our 4x4 matrix.
		constexpr Vec4<T>& operator[](size_t index)
		{ return rows[index]; }
		
		// Index into our 4x4 matrix.
		constexpr const Vec4<T>& operator[](size_t index) const
		{ return rows[index]; }
		
		
		// Construct an identity 4x4 matrix.
		static constexpr Mat4x4 Identity()
		{
			const T values[16]
			{
				T(1), T(0), T(0), T(0),
				T(0), T(1), T(0), T(0),
				T(0), T(0), T(1), T(0),
				T(0), T(0), T(0), T(1),
			};
			
			return Mat4x4(values);
		}
	};
	
	
	template<>
	struct Mat4x4<float>
	{
		std::array<Vec4<float>, 4> rows;
		
		
	 public:
		// Construct a zero-initialized 4x4 matrix.
		constexpr Mat4x4() noexcept
		{ std::fill(&rows[0].x, &rows[0].x + 16, 0.0f);}
		
		// Construct a 4x4 matrix from the given values.
		constexpr Mat4x4(const Vec4<float> values[4]) noexcept
		{ std::copy(&values[0].x, &values[0].x + 16, &rows[0].x); }
		
		// Construct a 4x4 matrix from the given values.
		constexpr Mat4x4(const float values[16]) noexcept
		{ std::copy(values, values + 16, &rows[0].x); }
		
		
		// Index into our 4x4 matrix.
		constexpr Vec4<float>& operator[](size_t index)
		{ return rows[index]; }
		
		// Index into our 4x4 matrix.
		constexpr const Vec4<float>& operator[](size_t index) const
		{ return rows[index]; }
		
		
		// Construct a 4x4 identity matrix.
		static constexpr Mat4x4<float> Identity()
		{
			constexpr float values[16]
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 translation matrix.
		static constexpr Mat4x4<float> Translation(float x, float y, float z)
		{
			const float values[16]
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 translation matrix.
		static constexpr Mat4x4<float> Translation(const Vec3<float>& pos)
		{
			const float x = pos.x, y = pos.y, z = pos.z;
			
			const float values[16]
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 yaw rotation matrix.
		static inline Mat4x4<float> YawRotation(float angle)
		{
			const float radians = angle * float(std::numbers::pi) / 180.0f;
			const float sin = std::sin(radians);
			const float cos = std::cos(radians);
			
			const float values[16]
			{
				 cos, 0.0f,  sin, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sin, 0.0f,  cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 pitch rotation matrix.
		static inline Mat4x4<float> PitchRotation(float angle)
		{
			const float radians = angle * float(std::numbers::pi) / 180.0f;
			const float sin = std::sin(radians);
			const float cos = std::cos(radians);
			
			const float values[16]
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f,  cos, -sin, 0.0f,
				0.0f,  sin,  cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 roll rotation matrix.
		static inline Mat4x4<float> RollRotation(float angle)
		{
			const float radians = angle * float(std::numbers::pi) / 180.0f;
			const float sin = std::sin(radians);
			const float cos = std::cos(radians);
			
			const float values[16]
			{
				 cos, -sin, 0.0f, 0.0f,
				 sin,  cos, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 euler rotation matrix.
		static inline Mat4x4<float> EulerRotation(float pitch, float yaw)
		{
			const float pitch_rads = pitch * float(std::numbers::pi) / 180.0f;
			const float sinp = std::sin(pitch_rads);
			const float cosp = std::cos(pitch_rads);
			
			const float yaw_rads = yaw * float(std::numbers::pi) / 180.0f;
			const float siny = std::sin(yaw_rads);
			const float cosy = std::cos(yaw_rads);
			
			const float values[16]
			{
				cosy,  siny * sinp, -siny * cosp, 0.0f,
				0.0f,         cosp,         sinp, 0.0f,
				siny, -cosy * sinp,  cosy * cosp, 0.0f,
				0.0f,         0.0f,         0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 euler rotation matrix.
		static inline Mat4x4<float> EulerRotation(float pitch, float yaw, float roll)
		{
			const float pitch_rads = pitch * float(std::numbers::pi) / 180.0f;
			const float sinp = std::sin(pitch_rads);
			const float cosp = std::cos(pitch_rads);
			
			const float yaw_rads = yaw * float(std::numbers::pi) / 180.0f;
			const float siny = std::sin(yaw_rads);
			const float cosy = std::cos(yaw_rads);
			
			const float roll_rads = roll * float(std::numbers::pi) / 180.0f;
			const float sinr = std::sin(roll_rads);
			const float cosr = std::cos(roll_rads);
			
			const float m11 = cosr * cosy;
			const float m21 = -sinr * cosy;
			const float m31 = siny;
			const float m12 = (cosr * siny * sinp) + (sinr * cosp);
			const float m22 = (-sinr * siny * sinp) + (cosr * cosp);
			const float m32 = -cosy * sinp;
			const float m13 = (-cosr * siny * cosp) + (sinr * sinp);
			const float m23 = (sinr * siny * cosp) + (cosr * sinp);
			const float m33 = cosy * cosp;
			
			const float values[16]
			{
				 m11,  m12,  m13, 0.0f,
				 m21,  m22,  m23, 0.0f,
				 m31,  m32,  m33, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a 4x4 euler rotation matrix.
		static inline Mat4x4<float> EulerRotation(const Vec3<float>& euler)
		{
			const float x_rads = euler.x * float(std::numbers::pi) / 180.0f;
			const float sinx = std::sin(x_rads);
			const float cosx = std::cos(x_rads);
			
			const float y_rads = euler.y * float(std::numbers::pi) / 180.0f;
			const float siny = std::sin(y_rads);
			const float cosy = std::cos(y_rads);
			
			const float z_rads = euler.z * float(std::numbers::pi) / 180.0f;
			const float sinz = std::sin(z_rads);
			const float cosz = std::cos(z_rads);
			
			const float m11 = cosz * cosy;
			const float m21 = -sinz * cosy;
			const float m31 = siny;
			const float m12 = (cosz *siny * sinx) + (sinz * cosx);
			const float m22 = (-sinz * siny * sinx) + (cosz * cosx);
			const float m32 = -cosy * sinx;
			const float m13 = (-cosz * siny * cosx) + (sinz * sinx);
			const float m23 = (sinz * siny * cosx) + (cosz * sinx);
			const float m33 = cosy * cosx;
			
			const float values[16]
			{
				 m11,  m12,  m13, 0.0f,
				 m21,  m22,  m23, 0.0f,
				 m31,  m32,  m33, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a transform matrix from a position and euler angles.
		static inline Mat4x4 Transform(const Vec3<float>& pos, const Vec3<float>& euler)
		{
			const float x_rads = euler.x * float(std::numbers::pi) / 180.0f;
			const float sinx = std::sin(x_rads);
			const float cosx = std::cos(x_rads);
			
			const float y_rads = euler.y * float(std::numbers::pi) / 180.0f;
			const float siny = std::sin(y_rads);
			const float cosy = std::cos(y_rads);
			
			const float z_rads = euler.z * float(std::numbers::pi) / 180.0f;
			const float sinz = std::sin(z_rads);
			const float cosz = std::cos(z_rads);
			
			const float m11 = cosz * cosy;
			const float m21 = -sinz * cosy;
			const float m31 = siny;
			const float m12 = (cosz *siny * sinx) + (sinz * cosx);
			const float m22 = (-sinz * siny * sinx) + (cosz * cosx);
			const float m32 = -cosy * sinx;
			const float m13 = (-cosz * siny * cosx) + (sinz * sinx);
			const float m23 = (sinz * siny * cosx) + (cosz * sinx);
			const float m33 = cosy * cosx;
			
			const float values[16]
			{
				  m11,   m12,   m13, 0.0f,
				  m21,   m22,   m23, 0.0f,
				  m31,   m32,   m33, 0.0f,
				pos.x, pos.y, pos.z, 1.0f,
			};
			
			return Mat4x4<float>(values);
		}
		
		// Construct a perspective 4x4 matrix.
		static inline Mat4x4 Perspective(float fov, float aspect, float near_plane, float far_plane)
		{
			const float scale = 1.0f / std::tan(fov * (float(std::numbers::pi) / 360.0f));
			const float range = far_plane - near_plane;
			
			const float m11 = scale / aspect;
			const float m22 = scale;
			const float m33 = (-near_plane - far_plane) / range;
			const float m34 = 1.0f;
			const float m43 = 2.0f * far_plane * near_plane / range;
			
			const float values[16]
			{
				 m11, 0.0f, 0.0f, 0.0f,
				0.0f,  m22, 0.0f, 0.0f,
				0.0f, 0.0f,  m33,  m34,
				0.0f, 0.0f,  m43, 0.0f,
			};
			
			return Mat4x4<float>(values);
		}
	};
	
	
	template<typename T>
	constexpr Mat4x4<T> operator*(const Mat4x4<T>& lhs, const Mat4x4<T>& rhs)
	{
		const T values[16]
		{
			lhs[0][0]*rhs[0][0] + lhs[0][1]*rhs[1][0] + lhs[0][2]*rhs[2][0] + lhs[0][3]*rhs[3][0],
			lhs[0][0]*rhs[0][1] + lhs[0][1]*rhs[1][1] + lhs[0][2]*rhs[2][1] + lhs[0][3]*rhs[3][1],
			lhs[0][0]*rhs[0][2] + lhs[0][1]*rhs[1][2] + lhs[0][2]*rhs[2][2] + lhs[0][3]*rhs[3][2],
			lhs[0][0]*rhs[0][3] + lhs[0][1]*rhs[1][3] + lhs[0][2]*rhs[2][3] + lhs[0][3]*rhs[3][3],
			lhs[1][0]*rhs[0][0] + lhs[1][1]*rhs[1][0] + lhs[1][2]*rhs[2][0] + lhs[1][3]*rhs[3][0],
			lhs[1][0]*rhs[0][1] + lhs[1][1]*rhs[1][1] + lhs[1][2]*rhs[2][1] + lhs[1][3]*rhs[3][1],
			lhs[1][0]*rhs[0][2] + lhs[1][1]*rhs[1][2] + lhs[1][2]*rhs[2][2] + lhs[1][3]*rhs[3][2],
			lhs[1][0]*rhs[0][3] + lhs[1][1]*rhs[1][3] + lhs[1][2]*rhs[2][3] + lhs[1][3]*rhs[3][3],
			lhs[2][0]*rhs[0][0] + lhs[2][1]*rhs[1][0] + lhs[2][2]*rhs[2][0] + lhs[2][3]*rhs[3][0],
			lhs[2][0]*rhs[0][1] + lhs[2][1]*rhs[1][1] + lhs[2][2]*rhs[2][1] + lhs[2][3]*rhs[3][1],
			lhs[2][0]*rhs[0][2] + lhs[2][1]*rhs[1][2] + lhs[2][2]*rhs[2][2] + lhs[2][3]*rhs[3][2],
			lhs[2][0]*rhs[0][3] + lhs[2][1]*rhs[1][3] + lhs[2][2]*rhs[2][3] + lhs[2][3]*rhs[3][3],
			lhs[3][0]*rhs[0][0] + lhs[3][1]*rhs[1][0] + lhs[3][2]*rhs[2][0] + lhs[3][3]*rhs[3][0],
			lhs[3][0]*rhs[0][1] + lhs[3][1]*rhs[1][1] + lhs[3][2]*rhs[2][1] + lhs[3][3]*rhs[3][1],
			lhs[3][0]*rhs[0][2] + lhs[3][1]*rhs[1][2] + lhs[3][2]*rhs[2][2] + lhs[3][3]*rhs[3][2],
			lhs[3][0]*rhs[0][3] + lhs[3][1]*rhs[1][3] + lhs[3][2]*rhs[2][3] + lhs[3][3]*rhs[3][3],
		};
		
		return Mat4x4<T>(values);
	}
	
	
	template<typename T>
	constexpr Vec4<T> operator*(const Mat4x4<T>& lhs, const Vec4<T>& rhs)
	{
		return Vec4<T>
		{
			lhs[0][0]*rhs[0] + lhs[0][1]*rhs[0] + lhs[0][2]*rhs[0] + lhs[0][3]*rhs[0],
			lhs[1][0]*rhs[1] + lhs[1][1]*rhs[1] + lhs[1][2]*rhs[1] + lhs[1][3]*rhs[1],
			lhs[2][0]*rhs[2] + lhs[2][1]*rhs[2] + lhs[2][2]*rhs[2] + lhs[2][3]*rhs[2],
			lhs[3][0]*rhs[3] + lhs[3][1]*rhs[3] + lhs[3][2]*rhs[3] + lhs[3][3]*rhs[3],
		};
	}
}


#endif // SMOL_CORE3D_MAT4X4_DEFINED