local level77 = {};--{"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,288,288,288,288,288,288,288,288,288,96,96,96,96,96,96,96,96,96,134,134,134,134,134,134,134,134,134,"portals":,"gameModeName":"Light up","scoreTargets":40000,60000,80000,"moveLimit":50}


level77.candyDropMode = 0;
level77.moveLimit = 28;
level77.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	288,288,288,288,288,288,288,288,288,
	96,96,96,96,96,96,96,96,96,
	138,138,138,138,138,138,138,138,138
};

level77.portalNum=0;

level77.newportalNum=0;


level77.oneStarScore =  40000;
level77.twoStarScore =  80000;
level77.threeStarScore =  100000;

level77.numberOfColours = 6;

level77.numjelly =  9;

level77.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level77.ingredientSpawnDensity = 35;
level77.numIngredientsOnScreen = 2;
level77.numCherry = 0;
level77.numChesnut = 1;
]]
return level77;