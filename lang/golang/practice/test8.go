//go:build ignore
// +build ignore

package main

import (
	"fmt"
	"unicode"
	"unicode/utf8"
)

const (
	QuoteFlag_NoPrintError  = 1 << iota //如果遇到不可打印字符则返回错误
	QuoteFlag_NoPrintFilter             //如果遇到不可打印字符则去除
)

const lowerhex = "0123456789abcdef"

func QuoteWith(s string, quote byte, flag int) (string, error) {
	var err error
	var buf = make([]byte, 0, 3*len(s)/2)
	buf = append(buf, quote)
	var runeTmp [utf8.UTFMax]byte
	for width := 0; len(s) > 0; s = s[width:] {
		r := rune(s[0])
		width = 1
		if r >= utf8.RuneSelf {
			r, width = utf8.DecodeRuneInString(s)
		}
		if width == 1 && r == utf8.RuneError {
			var bufTmp = runeTmp[:]
			bufTmp = append(bufTmp, `\x`...)
			bufTmp = append(bufTmp, lowerhex[s[0]>>4])
			bufTmp = append(bufTmp, lowerhex[s[0]&0xF])
			if flag&QuoteFlag_NoPrintError > 0 {
				err = fmt.Errorf("遇到不可打印字符:%s", string(bufTmp))
				return string(buf), err
			}
			if flag&QuoteFlag_NoPrintFilter == 0 {
				buf = append(buf, bufTmp...)
			}
			continue
		}
		buf, err = appendEscapedRune(buf, r, quote, false, false, flag)
		if err != nil {
			return string(buf), err
		}
	}
	buf = append(buf, quote)
	return string(buf), err
}

func appendEscapedRune(buf []byte, r rune, quote byte, ASCIIonly, graphicOnly bool, flag int) ([]byte, error) {
	var err error
	var runeTmp [utf8.UTFMax]byte
	if r == rune(quote) || r == '\\' { // always backslashed
		buf = append(buf, '\\')
		buf = append(buf, byte(r))
		return buf, err
	}
	if ASCIIonly {
		if r < utf8.RuneSelf && unicode.IsPrint(r) {
			buf = append(buf, byte(r))
			return buf, err
		}
	} else if unicode.IsPrint(r) || graphicOnly && unicode.IsGraphic(r) {
		n := utf8.EncodeRune(runeTmp[:], r)
		buf = append(buf, runeTmp[:n]...)
		return buf, err
	}
	switch r {
	case '\a':
		buf = append(buf, `\a`...)
	case '\b':
		buf = append(buf, `\b`...)
	case '\f':
		buf = append(buf, `\f`...)
	case '\n':
		buf = append(buf, `\n`...)
	case '\r':
		buf = append(buf, `\r`...)
	case '\t':
		buf = append(buf, `\t`...)
	case '\v':
		buf = append(buf, `\v`...)
	default:
		var bufTmp = runeTmp[:]
		switch {
		case r < ' ':
			bufTmp = append(bufTmp, `\x`...)
			bufTmp = append(bufTmp, lowerhex[byte(r)>>4])
			bufTmp = append(bufTmp, lowerhex[byte(r)&0xF])
		case r > utf8.MaxRune:
			r = 0xFFFD
			fallthrough
		case r < 0x10000:
			bufTmp = append(bufTmp, `\u`...)
			for s := 12; s >= 0; s -= 4 {
				bufTmp = append(bufTmp, lowerhex[r>>uint(s)&0xF])
			}
		default:
			bufTmp = append(bufTmp, `\U`...)
			for s := 28; s >= 0; s -= 4 {
				bufTmp = append(bufTmp, lowerhex[r>>uint(s)&0xF])
			}
		}
		if flag&QuoteFlag_NoPrintError > 0 {
			err = fmt.Errorf("遇到不可打印字符:%s", string(bufTmp))
			return buf, err
		}
		if flag&QuoteFlag_NoPrintFilter == 0 {
			buf = append(buf, bufTmp...)
		}
	}
	return buf, err
}

func main() {
	var origStr = `这是一个转译字符串\"\" "\\`
	var str2 = "向上人生‭"
	var rStr2 = []rune(str2)
	for _, r := range rStr2 {
		fmt.Printf("%v: %t\n", r, unicode.IsPrint(r))
	}
	fmt.Printf("\n")
	var result, err = QuoteWith(origStr, '"', QuoteFlag_NoPrintError)
	fmt.Printf("origStr: %s, err: %v\n", result, err)
	result, err = QuoteWith(str2, '"', QuoteFlag_NoPrintFilter)
	fmt.Printf("str2: %s, err: %v\n", result, err)
}
