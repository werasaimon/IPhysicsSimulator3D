#include "OpenGL_Render_Interface.h"
#include <GL/freeglut.h>
#include <QDebug>

OpenGL_Render_Interface::OpenGL_Render_Interface()
{

}

void OpenGL_Render_Interface::draw_line(const Vector3 &a, const Vector3 &b, const Vector3 &color)
{
    glPushMatrix();
    glColor3fv(color);
    glBegin(GL_LINES);
    glVertex3fv(a);
    glVertex3fv(b);
    glEnd();
    glPopMatrix();
}

void OpenGL_Render_Interface::draw_sphere(const Vector3 &pos, const float &radius , const Vector3 &color)
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glutSolidSphere(radius,10,10);
    glPopMatrix();
}
