#include "2.stencil_testing.h"

STENCIL_TESTING::stencil_testing::stencil_testing()
{
}

STENCIL_TESTING::stencil_testing::~stencil_testing()
{
}

void STENCIL_TESTING::stencil_testing::show()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

}
