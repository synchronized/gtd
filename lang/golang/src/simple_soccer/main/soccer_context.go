package main

type SoccerContext struct {
	pDispatcher *MessageDispatcher
	pConfig     *Config
	pEntityMgr  *EntityManager
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
