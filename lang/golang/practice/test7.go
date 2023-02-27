//go:build ignore
// +build ignore

package main

import (
	"os"
	"text/template"
)

var TemplateConfigLua = `-- Generator by Zhougames tool ReadExcel
local Conf_{{ .tableInfo.Name }} = {\n
    _ID = table.resize_array({
        {{- range .tableInfo.FieldId.LuaData -}}
        {{ .Val }},
        {{- end -}}
    }),
    {{- range $colIdx, $field := .tableInfo.FieldList -}}
    {{- if $field.LuaUseIndex }}
    {{ $field.Name }} = {["_default"]={{ $field.LuaDefaultVal }},
    {{- if $field.LuaNeedLoad -}}["_needLoad"]=true,{{- end -}}
    {{- range $rowIdx, $cell := $field.LuaData -}}
        {{- if ne $field.LuaDefaultVal $cell.Val -}}
        [{{ $rowIdx | AddOne }}]={{ $cell.Val }},
        {{- end -}}
    {{- end -}}
    },
    {{- else }}
    {{ $field.Name }} = table.resize_array({
    {{- range $rowIdx, $cell := $field.LuaData -}}
        {{- $cell.Val -}},
    {{- end -}}
    }{{- if $field.LuaNeedLoad -}}{["_needLoad"]=true}{{- end -}}),
    {{- end }}
    {{- end }}
}
Conf_{{ .tableInfo.Name }}.MinID = {{ .tableInfo.LuaMinId }}
Conf_{{ .tableInfo.Name }}.MaxID = {{ .tableInfo.LuaMaxId }}
setmetatable(Conf_{{ .tableInfo.Name }}, conf_base)
return Conf_{{ .tableInfo.Name }}

`

var TemplateConfigLuaTemp = `-- Generator by Zhougames tool ReadExcel
local Conf_{{ .tableInfo.Name }}={}
{{- range $rowIdx, $cell := .tableInfo.FieldId.LuaData }}
Conf_{{ $.tableInfo.Name }}[{{ $cell.ValTmp }}]={
{{- range $colIdx, $field := $.tableInfo.FieldList }}
{{- $cell := (index $field.LuaData $rowIdx) }}
{{- $field.Name -}}={{- $cell.ValTmp -}},
{{- end -}}
}
{{- end }}
return Conf_{{ .tableInfo.Name }}

`

//马甲包
var TemplateConfigLuaFake = `-- Generator by Zhougames tool ReadExcel
{{ range $rowIdx, $cell := .tableInfo.FieldId.LuaData -}}
Conf_{{ $.tableInfo.Name }}[{{ $cell.ValTmp }}]={
{{- range $colIdx, $field := $.tableInfo.FieldList }}
{{- $cell := (index $field.LuaData $rowIdx) }}
{{- $field.Name -}}={{- $cell.ValTmp }},
{{- end -}}
}
{{ end }}

`

//readall
var TemplateConfigLuaReadAll = `
local function Loadfile(path)
	local lua, err = loadfile(path)
	if err then
		Util.LogError('luaData Loadfile error: ' .. err  )
		return function ()	end
	else
		return lua
	end
end
{{ range $tableName := .tableList }}
Conf_{{ $tableName }} = Loadfile("Data/{{ $.DataPath }}{{ $tableName }}")()
{{- end -}}
`

//lua 字段数据
type LuaFieldData struct {
	//TODO
	Val    string //正式值
	ValTmp string //未优化的值
}

//字段信息
type FieldInfo struct {
	Name          string //字段名(英文)
	Note          string //字段名(中文)
	GoType        string //Go字段类型
	FnGoConv      string //Go字段转换函数
	FnGoConvType  int    //Go字段转换函数类型(见上面: FnGoConvType)
	Required      bool   //是否必填
	LuaRequired   bool   //是否生成lua代码
	LuaNeedLoad   bool   //是否需要加载
	LuaUseIndex   bool   //大于一定比例使用索引方式
	LuaDefaultVal string //大于一定比例使用索引方式(默认值)

	LuaData []*LuaFieldData //lua数据
}

