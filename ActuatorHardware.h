#ifndef ACTUATORHARDWARE_H
#define ACTUATORHARDWARE_H

#include <IEngineComponent/IComponents.hpp>
#include <Sensors/ISensors.hpp>

class ActuatorHardware
{
public:
    ActuatorHardware();

    void Init(); // Иницилизация

    scalar GetPosition() const; // Текущая позиция актутора
    virtual scalar getReadEncoder() const = 0;  // тут свою реализцаю получить по позицию акуттора по енкодеру
    virtual void SetPWM( float _pwm_vel ) = 0; // тут свою реализцаю как дать сигнал на мотор акутуатора

    ///
    /// \brief UpdatePID - Функция стабилизации актутора по обратной связи Encoder
    /// \param _pos - Желаемая позиция актуатора
    ///
    void UpdatePID(const scalar &_pos);

protected:

    float m_Position; // Текущая позиция актутора
    float m_CofficientPos; // Коефициент стабилизации по позиции

    float m_MaxVelocity; // Максимальная скорость PWM , которая ровна  2^bits_pwm
    float m_MinVelocity; // Максимальная скорость PWM , которая ровна -2^bits_pwm



};

#endif // ACTUATORHARDWARE_H
