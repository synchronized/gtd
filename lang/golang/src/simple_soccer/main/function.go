package main

//------------------------- Overlapped -----------------------------------
//
//  tests to see if an entity is overlapping any of a number of entities
//  stored in a std container
//------------------------------------------------------------------------
// = 40.0
// 测试一个实体ob是否与players中的多个实体中的任何一个重叠
//------------------------------------------------------------------------
func Overlapped(ob *PlayerBase, players []*PlayerBase, MinDistBetweenObstacles float64) bool {

	for _, player := range players {

		var bOverlapped = TwoCirclesOverlapped(ob.Pos(),
			ob.BRadius()+MinDistBetweenObstacles,
			player.Pos(),
			player.BRadius())
		if bOverlapped {
			return true
		}
	}

	return false
}

//----------------------- TagNeighbors ----------------------------------
//
//  tags any entities contained in a std container that are within the
//  radius of the single entity parameter
//------------------------------------------------------------------------
// 标记实体数组players中包含在单个实体参数半径内的任何实体
//------------------------------------------------------------------------
func TagNeighbors(entity *PlayerBase, players []*PlayerBase, radius float64) {
	//iterate through all entities checking for range
	//遍历所有的实体检查范围
	for _, player := range players {
		//first clear any current tag
		//先清理标记状态
		player.UnTag()

		//work in distance squared to avoid sqrts
		//使用距离平方计算,以避免开方
		var to Vector2D = player.Pos().OpMinus(entity.Pos())

		//the bounding radius of the other is taken into account by adding it
		//to the range
		//other通过将半径边界添加到范围中来计算
		var rang float64 = radius + player.BRadius()

		//if entity within range, tag for further consideration
		if (player != entity) && (to.LengthSq() < rang*rang) {
			player.Tag()
		}

	} //next entity
}

//------------------- EnforceNonPenetrationContraint ---------------------
//
//  Given a pointer to an entity and a std container of pointers to nearby
//  entities, this function checks to see if there is an overlap between
//  entities. If there is, then the entities are moved away from each
//  other
//------------------------------------------------------------------------
// 给定一个指向实体的指针和一个指向附近实体的数组，
// 此函数检查实体之间是否存在重叠。
// 如果存在，那么这些实体就会彼此远离
//------------------------------------------------------------------------
func EnforceNonPenetrationContraint(entity *PlayerBase, others []*PlayerBase) {

	//iterate through all entities checking for any overlap of bounding
	//radii
	//遍历所有实体，检查边界半径是否重叠
	for _, pkayer := range others {
		//make sure we don't check against this entity
		//确保不检查这个实体
		if player == entity {
			continue
		}

		//calculate the distance between the positions of the entities
		//计算距离
		var toEntity Vector2D = entity.Pos() - player.Pos()

		var distFromEachOther float64 = toEntity.Length()

		//if this distance is smaller than the sum of their radii then this
		//entity must be moved away in the direction parallel to the
		//ToEntity vector
		//如果该距离小于其半径之和，则该实体必须沿平行于实体向量的方向移动
		var amountOfOverLap float64 = player.BRadius() + entity.BRadius() - distFromEachOther

		if amountOfOverLap >= 0 {
			//move the entity a distance away equivalent to the amount of overlap.
			//将实体移到与重叠量相等的距离以外。
			var moveAway Vector2d = ToEntity.OpDivide(distFromEachOther).OpMultiply(amountOfOverLap)
			entity.SetPos(entity.Pos().OpAdd(moveAway))
		}
	} //next entity
}
