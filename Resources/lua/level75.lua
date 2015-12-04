local level75 = {};--{"randomSeed":0,"protocolVersion":"0.1","tileMap":304,112,18,18,18,18,18,112,304,288,96,2,2,2,2,2,96,288,288,96,2,2,2,2,2,96,288,288,96,2,2,2,2,2,96,288,288,96,2,2,2,2,2,96,288,288,96,2,2,2,2,2,96,288,288,96,2,2,2,2,2,96,288,288,96,96,96,96,96,96,96,288,288,288,288,288,288,288,288,288,288,"portals":,"timeLimit":90,"gameModeName":"Classic","scoreTargets":15000,25000,35000,"numberOfColours":6}


level75.candyDropMode = 0;
level75.moveLimit = 30;
level75.CandyMapDataTable = {
	146,112,18,18,18,18,18,112,146,
	130,96,2,2,2,2,2,96,130,
	130,96,2,2,2,2,2,96,130,
	130,96,2,2,2,2,2,96,130,
	130,96,2,2,2,2,2,96,130,
	130,96,2,2,2,2,2,96,130,
	130,96,2,2,2,2,2,96,130,
	130,96,96,96,96,96,96,96,130,
	642,642,642,642,642,642,642,642,642
};

level75.portalNum=0;

level75.newportalNum=0;

level75.oneStarScore =  40000;
level75.twoStarScore =  70000;
level75.threeStarScore =  100000;

level75.numberOfColours = 6;

level75.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level75.timeLimit = 90;

--[[
level75.ingredientSpawnDensity = 35;
level75.numIngredientsOnScreen = 2;
level75.numCherry = 0;
level75.numChesnut = 1;
]]
return level75;