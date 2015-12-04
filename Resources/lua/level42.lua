local level42 = {};--{"gameModeName":"Classic","scoreTargets":15000,25000,45000,"timeLimit":60,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,18,0,0,2,2,2,2,2,2,2,18,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,"portals":}


level42.candyDropMode = 0;
level42.moveLimit = 22;
level42.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,2,2,2,2,2,2,2,
	0,3074,3074,3074,2,2,3074,3074,3074,
	0,0,0,0,97,97,0,0,0,
	0,2,0,5250,130,130,5250,0,2,
	0,2,5250,130,130,130,130,5250,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
};

level42.portalNum=0;

level42.newportalNum=0;

level42.oneStarScore =  6000;
level42.twoStarScore =  75000;
level42.threeStarScore =  130000;

level42.numberOfColours = 5;

level42.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level42.collectItem = {
	0,30,
	3,30,
};

--[[
level42.ingredientSpawnDensity = 35
level42.numIngredientsOnScreen = 2
level42.numCherry = 1
level42.numChesnut = 3
]]
return level42;