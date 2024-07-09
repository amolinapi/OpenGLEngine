#include "GLWindow.h"
#include "GLRender.h"

int main()
{ 
    GLWindow window;
    GLRender render;

    window.init();
    render.renderLoop();

    return 0;
}
   