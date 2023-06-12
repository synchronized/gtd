package practice

import (
	"errors"
	"fmt"
	"github.com/Knetic/govaluate"
	"testing"
)

type GoValuateUserEntity struct {
	Name string
	Age  int
	Hp   int
	Atk  int
}

func (this *GoValuateUserEntity) GetName() string { return this.Name }
func (this *GoValuateUserEntity) GetAge() int     { return this.Age }
func (this *GoValuateUserEntity) GetHp() int      { return this.Hp }
func (this *GoValuateUserEntity) GetAtk() int     { return this.Atk }

type GoValuateUserEntityParameter struct {
	Attacker *GoValuateUserEntity
	Target   *GoValuateUserEntity
}

func (this *GoValuateUserEntityParameter) Get(name string) (interface{}, error) {
	switch name {
	case "age":
		return this.Attacker.Age, nil
	case "hp":
		return this.Attacker.Hp, nil
	case "atk":
		return this.Attacker.Atk, nil
	case "tgtAge":
		return this.Target.Age, nil
	case "tgtHp":
		return this.Target.Hp, nil
	case "tgtAtk":
		return this.Target.Atk, nil
	default:
		return nil, errors.New("unknow field name:" + name)
	}
}

func BenchmarkGoValuateFunction1(b *testing.B) {
	var express = "user.GetAge + user.GetHp * user.GetAtk + 10001.1010 + user.GetAge + user.GetHp * user.GetAtk"
	expr, err := govaluate.NewEvaluableExpression(express)
	if err != nil {
		b.Logf("build express failed express:%s, err:%s", express, err.Error())
		b.Fail()
		return
	}

	var attacker = &GoValuateUserEntity{"sunday", 10, 20, 30}
	//var target = &GoValuateUserEntity{"target", 100, 200, 300}
	var params = map[string]interface{}{
		"user": attacker,
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, err := expr.Evaluate(params)
		if err != nil {
			b.Logf("build express failed express:%s, err:%s", express, err.Error())
			b.Fail()
			return
		}
		//b.Logf("output:%v", output)
		//b.Logf("output-type:%v", reflect.TypeOf(output).Kind())
		//b.Fail()
		//return
	}
}

func BenchmarkGoValuateFunction2(b *testing.B) {
	var express = "age + hp * atk + 10001.1010 - tgtAge / tgtHp * tgtAtk"
	expr, err := govaluate.NewEvaluableExpression(express)
	if err != nil {
		b.Logf("build express failed express:%s, err:%s", express, err.Error())
		b.Fail()
		return
	}

	var attacker = &GoValuateUserEntity{"sunday", 10, 20, 30}
	var target = &GoValuateUserEntity{"target", 100, 200, 300}
	var params = &GoValuateUserEntityParameter{
		Attacker: attacker,
		Target:   target,
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, err := expr.Eval(params)
		if err != nil {
			b.Logf("build express failed express:%s, err:%s", express, err.Error())
			b.Fail()
			return
		}
		//b.Logf("output:%v", output)
		//b.Logf("output-type:%v", reflect.TypeOf(output).Kind())
		//b.Fail()
		//return
	}
}

func BenchmarkGoValuateFunction3(b *testing.B) {
	var express = "tgtHp*ternary(age > 0, age, 0)+tgtAge"

	functions := map[string]govaluate.ExpressionFunction{
		"ternary": func(args ...interface{}) (interface{}, error) {
			if len(args) != 3 {
				return nil, fmt.Errorf("func must be 3 args len:%v", len(args))
			}
			cond, ok := args[0].(bool)
			if !ok {
				return nil, fmt.Errorf("arg1 must be bool type val:%v", args[0])
			}
			val1, ok := args[1].(float64)
			if !ok {
				return nil, fmt.Errorf("arg2 must be float64 type val:%v", args[0])
			}
			val2, ok := args[2].(float64)
			if !ok {
				return nil, fmt.Errorf("arg3 must be float64 type val:%v", args[0])
			}
			if cond {
				return val1, nil
			}
			return val2, nil
		},
	}

	var attacker = &GoValuateUserEntity{"sunday", 10, 20, 30}
	var target = &GoValuateUserEntity{"target", 100, 200, 300}
	var params = &GoValuateUserEntityParameter{
		Attacker: attacker,
		Target:   target,
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {

		expr, err := govaluate.NewEvaluableExpressionWithFunctions(express, functions)
		if err != nil {
			b.Logf("build express failed express:%s, err:%s", express, err.Error())
			b.Fail()
			return
		}

		_, err = expr.Eval(params)
		if err != nil {
			b.Logf("build express failed express:%s, err:%s", express, err.Error())
			b.Fail()
			return
		}
		//b.Logf("output:%v", output)
		//b.Logf("output-type:%v", reflect.TypeOf(output).Kind())
		//b.Fail()
		//return
	}
}

func TestGoValuateFunction(t *testing.T) {
	var express = "(user.Age > 0), 0"
	expr, err := govaluate.NewEvaluableExpression(express)
	if err != nil {
		t.Logf("build express failed express:%s, err:%s", express, err.Error())
		t.Fail()
		return
	}

	var params = map[string]interface{}{
		"user": &GoValuateUserEntity{"sunday", 1, 200, 3000},
	}

	output, err := expr.Evaluate(params)
	if err != nil {
		t.Logf("build express failed express:%s, err:%s", express, err.Error())
		t.Fail()
		return
	}
	t.Logf("output:%v", output)
	t.Fail()
}
