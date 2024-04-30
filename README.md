# Smol Core3D

This is a C++20 header-only library I created so I could reuse various basic structs I keep adding to my projects that make dealing with 3D space easier and more convenient. Notably, it includes template class implementations for a 3D vector type, a 4D vector type, and a 4x4 matrix type.

## Installation

This library uses CMake as its build system, so you can simply git clone it and then build & install it locally. Alternatively, since this is a header-only library, copy-pasting the headers you want into your project will suffice.

## Usage

Either include the main header file or the headers of individual structs. Note that including the main header also defines type aliases that use int and float as our structs' underlying value types in the parent `Smol` namespace. Only including individual structs does not define these aliases and does not put anything in the parent namespace, only defining things in `Smol::Core3D`.

```C++
#include <smol/core3d.hpp>
// Smol::Vec3I, Smol::Vec3F, Smol::Mat4x4I, Smol::Mat4x4F, etc. are available from now on.
```

```C++
#include <smol/core3d/vec3.hpp>
// Only Smol::Core3D::Vec3 is available from now on.

...

#include <smol/core3d/vec4.hpp>
// Only Smol::Core3D::Vec4 is available from now on.

...

#include <smol/core3d/mat4x4.hpp>
// Only Smol::Core3D::Mat4x4 is available from now on.
```

Since this library is still in its infancy, it does not yet have documentation that covers 100% (or any percent for that matter) of its public functions.