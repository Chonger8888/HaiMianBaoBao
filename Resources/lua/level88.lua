local level88 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level88.candyDropMode = 0;
level88.moveLimit = 50;
level88.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	138,138,138,138,138,138,138,138,138,
	0,2,2,2,2,2,2,2,0,
	10,10,10,10,10,10,10,10,10,
	2,2,2,2,2,2,2,2,2,
	138,138,138,138,138,138,138,138,138,
	288,288,288,288,288,288,288,288,288
};

level88.portalNum=0;

level88.newportalNum=0;

level88.oneStarScore =  60000;
level88.twoStarScore =  100000;
level88.threeStarScore =  150000;

level88.numberOfColours = 6;

level88.numjelly =  27;

level88.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level88.ingredientSpawnDensity = 35;
level88.numIngredientsOnScreen = 2;
level88.numCherry = 0;
level88.numChesnut = 1;
]]
return level88;