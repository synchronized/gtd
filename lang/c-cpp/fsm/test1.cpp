
class Vehicle
{
    //在空间中用一个矢量表示车的位置
    vector m_vPosition;
    //速度
    vector m_vVelocity;
public:
    //每一帧更新车的位置
    void Update(float TimeElapsedSinceLastUpdate)
    {
        m_vPosition += m_vVelocity * TimeElapsedSinceLastUpdate;
    }
    //如果你的游戏对物理学特性使用的是固定刷新频率
    void Update()
    {
        m_vPosition += m_vVelocity;
    }
};

class SpaceShip
{
    //位置
    vector m_vPosition;
    //速度
    vector m_vVelocity;
    //质量
    float m_fMass;
public:
    void Update(float TimeElapsedSinceLastUpdate, float ForceOnShip)
    {
        float acceleration = ForceOnShip / m_fMass;
        m_vVelocity += acceleration * TimeElapsedSinceLastUpdate;
        m_vPosition += m_vVelocity * TimeElapsedSinceLastUpdate;
    }
}
