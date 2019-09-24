package main

type SoccerContext struct {
	pDispatcher *MessageDispatcher
	pConfig     *Config
	pEntityMgr  *EntityManager
}

func NewSoccerContext() *SoccerContext {
	return &SoccerContext{}
}

func (sc *SoccerContext) Dispatcher() *MessageDispatcher {
	return sc.pDispatcher
}

func (sc *SoccerContext) Config() *Config {
	return sc.pConfig
}

func (sc *SoccerContext) EntityMgr() *EntityManager {
	return sc.pEntityMgr
}

func (sc *SoccerContext) SetDispatcher(dispatcher *MessageDispatcher) {
	sc.pDispatcher = dispatcher
}

func (sc *SoccerContext) SetConfig(config *Config) {
	sc.pConfig = config
}

func (sc *SoccerContext) SetEntityMgr(entityMgr *EntityManager) {
	sc.pEntityMgr = entityMgr
}
