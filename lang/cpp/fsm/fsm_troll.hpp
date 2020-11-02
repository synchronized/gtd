
class State
{
public:
    virtual void Execute(Troll* troll) = 0;
};

class Troll
{
    State* m_pCurrentState;
public:
    /*省略属性接口*/
    bool isSafe();
    bool isThreatened();
    void Snore();
    void MoveAwayFromEnemy();
    void Update()
    {
        m_pCurrentState->Execute(this);
    }

    void ChangeState(const State* pNewState)
    {
        delete m_pCurrentState;
        m_pCurrentState = pNewState;
    }

};

class State_RunAway: public State
{
public:
    void Execute(Troll* troll)
    {
        if (troll->isSafe()) {
            troll->ChangeState(new State_Sleep());
        } else {
            troll->MoveAwayFromEnemy();
        }
    }
};

class State_Sleep: public State
{
public:
    void Execute(Troll* troll)
    {
        if (troll->isThreatened()) {
            troll->ChangeState(new State_RunAway());
        } else {
            troll->Snore();
        }
    }
};
