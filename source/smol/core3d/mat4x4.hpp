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
		static inline Mat4x4<float> EulerRotation(float yaw, float pitch, float roll = 0.0f)
		{
			const float yaw_rads = yaw * float(std::numbers::pi) / 180.0f;
			const float ysin = std::sin(yaw_rads);
			const float ycos = std::cos(yaw_rads);
			
			const float pitch_rads = pitch * float(std::numbers::pi) / 180.0f;
			const float psin = std::sin(pitch_rads);
			const float pcos = std::cos(pitch_rads);
			
			const float roll_rads = roll * float(std::numbers::pi) / 180.0f;
			const float rsin = std::sin(roll_rads);
			const float rcos = std::cos(roll_rads);
			
			// const float values[16]
			// {
			// 	 cos, -sin, 0.0f, 0.0f,
			// 	 sin,  cos, 0.0f, 0.0f,
			// 	0.0f, 0.0f, 1.0f, 0.0f,
			// 	0.0f, 0.0f, 0.0f, 1.0f,
			// };
			
			// return Mat4x4<float>(values);
			
			throw std::exception("not implemented");
		}
		
		// Construct a perspective 4x4 matrix.
		static inline Mat4x4 Perspective(float fov, float aspect, float near_plane, float far_plane)
		{
			const float scale = 1.0f / std::tan(fov * (float(std::numbers::pi) / 360.0f));
			const float range = far_plane - near_plane;
			
			const float v0x0 = scale / aspect;
			const float v1x1 = scale;
			const float v2x2 = (-near_plane - far_plane) / range;
			const float v3x2 = 1.0f;
			const float v2x3 = 2.0f * far_plane * near_plane / range;
			
			const float values[16]
			{
				v0x0, 0.0f, 0.0f, 0.0f,
				0.0f, v1x1, 0.0f, 0.0f,
				0.0f, 0.0f, v2x2, v3x2,
				0.0f, 0.0f, v2x3, 0.0f,
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