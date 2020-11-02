package main

import "westworld/common"

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

func (em *EntityManager) GetEntityById(id int) (entity common.IBaseGameEntity) {
	entity, _ = em.entityMap[id]
	return entity
}

func (em *EntityManager) RemoveEntity(entity common.IBaseGameEntity) {
	delete(em.entityMap, entity.Id())
}
