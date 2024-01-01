#include "ActuatorHardware.h"

ActuatorHardware::ActuatorHardware()
{

}

void ActuatorHardware::Init()
{
  // Тут иницилизация пинов и каналов для PWM
    //---------------------------------------//


    //---------------------------------------//

    m_CofficientPos = 4.0;
    m_MaxVelocity =  10; // на плате єто
    m_MinVelocity = -10; // на плате єто
}

float ActuatorHardware::GetPosition() const
{
  return m_Position;
}

void ActuatorHardware::UpdatePID(const scalar &_pos)
{
    m_Position = getReadEncoder();
    float fine_pos = _pos;
    float error_pos = ((m_Position - fine_pos) * m_CofficientPos);
    error_pos = IClamp(error_pos, float(m_MinVelocity), float(m_MaxVelocity));
    SetPWM(-error_pos);
    //m_Integral += error * 0.005f;
}

