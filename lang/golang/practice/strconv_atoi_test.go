package practice

import (
	"strconv"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestStrconvAtoi(t *testing.T) {
	var i, err = strconv.Atoi("")
	assert.NotEqual(t, err, nil)
	assert.Equal(t, i, 0)
}
