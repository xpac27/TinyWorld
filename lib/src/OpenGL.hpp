#ifdef PLATFORM_OSX
#define GLFW_INCLUDE_GLEXT
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#endif

#ifdef PLATFORM_IOS
#include <OpenGLES/ES3/glext.h>
#endif
