#ifndef OPENGL_RENDER_INTERFACE_H
#define OPENGL_RENDER_INTERFACE_H

#include <IEngineComponent/IComponents.hpp>

class OpenGL_Render_Interface
{
public:
    OpenGL_Render_Interface();


protected:

    void draw_line(const Vector3& a ,  const Vector3& b , const Vector3& color = Vector3::IDENTITY);
    void draw_sphere(const Vector3& pos , const float& radius, const Vector3&  color = Vector3::IDENTITY);
};

#endif // OPENGL_RENDER_INTERFACE_H
