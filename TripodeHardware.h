#ifndef TRIPODEHARDWARE_H
#define TRIPODEHARDWARE_H

#include <ActuatorDynamic.h>
#include <HingeMountTwoAxis.h>
#include <Sensors/ISensors.hpp>


class TripodeHardware
{

public:

    TripodeHardware(GLWidget *_globalScene_);

    /// Иницилизация обекта управления турелю
    void Init(GLWidget *_globalScene_);


    ///
    /// \brief Update - Задаем поворот по углам Yaw , Pitch
    ///
    void Update();

    ///
    /// \brief UpdateLQR - Линейний квадратичний регулятор стабилизации в угол - control_euler_angle
    /// \param control_euler_angle - Входной клиентские углі куда нужно повернуть
    ///  control_euler_angle.x => клиентский угол поарота - ( вверх - вниз )
    ///  control_euler_angle.y => клиентский угол поарота - ( лево - право )
    void UpdateLQR(const Vector3 &control_euler_angle = Vector3::ZERO);


    ///
    /// \brief SetYaw
    /// \param _yaw - задаем угол поарота - ( лево - право )
    ///
    void SetYaw(float _yaw);

    ///
    /// \brief SetPitch
    /// \param _pitch - задаем угол поарота - ( вверх - вниз )
    ///
    void SetPitch(float _pitch);

    ///
    /// \brief GetYaw - получаем угол поарота - ( лево - право )
    /// \return
    ///
    float GetYaw() const;

    ///
    /// \brief GetPitch - получаем угол поарота - ( вверх - вниз )
    /// \return
    ///
    float GetPitch() const;


    Vector3 m_Origin;  // -- no -- //
    GLWidget *mGlobalScene; // -- no -- //


protected:

    //Quaternion m_InitBasis;
    IOrientationSensor *m_OrientationSensor; // Датчик ориентации

    ActuatorDynamic *m_Actuator1; // Объект для управления актуатором 1
    ActuatorDynamic *m_Actuator2; // Объект для управления актуатором 2


    float m_PositionActuator1; // Точная позиция для актутора 1
    float m_PositionActuator2; // Точная позиция для актутора 1

    float m_Yaw; // угол поарота - ( лево - право )
    float m_Pitch; // угол поарота - ( вверх - вниз )

    float m_PrevYaw;
    float m_PrevPitch;

};

#endif // TRIPODEHARDWARE_H
