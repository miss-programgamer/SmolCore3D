#ifndef SMOL_CORE3D_DEFINED
#define SMOL_CORE3D_DEFINED


#include "core3d/vec3.hpp"
#include "core3d/vec4.hpp"
#include "core3d/mat4x4.hpp"


namespace Smol
{
	using Vec3I = Core3D::Vec3<int>;
	using Vec3F = Core3D::Vec3<float>;
	
	using Vec4I = Core3D::Vec4<int>;
	using Vec4F = Core3D::Vec4<float>;
	
	using Mat4x4I = Core3D::Mat4x4<int>;
	using Mat4x4F = Core3D::Mat4x4<float>;
}


#endif // SMOL_CORE3D_DEFINED