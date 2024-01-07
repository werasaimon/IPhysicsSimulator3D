#ifndef GLWIDGET_QUADROCOPTER_H
#define GLWIDGET_QUADROCOPTER_H

#include <QObject>
#include "glwidget.h"
#include "IQuadrocopterDynamica.h"

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

    IQuadrocopterDynamica *QuadroDynamica() const;

    void start_simulate() { m_CScene->Descriptor().m_IsDynamics = true; }
    void stop_simulate() { m_CScene->Descriptor().m_IsDynamics = false; }
    bool is_simulate() const { return m_CScene->Descriptor().m_IsDynamics; }

private:

    IQuadrocopterDynamica *m_QuadroDynamica;

    //-----------------------------------//

    Vector3 m_PositionStability;
    Vector3 m_AngleStability;

};

#endif // GLWIDGET_QUADROCOPTER_H
