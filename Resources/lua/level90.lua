local level90 = {};--{"gameModeName":"Classic","scoreTargets":10000,20000,30000,"timeLimit":90,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,130,96,130,96,130,96,130,96,130,288,130,288,130,288,130,288,130,288,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,"portals":}


level90.candyDropMode = 0;
level90.moveLimit = 40;
level90.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	130,96,130,96,130,96,130,96,130,
	288,130,288,130,288,130,288,130,288,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1
};

level90.portalNum=0;

level90.newportalNum=0;

level90.oneStarScore =  40000;
level90.twoStarScore =  60000;
level90.threeStarScore =  80000;

level90.numberOfColours = 6;

level90.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level90.timeLimit = 90

--[[
level90.ingredientSpawnDensity = 35;
level90.numIngredientsOnScreen = 2;
level90.numCherry = 0;
level90.numChesnut = 1;
]]
return level90;