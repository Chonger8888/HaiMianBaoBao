local level53 = {};--{"numberOfColours":6,"moveLimit":45,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,138,96,138,96,138,96,138,96,138,96,138,96,138,96,138,96,138,96,138,96,138,96,138,100,138,96,138,96,138,96,138,96,134,96,138,96,"portals":,"gameModeName":"Light up","scoreTargets":40000,110000,150000}


level53.candyDropMode = 0;
level53.moveLimit = 36;
level53.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	138,96,138,96,138,96,138,96,138,
	96,138,96,138,96,138,96,138,96,
	138,1,138,1,138,1,138,1,138,
	1,138,1,138,1,134,1,138,1
};

level53.portalNum=0;

level53.newportalNum=0;

level53.oneStarScore =  30000;
level53.twoStarScore =  110000;
level53.threeStarScore =  180000;

level53.numberOfColours = 6;

level53.numjelly =  18;

level53.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level53.ingredientSpawnDensity = 35;
level53.numIngredientsOnScreen = 2;
level53.numCherry = 1;
level53.numChesnut = 3;
]]
return level53;