local level45 = {};--{"portals":,"timeLimit":120,"gameModeName":"Classic","scoreTargets":25000,33000,42000,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,0,0,18,18,18,0,0,0,0,0,18,2,2,2,18,0,0,0,18,2,96,96,96,2,18,0,18,2,96,96,96,96,96,2,18,2,2,96,96,96,96,96,2,2,2,2,96,96,96,96,96,2,2,0,2,2,96,96,96,2,2,0,0,0,2,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0}


level45.candyDropMode = 0;
level45.moveLimit = 40;
level45.CandyMapDataTable = {
	0,0,0,18,18,18,0,0,0,
	0,0,18,2,2,2,18,0,0,
	0,18,2,96,96,96,2,18,0,
	18,2,96,96,96,96,96,2,18,
	2,2,96,96,96,96,96,2,2,
	2,2,96,96,96,96,96,2,2,
	0,2,2,96,96,96,2,2,0,
	0,0,2,2,2,2,2,0,0,
	0,0,0,2,2,2,0,0,0
};

level45.portalNum=0;

level45.newportalNum=0;

level45.oneStarScore =  35000;
level45.twoStarScore =  60000;
level45.threeStarScore =  110000;

level45.numberOfColours = 5;

level45.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level45.timeLimit = 70;

--[[
level45.ingredientSpawnDensity = 35;
level45.numIngredientsOnScreen = 2;
level45.numCherry = 0;
level45.numChesnut = 1;
]]
return level45;