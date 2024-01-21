#ifndef GLWIDGET_QUADROCOPTER_H
#define GLWIDGET_QUADROCOPTER_H

#include <QObject>
#include "glwidget.h"
#include "IQuadrocopterDynamica.h"

#include <../OpenGL/OpenGLTextRender.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

using namespace glfreetype;

class GLWidget_Quadrocopter : public GLWidget
{
    Q_OBJECT

public:

     GLWidget_Quadrocopter(QWidget *parent = nullptr);
    ~GLWidget_Quadrocopter();

    virtual void initializeGL();
    virtual void update_scene();
    virtual void paintGL();

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void closeEvent(QCloseEvent *event);

    void renderText();

    IQuadrocopterDynamica *QuadroDynamica() const;

    void start_simulate() { m_CScene->Descriptor().m_IsDynamics = true; }
    void stop_simulate() { m_CScene->Descriptor().m_IsDynamics = false; }
    bool is_simulate() const { return m_CScene->Descriptor().m_IsDynamics; }

private:



    font_data mOpenGLRenderText;

    //-----------------------------------//

    IQuadrocopterDynamica *m_QuadroDynamica;

    //-----------------------------------//

    Vector3 m_PositionStability;
    Vector3 m_AngleStability;

    void DisplayText(int x, int y, int pixelSize, const char* text, ...)
    {
        char buf[512];
        va_list ap;
        va_start(ap, text);
        vsprintf(buf, text, ap);
        va_end(ap);

        mOpenGLRenderText.print(x, y - 20, buf);

    }

};

#endif // GLWIDGET_QUADROCOPTER_H
