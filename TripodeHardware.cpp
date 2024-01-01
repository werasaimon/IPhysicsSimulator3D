#include "TripodeHardware.h"

TripodeHardware::TripodeHardware(GLWidget *_globalScene_)
    : mGlobalScene(_globalScene_)
{
    this->Init(_globalScene_);
}

void TripodeHardware::Init(GLWidget *_globalScene_)
{

    m_Yaw = 0; // Обнуляем угол при старте
    m_Pitch = 0; // Обнуляем угол при старте
    //m_PositionActuator1 = m_PositionActuator2 = 0;

    m_Origin = Vector3(0,0,-10); // -- no -- //
    m_PositionActuator1 = m_PositionActuator2 = 0; // Обнуляем позиции актуторов

    //------ у тебя тут иницилизация  по своиму пин  и.т.д ------//

    Vector3 a_p1 = Vector3(12,-4,0) + m_Origin; // -- no -- //
    Vector3 a_p2 = Vector3(4,2,10) + m_Origin; // -- no -- //
    m_Actuator1 = new ActuatorDynamic(a_p1,a_p2,mGlobalScene,0); // Тут своя инцилизация обекта для управления актутором 1

    Vector3 b_p1 = Vector3(-12,-4,0) + m_Origin; // -- no -- //
    Vector3 b_p2 = Vector3(-4,2,10) + m_Origin; // -- no -- //
    m_Actuator2 = new ActuatorDynamic(b_p1,b_p2,mGlobalScene,0); // Тут своя инцилизация обекта для управления актутором 2

    //-----------------------------------------------------------//
}


void TripodeHardware::Update()
{
    // Задаем вращения через позиционие соотношение
    m_PositionActuator1 = m_Pitch + m_Yaw;
    m_PositionActuator2 = m_Pitch - m_Yaw;

    m_Actuator1->UpdatePID(m_PositionActuator1);
    m_Actuator2->UpdatePID(m_PositionActuator2);
}


void TripodeHardware::UpdateLQR(const Vector3& control_euler_angle)
{
    Quaternion quaternion_feedback_sensor = m_OrientationSensor->getQuaternion(); //  Кватернион который получаем из датчика ориентации
    ///
    /// \brief QuadControl - Кватернион клиентского поворота
    ///
    Quaternion QuadControl = Quaternion::FromAngleAxis(Vector3::Z, IMath::IDegreesToRadians(control_euler_angle.y)) * // Поворот вокрну оси Z
                             Quaternion::FromAngleAxis(Vector3::X, IMath::IDegreesToRadians(control_euler_angle.x)) * // Поворот вокрну оси X
                             Quaternion::FromAngleAxis(Vector3::Y, IMath::IDegreesToRadians(control_euler_angle.z));  // Поворот вокрну оси Y
    QuadControl.Normalize(); // Нормализация кватерниона
    QuadControl = QuadControl.GetConjugate(); // Сопряжения кватерниона самому себе !


    /// \brief common_quat - Общий кватернино кторий являеться перемноженими всеми кватернионами
    Quaternion common_quat = (QuadControl * /*m_InitBasis */ quaternion_feedback_sensor);

    /// \brief euler - Получаем с общего кватернина [common_quat] угли ейлера [euler]
    Vector3 euler = (common_quat).GetEulerAngleGimbalLock(Quaternion::RotSeq::zxy);

    float real_yaw = euler.x; // Стабилизирований угол поврота по - Yaw (лево - право)
    float real_pitch = euler.y; // Стабилизирований угол поврота по - Pitch (вверх - низ )

    float elapsedTime = 1.0;// / 60.f; // временой шаг
    float velocity_yaw = (m_PrevYaw - real_yaw) * elapsedTime; // скорость вращения по Yaw`= (yaw` - yaw)/dt Произвдная первого порядка от Yaw
    float velocity_pitch = (m_PrevPitch - real_pitch) * elapsedTime; // скорость вращения по Pitch`= (pitch` - pitch)/dt Произвдная первого порядка от Pitch

    float ButterworthFilterCoefficientPos = 0.15f; // коэффициент обратной связи , стабилизации по позиции
    float ButterworthFilterCoefficientVel = 0.015f; // коэффициент обратной связи , стабилизации по скорости
    float Resolution = 1; // коэффициент сили стабизации

    m_Yaw -= (real_yaw * ButterworthFilterCoefficientPos - velocity_yaw * ButterworthFilterCoefficientVel) * Resolution; // Стабилизация по углу Yaw
    m_Pitch -= (real_pitch * ButterworthFilterCoefficientPos - velocity_pitch * ButterworthFilterCoefficientVel) * Resolution; // Стабилизация по углу Pitch

    m_PrevYaw = real_yaw; // сохраняем текущий угол Yaw  , для взятия производной на следущей итерации
    m_PrevPitch = real_pitch; // сохраняем текущий угол Pitch , для взятия производной на следущей итерации

}


void TripodeHardware::SetPitch(float _yaw)
{
    m_Pitch = _yaw;
}

void TripodeHardware::SetYaw(float _pitch)
{
    m_Yaw = _pitch;
}


float TripodeHardware::GetPitch() const
{
    return m_Pitch;
}

float TripodeHardware::GetYaw() const
{
    return m_Yaw;
}



