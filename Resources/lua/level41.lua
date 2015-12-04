local level41 = {};--{"gameModeName":"Classic","scoreTargets":15000,25000,45000,"timeLimit":60,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,18,0,0,2,2,2,2,2,2,2,18,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,"portals":}


level41.candyDropMode = 0;
level41.moveLimit = 24;
level41.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,0,2,2,2,2,0,2,
	0,2,2,0,130,130,0,2,2,
	0,2,2,130,0,0,130,2,2,
	0,2,2,130,0,0,130,2,2,
	0,2,2,0,130,130,0,2,2,
	0,2,0,2,2,2,2,0,2,
	0,2,2,2,2,2,2,2,2,
};

level41.portalNum=0;

level41.newportalNum=0;

level41.oneStarScore =  6000;
level41.twoStarScore =  20000;
level41.threeStarScore =  35000;

level41.numberOfColours = 5;

level41.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level41.collectItem = {
	1,25,
	0,25,
	3,25
};


--[[
level41.ingredientSpawnDensity = 35
level41.numIngredientsOnScreen = 2
level41.numCherry = 1
level41.numChesnut = 3
]]
return level41;