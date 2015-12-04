local level61 = {};--{"scoreTargets":50000,90000,150000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":154,18,18,18,18,18,18,18,154,2,2,2,2,2,2,2,2,2,2,2,10,10,10,10,10,2,2,2,2,10,138,138,138,10,2,2,2,2,10,138,138,138,10,2,2,2,2,10,138,138,138,10,2,2,2,2,10,10,10,10,10,2,2,2,2,2,2,2,2,2,2,2,138,2,2,2,2,2,2,2,138,"portals":,"gameModeName":"Light up"}


level61.candyDropMode = 0;
level61.moveLimit = 28;
level61.CandyMapDataTable = {
	154,18,18,18,18,18,18,18,154,
	2,2,2,2,2,2,2,2,2,
	2,2,10,2,10,2,10,2,2,
	2,2,2,138,138,138,2,2,2,
	2,2,10,138,10,138,10,2,2,
	2,2,2,138,138,138,2,2,2,
	2,2,10,2,10,2,10,2,2,
	2,2,2,2,2,2,2,2,2,
	138,2,2,2,2,2,2,2,138
};

level61.portalNum=0;

level61.newportalNum=0;

level61.oneStarScore =  45000;
level61.twoStarScore =  130000;
level61.threeStarScore =  180000;

level61.numberOfColours = 6;

level61.numjelly =  21;

level61.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level61.ingredientSpawnDensity = 35;
level61.numIngredientsOnScreen = 2;
level61.numCherry = 0;
level61.numChesnut = 1;
]]
return level61;