local level30 = {};--{"gameModeName":"Classic","scoreTargets":40000,60000,100000,"timeLimit":60,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":112,18,18,18,18,18,18,18,112,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,2,2,2,2,2,2,2,96,96,96,96,96,96,96,96,96,96,"portals":}


level30.candyDropMode = 0;
level30.moveLimit = 40;
level30.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2
};

level30.portalNum=0;

level30.newportalNum=0;

level30.oneStarScore =  60000;
level30.twoStarScore =  120000;
level30.threeStarScore =  200000;

level30.numberOfColours = 5;

level30.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level30.timeLimit = 60;

--[[
level30.ingredientSpawnDensity = 35;
level30.numIngredientsOnScreen = 2;
level30.numCherry = 1;
level30.numChesnut = 3;
]]
return level30;