#ifndef SMOL_CORE3D_VEC3_DEFINED
#define SMOL_CORE3D_VEC3_DEFINED


#include <cmath>


namespace Smol::Core3D
{
	template<typename T>
	struct Vec3
	{
		enum class Dir
		{ Up, Down, Left, Right, Forward, Back };
		
		
		T x;
		
		T y;
		
		T z;
		
		
	 public:
		// Construct a zero vector.
		constexpr Vec3() noexcept:
			x(T(0)), y(T(0)), z(T(0))
		{}
		
		// Construct a unit vector.
		constexpr Vec3(T value) noexcept:
			x(value), y(value), z(value)
		{}
		
		// Construct a vector by piece.
		constexpr Vec3(T x, T y, T z) noexcept:
			x(x), y(y), z(z)
		{}
		
		// Construct a normal vector pointing in the given direction.
		constexpr Vec3(Dir dir) noexcept
		{
			switch (dir)
			{
				case Dir::Up:      x =  T(0); y = T(+1); z =  T(0); break;
				case Dir::Down:    x =  T(0); y = T(-1); z =  T(0); break;
				case Dir::Left:    x = T(-1); y =  T(0); z =  T(0); break;
				case Dir::Right:   x = T(+1); y =  T(0); z =  T(0); break;
				case Dir::Forward: x =  T(0); y =  T(0); z = T(+1); break;
				case Dir::Back:    x =  T(0); y =  T(0); z = T(-1); break;
				default:      x =  T(0); y =  T(0); z =  T(0); break;
			}
		}
		
		
		// Get the length of this vector.
		inline T GetLength() const
		{ return std::sqrt(x*x + y*y + z*z); }
		
		// Get the square of the length of this vector.
		constexpr T GetLengthSqr() const
		{ return x*x + y*y + z*z; }
		
		// Get the normal of this vector.
		inline Vec3 GetNormal() const
		{
			const float length = std::sqrt(x*x + y*y + z*z);
			return Vec3(x / length, y / length, z / length);
		}
		
		
		// Get a vector member value by index.
		constexpr T operator[](size_t index) const
		{ return (&x)[index]; }
		
		
		// Get the dot product of the two given vectors.
		static constexpr T Dot(const Vec3& lhs, const Vec3& rhs)
		{ return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
	};
	
	
	template<typename T>
	constexpr Vec3<T> operator-(const Vec3<T>& vec)
	{ return Vec3<T>(-vec.x, -vec.y, -vec.z); }
	
	
	template<typename T>
	constexpr Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ return Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
	
	template<typename T>
	constexpr Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ return Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
	
	template<typename T>
	constexpr Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ return Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
	
	template<typename T>
	constexpr Vec3<T> operator/(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ return Vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }
	
	
	template<typename T>
	constexpr Vec3<T> operator*(const Vec3<T>& lhs, T rhs)
	{ return Vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
	
	template<typename T>
	constexpr Vec3<T> operator*(T lhs, const Vec3<T>& rhs)
	{ return Vec3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }
	
	template<typename T>
	constexpr Vec3<T> operator/(const Vec3<T>& lhs, T rhs)
	{ return Vec3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }
	
	
	
	template<typename T>
	constexpr Vec3<T>& operator+=(Vec3<T>& lhs, const Vec3<T>& rhs)
	{ lhs = Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); return lhs; }
	
	template<typename T>
	constexpr Vec3<T>& operator-=(Vec3<T>& lhs, const Vec3<T>& rhs)
	{ lhs = Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); return lhs; }
	
	template<typename T>
	constexpr Vec3<T>& operator*=(Vec3<T>& lhs, const Vec3<T>& rhs)
	{ lhs = Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); return lhs; }
	
	template<typename T>
	constexpr Vec3<T>& operator/=(Vec3<T>& lhs, const Vec3<T>& rhs)
	{ lhs = Vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); return lhs; }
	
	
	template<typename T>
	constexpr Vec3<T>& operator*=(Vec3<T>& lhs, T rhs)
	{ lhs = Vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); return lhs; }
	
	template<typename T>
	constexpr Vec3<T>& operator/=(Vec3<T>& lhs, T rhs)
	{ lhs = Vec3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); return lhs; }
}


#endif // SMOL_CORE3D_VEC3_DEFINED