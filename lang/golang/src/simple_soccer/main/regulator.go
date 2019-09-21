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
	var dUpdatePeriod = -1
	if NumUpdatesPerSecondRqd > 0 {
		dUpdatePeriod = 1000 / NumUpdatesPerSecondRqd
	} else if NumUpdatesPerSecondRqd == 0 {
		dUpdatePeriod = 0
	}
	nextUpdateTime = time.Now().UnixNano()/1e6 + rand.Int63(1000)
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
	if currentTime >= f.nextUpdateTime {
		f.nextUpdateTime = currentTime + f.dUpdatePeriod + rand.Int63(updatePeriodVariator*2) - updatePeriodVariator
		return true
	}
	return false
}
