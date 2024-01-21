#ifndef IQUADROCOPTERDYNAMICA_H
#define IQUADROCOPTERDYNAMICA_H

#include <QObject>
#include <Sensors/ISensors.hpp>
#include "OpenGL_Render_Interface.h"
#include "Sensors/IVirtualOrientationSensor.h"


class GLWidget;

// Интерфейс динамики квадрокоптера
class IQuadrocopterDynamica : public OpenGL_Render_Interface
{
public:
    // Конструктор и инициализация
    IQuadrocopterDynamica(GLWidget *_globalScene_);
    void Init(GLWidget *_globalScene_);

    // Обновление позиции и угла
    void UpdatePosition(const Vector3 &_PositionStability);
    void UpdateAngle(const Vector3 &_PositionStability);

    // Стабилизация высоты, позиции и угла ориентации
    void UpdateStabilizationHeight(Vector3& out_F , const scalar &_tau_height , scalar _time_step);
    void UpdateStabilizationPosition(Vector3 &out_Angle , const Vector3 &_tau_coords , scalar _time_step, bool is_rotate_plane=false);
    void UpdateStabilizationAngle(Vector3& stab_moment ,const Vector3 &_tau_angle , scalar _time_step);

    // Обновление стабилизации
    void UpdateStabilizationFreeControl(float _time_step);
    void UpdateStabilizationControlHeight(scalar expected_height, float _time_step);
    void UpdateStabilizationControlPosition(const Vector3 &expected_coords, scalar _time_step);

    void RenderDebug();

    // Получение и установка свойств
    IComponentRigidBody *PhysicsBody_Base() const;
    void SetTauAngles(const Vector3 &TauAngles);
    Vector3 Forward() const;
    Vector3 Left() const;
    IVirtualOrientationSensor *Sensor() const;

private:
    // Динамические точки
    Vector3 mDynamicPoints[4];

    // Физическое тело и сенсор
    IComponentRigidBody *mRigidBody_Base;
    IVirtualOrientationSensor *mSensor;

    // Параметры углов и позиции
    Vector3 m_TauAngles;
    Vector3 m_TauPosition;

    // Другие параметры
    scalar m_W[4];
    scalar m_Lenght;
    scalar m_Power;
    scalar m_AngleYaw;

    // Направления
    Vector3 m_Direction;
    Vector3 m_Forward;
    Vector3 m_Left;
};
#endif // IQUADROCOPTERDYNAMICA_H
