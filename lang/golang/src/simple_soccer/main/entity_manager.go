package main

type EntityManager struct {
	entityMap map[int]common.IBaseGameEntity
}

func NewEntityManager() *EntityManager {
	var em = &EntityManager{}
	em.entityMap = make(map[int]common.IBaseGameEntity)
	return em
}

func (em *EntityManager) RegisterEntity(entity common.IBaseGameEntity) {
	em.entityMap[entity.Id()] = entity
}

func (em *EntityManager) GetEntityFromID(id int) common.IBaseGameEntity {
	return em.entityMap[id]
}

func (em *EntityManager) RemoveEntity(pEntity common.IBaseGameEntity) {
	delete(em.entityMap, entity.Id())
}

func (em *EntityManager) Reset() {
	em.entityMap = make(map[int]common.IBaseGameEntity)
}
