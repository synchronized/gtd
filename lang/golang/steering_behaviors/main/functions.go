package main

import "math/rand"

func TrunaroundTime(pAgent *Vehicle, target Vector2d) float64 {
	//确定到目标的标准化向量
	var toTarget Vector2d = target.OpMinus(pAgent.Pos()).Normalize()
	var dot float64 = pAgent.Heading().Dot(toTarget)
	//改变这个值得到预期行为
	//交通工具的最大转弯率越高，这个值越大
	//如果交通工具正在朝目标位置的反方向
	//那么0.5这个值意味着这个函数返回疫苗的时间以便让交通工具转弯
	const double coefficient = 0.5

	//如果目标直接在前面，那么点积为1
	//如果目标直接在后面,那么点积为-1
	//减去1,初一负的cofficient, 得到一个正的值
	//且正比于交通工具和目标的转动角位移
	return (dot - 1.0) * -coefficient

}

func RandomClamped() float64 {
	return rand.Float64()*2 - 1
}

func PointToWorldSpace() Vector2d {

	//TODO
}
