package main

import "github.com/go-init/init"

type Config struct {
	//MinDetectionBoxLength        float64 //检测盒长度
	//Friction                     float64 //球的摩擦力大小
	//NumAttemptsToFindValidStrike int     //随机创建的射击目标数
	//MaxPassingForce              float64 //最大传球力
	//MaxShootingForce             float64 //最大射门力量
	//MaxDribbleForce              float64 //最大运球力量
	//MinPassDist                  float64 //最小传球距离

	//PlayerMass                             float64 //角色质量
	//PlayerMaxForce                         float64 //最大力量
	//PlayerMaxSpeedWithoutBall              float64 //最大速度带球
	//PlayerMaxTurnRate                      float64 //最大转向角度
	//PlayerMaxSpeedWithBall                 float64 //最大踢球速度
	//PlayerScale                            float64 //
	//PlayerComfortZoneSq                    float64 //舒适区范围
	//KeeperInBallRangeSq                    float64 //持球队员范围的平方
	//BallWithinReceivingRangeSq             float64 //接球范围平方
	//PlayerKickingDistanceSq                float64 //踢球范围-距离平方
	//PlayerInTargetRangeSq                  float64 //
	//PlayerKickFrequency                    int64   //玩家踢球频率(每秒多少次)
	//BNonPenetrationConstraint              float64
	//GoalKeeperInterceptRangeSq             float64 //球和球门距离少于这个值，守门员拦截球
	//GoalKeeperTendingDistance              float64 //守门员抢球距离
	//GoalkeeperMinPassDist                  float64 //守门员最大传球距离
	//GoalWidth                              float64 //球的宽度
	//ChancePlayerAttemptsPotShot            float64 //球员射门几率(小于1)
	//ChanceOfUsingArriveTypeReceiveBehavior float64 //接球行为纪律
	//SupportSpotUpdateFreq                  int64   //助攻点计算频率
	//Spot_PassSafeScore                     float64 //助攻点分数计算-可传球分数
	//Spot_CanScoreFromPositionScore         float64 //助攻点分数计算-能射门得分
	//Spot_DistFromControllingPlayerScore    float64 //助攻点分数计算-控球员和点距离

	GoalWidth float64

	NumSupportSpotsX int
	NumSupportSpotsY int

	Spot_PassSafeScore                    float64
	Spot_CanScoreFromPositionScore        float64
	Spot_DistFromControllingPlayerScore   float64
	Spot_ClosenessToSupportingPlayerScore float64
	Spot_AheadOfAttackerScore             float64

	SupportSpotUpdateFreq float64

	ChancePlayerAttemptsPotShot            float64
	ChanceOfUsingArriveTypeReceiveBehavior float64

	BallSize float64
	BallMass float64
	Friction float64

	KeeperInBallRange     float64
	PlayerInTargetRange   float64
	PlayerKickingDistance float64
	PlayerKickFrequency   float64

	PlayerMass                float64
	PlayerMaxForce            float64
	PlayerMaxSpeedWithBall    float64
	PlayerMaxSpeedWithoutBall float64
	PlayerMaxTurnRate         float64
	PlayerScale               float64
	PlayerComfortZone         float64
	PlayerKickingAccuracy     float64

	NumAttemptsToFindValidStrike int

	MaxDribbleForce  float64
	MaxShootingForce float64
	MaxPassingForce  float64

	WithinRangeOfHome        float64
	WithinRangeOfSupportSpot float64

	MinPassDist           float64
	GoalkeeperMinPassDist float64

	GoalKeeperTendingDistance float64
	GoalKeeperInterceptRange  float64
	BallWithinReceivingRange  float64

	bStates                bool
	bIDs                   bool
	bSupportSpots          bool
	bRegions               bool
	bShowControllingTeam   bool
	bViewTargets           bool
	bHighlightIfThreatened bool

	FrameRate int

	SeparationCoefficient     float64
	ViewDistance              float64
	bNonPenetrationConstraint bool
}

