package main

import (
	"math/rand"
	"time"
)

const updatePeriodVariator = 10.0

type Regulator struct {
	dUpdatePeriod  int64 //每次间隔（毫秒)
	nextUpdateTime int64 //下次更新时间
}

func NewRegulator(NumUpdatesPerSecondRqd int64) *Regulator {
	var nextUpdateTime int64 = 0
	var dUpdatePeriod int64 = -1
	if NumUpdatesPerSecondRqd > 0 {
		dUpdatePeriod = int64(1000) / NumUpdatesPerSecondRqd
	} else if NumUpdatesPerSecondRqd == 0 {
		dUpdatePeriod = 0
	}
	nextUpdateTime = time.Now().UnixNano()/1e6 + rand.Int63n(1000)
	return &Regulator{
		dUpdatePeriod:  dUpdatePeriod,
		nextUpdateTime: nextUpdateTime,
	}
}

func (r *Regulator) IsReady() bool {
	if r.dUpdatePeriod == 0 {
		return true
	}
	if r.dUpdatePeriod < 0 {
		return false
	}

	var currentTime = time.Now().UnixNano() / 1e6
	if currentTime >= r.nextUpdateTime {
		r.nextUpdateTime = currentTime + r.dUpdatePeriod + rand.Int63n(updatePeriodVariator*2) - updatePeriodVariator
		return true
	}
	return false
}
