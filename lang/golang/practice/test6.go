//go:build ignore
// +build ignore

package main

import (
	"os"
	"text/template"
)

var t1 = `package {{ .packageName }}

import(
    "MyEngine/mlog"
    "MyEngine/stack"

    "fmt"
    "strconv"
    "strings"
    "errors"

    "github.com/go-ffmt/ffmt"
)

var Map{{ .tableInfo.Name }} map[string]map[int]*Conf_{{ .tableInfo.Name }}
var map{{ .tableInfo.Name }}Bak map[string]map[int]*Conf_{{ .tableInfo.Name }}

type Conf_{{ .tableInfo.Name }} struct{
{{- range .tableInfo.FieldList }}
    {{ .Name }} {{ .Type }} //{{ .Note }}
{{- end }}
}
`

type FieldInfo struct {
	Name string
	Type string
	Note string
}

type TableInfo struct {
	Name      string
	FieldList []*FieldInfo
}

func main() {
	if true { return }

	var template1, err = template.New("temp1").Parse(t1)
	if err != nil {
		panic(err)
	}
	template1.Execute(os.Stdout, map[string]interface{}{
		"packageName": "msg",
		"tableInfo": &TableInfo{
			Name: "Activity",
			FieldList: []*FieldInfo{
				&FieldInfo{"Id", "int", "活动id"},
				&FieldInfo{"NameId", "int", "活动名称id"},
			},
		},
	})
}
