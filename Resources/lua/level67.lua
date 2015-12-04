local level67 = {};--{"portals":,"gameModeName":"Classic moves","scoreTargets":15000,25000,35000,"moveLimit":40,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,130,130,130,2,130,130,130,2,2,130,130,2,2,2,130,130,2,2,130,2,2,2,2,2,130,2,2,2,2,2,2,2,2,2,2,2,130,2,2,2,2,2,130,2,2,130,130,2,2,2,130,130,2,2,130,130,130,2,130,130,130,2,2,2,2,2,2,2,2,2,2}


level67.candyDropMode = 0;
level67.moveLimit = 28;
level67.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	97,97,97,97,97,97,97,97,97,
	130,130,130,130,130,130,130,130,130,
	97,97,97,97,97,97,97,97,97,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2
};

level67.portalNum=0;

level67.newportalNum=0;

level67.oneStarScore =  40000;
level67.twoStarScore =  120000;
level67.threeStarScore =  180000;

level67.numberOfColours = 5;

level67.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
level67.collectItem = {
    0,99,
    1,99,	
	
};
--[[
level67.ingredientSpawnDensity = 35;
level67.numIngredientsOnScreen = 2;
level67.numCherry = 0;
level67.numChesnut = 1;
]]
return level67;