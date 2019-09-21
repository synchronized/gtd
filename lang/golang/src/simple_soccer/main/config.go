package main

type Config struct {
	MinDetectionBoxLength        float64 //检测盒长度
	Friction                     float64 //球的摩擦力大小
	NumAttemptsToFindValidStrike int     //随机创建的射击目标数
	MaxPassingForce              float64 //最大传球力

	PlayerMass                 float64 //角色质量
	PlayerMaxForce             float64 //最大力量
	PlayerMaxSpeedWithoutBall  float64 //最大速度带球
	PlayerMaxTurnRate          float64 //最大转向角度
	PlayerMaxSpeedWithBall     float64 //最大踢球速度
	PlayerScale                float64 //
	PlayerComfortZoneSq        float64 //舒适区范围
	KeeperInBallRangeSq        float64 //持球队员范围的平方
	BallWithinReceivingRangeSq float64 //接球范围平方
	PlayerKickingDistanceSq    float64 //踢球范围-距离平方
	PlayerInTargetRangeSq      float64 //
	PlayerKickFrequency        int64   //玩家踢球频率(每秒多少次)
	BNonPenetrationConstraint  float64
	GoalKeeperInterceptRangeSq float64 //球和球门距离少于这个值，守门员拦截球
	GoalKeeperTendingDistance  float64 //守门员抢球距离
	GoalWidth                  float64 //球的宽度
}