func LoadConfig() *Config {
	cfg, err := init.Load("params.ini")
	if err != nil {
		panic(err.Error())
	}
	var defaultSection = cfg.Section("")
	var config = &Config{
		GoalWidth: defaultSection.Key("GoalWidth").MustFloat64(1.0),

		NumSupportSpotsX: defaultSection.Key("NumSupportSpotsX").MustInt(1),
		NumSupportSpotsY: defaultSection.Key("NumSupportSpotsY").MustInt(1),

		Spot_PassSafeScore:                    defaultSection.Key("Spot_PassSafeScore").MustFloat64(1.0),
		Spot_CanScoreFromPositionScore:        defaultSection.Key("Spot_CanScoreFromPositionScore").MustFloat64(1.0),
		Spot_DistFromControllingPlayerScore:   defaultSection.Key("Spot_DistFromControllingPlayerScore").MustFloat64(1.0),
		Spot_ClosenessToSupportingPlayerScore: defaultSection.Key("Spot_ClosenessToSupportingPlayerScore").MustFloat64(1.0),
		Spot_AheadOfAttackerScore:             defaultSection.Key("Spot_AheadOfAttackerScore").MustFloat64(1.0),

		SupportSpotUpdateFreq: defaultSection.Key("SupportSpotUpdateFreq").MustFloat64(1.0),

		ChancePlayerAttemptsPotShot:            defaultSection.Key("ChancePlayerAttemptsPotShot").MustFloat64(1.0),
		ChanceOfUsingArriveTypeReceiveBehavior: defaultSection.Key("ChanceOfUsingArriveTypeReceiveBehavior").MustFloat64(1.0),

		BallSize: defaultSection.Key("BallSize").MustFloat64(1.0),
		BallMass: defaultSection.Key("BallMass").MustFloat64(1.0),
		Friction: defaultSection.Key("Friction").MustFloat64(1.0),

		KeeperInBallRange:     defaultSection.Key("KeeperInBallRange").MustFloat64(1.0),
		PlayerInTargetRange:   defaultSection.Key("PlayerInTargetRange").MustFloat64(1.0),
		PlayerKickingDistance: defaultSection.Key("PlayerKickingDistance").MustFloat64(1.0),
		PlayerKickFrequency:   defaultSection.Key("PlayerKickFrequency").MustFloat64(1.0),

		PlayerMass:                defaultSection.Key("PlayerMass").MustFloat64(1.0),
		PlayerMaxForce:            defaultSection.Key("PlayerMaxForce").MustFloat64(1.0),
		PlayerMaxSpeedWithBall:    defaultSection.Key("PlayerMaxSpeedWithBall").MustFloat64(1.0),
		PlayerMaxSpeedWithoutBall: defaultSection.Key("PlayerMaxSpeedWithoutBall").MustFloat64(1.0),
		PlayerMaxTurnRate:         defaultSection.Key("PlayerMaxTurnRate").MustFloat64(1.0),
		PlayerScale:               defaultSection.Key("PlayerScale").MustFloat64(1.0),
		PlayerComfortZone:         defaultSection.Key("PlayerComfortZone").MustFloat64(1.0),
		PlayerKickingAccuracy:     defaultSection.Key("PlayerKickingAccuracy").MustFloat64(1.0),

		NumAttemptsToFindValidStrike: defaultSection.Key("NumAttemptsToFindValidStrike").MustInt(1),

		MaxDribbleForce:  defaultSection.Key("MaxDribbleForce").MustFloat64(1.0),
		MaxShootingForce: defaultSection.Key("MaxShootingForce").MustFloat64(1.0),
		MaxPassingForce:  defaultSection.Key("MaxPassingForce").MustFloat64(1.0),

		WithinRangeOfHome:        defaultSection.Key("WithinRangeOfHome").MustFloat64(1.0),
		WithinRangeOfSupportSpot: defaultSection.Key("WithinRangeOfSupportSpot").MustFloat64(1.0),

		MinPassDist:           defaultSection.Key("MinPassDist").MustFloat64(1.0),
		GoalkeeperMinPassDist: defaultSection.Key("GoalkeeperMinPassDist").MustFloat64(1.0),

		GoalKeeperTendingDistance: defaultSection.Key("GoalKeeperTendingDistance").MustFloat64(1.0),
		GoalKeeperInterceptRange:  defaultSection.Key("GoalKeeperInterceptRange").MustFloat64(1.0),
		BallWithinReceivingRange:  defaultSection.Key("BallWithinReceivingRange").MustFloat64(1.0),

		bStates:                defaultSection.Key("bStates").MustBool(false),
		bIDs:                   defaultSection.Key("bIDs").MustBool(false),
		bSupportSpots:          defaultSection.Key("bSupportSpots").MustBool(false),
		bRegions:               defaultSection.Key("bRegions").MustBool(false),
		bShowControllingTeam:   defaultSection.Key("bShowControllingTeam").MustBool(false),
		bViewTargets:           defaultSection.Key("bViewTargets").MustBool(false),
		bHighlightIfThreatened: defaultSection.Key("bHighlightIfThreatened").MustBool(false),

		FrameRate: defaultSection.Key("FrameRate").MustInt(1),

		SeparationCoefficient:     defaultSection.Key("SeparationCoefficient").MustFloat64(1.0),
		ViewDistance:              defaultSection.Key("ViewDistance").MustFloat64(1.0),
		bNonPenetrationConstraint: defaultSection.Key("bNonPenetrationConstraint").MustBool(false),
	}

	config.BallWithinReceivingRangeSq = config.BallWithinReceivingRange * config.BallWithinReceivingRange
	config.KeeperInBallRangeSq = config.KeeperInBallRange * config.KeeperInBallRange
	config.PlayerInTargetRangeSq = config.PlayerInTargetRange * config.PlayerInTargetRange
	config.PlayerKickingDistance += config.BallSize
	config.PlayerKickingDistanceSq = config.PlayerKickingDistance * config.PlayerKickingDistance
	config.PlayerComfortZoneSq = config.PlayerComfortZone * config.PlayerComfortZone
	config.GoalKeeperInterceptRangeSq = config.GoalKeeperInterceptRange * config.GoalKeeperInterceptRange
	config.WithinRangeOfSupportSpotSq = config.WithinRangeOfSupportSpot * config.WithinRangeOfSupportSpot
	return config
}
