#ifndef SMOL_CORE3D_VEC4_DEFINED
#define SMOL_CORE3D_VEC4_DEFINED


namespace Smol::Core3D
{
	template<typename T>
	struct Vec4
	{
		T x;
		
		T y;
		
		T z;
		
		T w;
		
		
		// Construct a zero vector.
		constexpr Vec4() noexcept:
			x(T(0)), y(T(0)), z(T(0)), w(T(0))
		{}
		
		// Construct a unit vector.
		constexpr Vec4(T value) noexcept:
			x(value), y(value), z(value), w(value)
		{}
		
		// Construct a vector by piece.
		constexpr Vec4(T x, T y, T z, T w) noexcept:
			x(x), y(y), z(z), w(w)
		{}
		
		
		// Get a vector member value by index.
		constexpr T operator[](int index) const
		{ return (&x)[index]; }
	};
}


#endif // SMOL_CORE3D_VEC4_DEFINED