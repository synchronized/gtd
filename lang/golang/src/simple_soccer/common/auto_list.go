
type AutoList struct {
	members []interface{}
}

func (al *AutoList) GetAllMembers() []interface{} {
	return al.members
}
