local level89 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level89.candyDropMode = 0;
level89.moveLimit = 30;
level89.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,10,138,138,138,10,2,2,
	2,2,138,2,138,2,138,2,2,
	2,2,138,138,138,138,138,2,2,
	2,2,138,2,138,2,138,2,2,
	2,2,10,138,138,138,10,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2
};

level89.portalNum=0;

level89.newportalNum=0;

level89.oneStarScore =  60000;
level89.twoStarScore =  160000;
level89.threeStarScore =  260000;

level89.numberOfColours = 6;

level89.numjelly =  21;

level89.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level89.ingredientSpawnDensity = 35;
level89.numIngredientsOnScreen = 2;
level89.numCherry = 0;
level89.numChesnut = 1;
]]
return level89;