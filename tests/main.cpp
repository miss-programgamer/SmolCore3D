#include <catch2/catch_test_macros.hpp>
#include <smol/core3d.hpp>
using namespace Smol;


TEST_CASE("Mat4x4 Constructor", "[mat4x4, constructor]")
{
	Mat4x4F mat1;
	REQUIRE(mat1[0][0] == 0.0f);
}