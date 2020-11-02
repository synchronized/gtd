/******************* Location ****************/
enum location_type{
    goldmine = 1; //金矿
};

/******************* Entity ****************/
class BaseGameEntity
{
private:
    int m_ID;
    static int m_iNextValidID;
    void SetID(int val);

public:
    BaseGameEntity(int id) {
        SetID(id);
    }

    virtual ~BaseGameEntity() {}
    virtual void Update()=0;
    int ID()const {return m_ID;}
};

class Miner: public BaseGameEntity
{
private:
    //状态
    State* m_pCurrentState;
    //位置
    location_type m_Location;
    //金块
    int m_iGoldCarried;
    //矿工银行存款
    int m_iMoneyInBank;
    //口渴程度
    int m_iThirst;
    //疲劳
    int m_iFatigue;
public:
    Miner(int ID);
    //更新
    void Update() {
        m_iThirst += 1;
        if (m_pCurrentState) {
            m_pCurrentState->Execute(this);
        }
    }
    //状态改变
    void ChangeState(State *pNewState) {
        assert( m_pCurrentState && pNewState);
        if (m_pCurrentState) {
            m_pCurrentState->Exit(this);
        }
        m_pCurrentState = pNewState;
        m_pCurrentState->Enter(this);
    }
    void ChangeLocation(location_type location) {
        m_Location = location;
    }
    void AddToGoldCarried(int iNum) {
        m_iGoldCarried += iNum;
    }
    void IncreaseFatigue() {
        m_iFatigue += 1;
    }
    bool isPocketsFull() {
        return m_iGoldCarried > 50;
    }
    bool isThirst() {
        return m_iThirst > 50;
    }
};

/******************* State ****************/
class State
{
public:
    virtual ~State() {}
    virtual void Enter(Miner*)=0;
    virtual void Execute(Miner*)=0;
    virtual void Exit(Miner*)=0;
};

class EnterMinerAndDigForNugger: public State
{
private:
    EnterMinerAndDigForNugger() {}
    //ctor
public:
    static EnterMinerAndDigForNugger* Instance();
    virtual void Enter(Miner*);
    virtual void Execute(Miner*);
    virtual void Exit(Miner*);
};

void EnterMinerAndDigForNugger::Enter(Miner *pMiner)
{
    count << "\n" << GetNameOfEntity(pMiner->Id()) << ":"
          << "Walkin' to the gold mine";
    pMiner->ChangeLocation(goldmine);
}

void EnterMinerAndDigForNugger::Execute(Miner *pMiner)
{
    //增加金块
    pMiner->AddToGoldCarried(1);
    //增加疲劳
    pMiner->IncreaseFatigue();
    cout << "\n" << GetNameOfEntity(pMiner->id()) << ":"
         << "Pickin' up a nugget";
    //如果开采足够的金子
    if (pMiner->isPocketsFull()) {
        pMiner->ChangeState(VisitBankAndDepositGold::Instance())
    }
    if (pMiner->isThirst()) {
        pMiner->ChangeState(QuenchThirst::Instance())
    }
}

void EnterMinerAndDigForNugger::Enter(Miner *pMiner)
{
    count << "\n" << GetNameOfEntity(pMiner->Id()) << ":"
          << "Ah'm leavin' the gold mine with mah pockets full o' sweet gold";
}

class VisitBankAndDepositGold: public State
{

};

class QuenchThirst: public State
{

}