type TableInfo struct {
	Name      string       //原filename
	LuaMinId  int          //最小值
	LuaMaxId  int          //最大值
	FieldId   *FieldInfo   //id字段信息
	FieldList []*FieldInfo //字段列表
}

func genData() map[string]interface{} {
	var fieldId = &FieldInfo{
		Name:          "Id",
		Note:          "活动id",
		LuaRequired:   true,
		LuaNeedLoad:   false,
		LuaUseIndex:   false,
		LuaDefaultVal: "",
		LuaData: []*LuaFieldData{
			&LuaFieldData{Val: "1", ValTmp: "1"},
			&LuaFieldData{Val: "2", ValTmp: "2"},
			&LuaFieldData{Val: "3", ValTmp: "3"},
			&LuaFieldData{Val: "4", ValTmp: "4"},
			&LuaFieldData{Val: "5", ValTmp: "5"},
			&LuaFieldData{Val: "6", ValTmp: "6"},
		},
	}

	var fieldList = []*FieldInfo{
		fieldId,
		&FieldInfo{
			Name:          "NameId",
			Note:          "活动名称id",
			LuaRequired:   true,
			LuaNeedLoad:   false,
			LuaUseIndex:   false,
			LuaDefaultVal: "",
			LuaData: []*LuaFieldData{
				&LuaFieldData{Val: "101", ValTmp: "101"},
				&LuaFieldData{Val: "102", ValTmp: "102"},
				&LuaFieldData{Val: "103", ValTmp: "103"},
				&LuaFieldData{Val: "104", ValTmp: "104"},
				&LuaFieldData{Val: "105", ValTmp: "105"},
				&LuaFieldData{Val: "106", ValTmp: "106"},
			},
		},
		&FieldInfo{
			Name:          "Weight",
			Note:          "概率",
			LuaRequired:   true,
			LuaNeedLoad:   true,
			LuaUseIndex:   false,
			LuaDefaultVal: "",
			LuaData: []*LuaFieldData{
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
				&LuaFieldData{Val: "'{1,2,3}'", ValTmp: "{1,2,3}"},
			},
		},
		&FieldInfo{
			Name:          "Age",
			Note:          "年龄",
			LuaRequired:   true,
			LuaNeedLoad:   false,
			LuaUseIndex:   true,
			LuaDefaultVal: "18",
			LuaData: []*LuaFieldData{
				&LuaFieldData{Val: "18", ValTmp: "18"},
				&LuaFieldData{Val: "18", ValTmp: "18"},
				&LuaFieldData{Val: "19", ValTmp: "19"},
				&LuaFieldData{Val: "20", ValTmp: "20"},
				&LuaFieldData{Val: "18", ValTmp: "18"},
				&LuaFieldData{Val: "21", ValTmp: "21"},
			},
		},
	}
	return map[string]interface{}{
		"tableInfo": &TableInfo{
			Name:      "Activity",
			LuaMinId:  1,
			LuaMaxId:  6,
			FieldId:   fieldId,
			FieldList: fieldList,
		},
		"DataPath": "XM/Android/",
		"tableList": []string{"Activity", "LanguageByCH", "Player"},
	}
}

type TeamplateMeta struct {
	Name        string //模板名称
	TempContent string //模板内容
}

func main() {
	var templateList = []*TeamplateMeta{
		&TeamplateMeta{"t1", TemplateConfigLua},
		&TeamplateMeta{"t2", TemplateConfigLuaTemp},
		&TeamplateMeta{"t3", TemplateConfigLuaFake},
		&TeamplateMeta{"t4", TemplateConfigLuaReadAll},
	}
	for _, tm := range templateList {
		var template1, err = template.New(tm.Name).Funcs(template.FuncMap{
			"AddOne": func(i int) int {
				return i+1
			},
		}).Parse(tm.TempContent)
		if err != nil {
			panic(err)
		}
		err = template1.Execute(os.Stdout, genData())
		if err != nil {
			panic(err)
		}
	}
}
