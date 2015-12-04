local level87 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level87.candyDropMode = 0;
level87.moveLimit = 50;
level87.CandyMapDataTable = {
	0,0,0,18,0,18,0,0,0,
	18,18,18,2,0,2,18,18,18,
	10,10,10,2,0,2,10,10,10,
	0,10,10,10,0,10,10,10,0,
	0,0,10,10,0,10,10,0,0,
	0,10,10,10,0,10,10,10,0,
	0,10,10,10,0,10,10,10,0,
	0,0,0,10,10,10,0,0,0,
	0,0,0,2,2,2,0,0,0
};

level87.portalNum=0;

level87.newportalNum=0;

level87.oneStarScore =  60000;
level87.twoStarScore =  160000;
level87.threeStarScore =  260000;

level87.numberOfColours = 5;

level87.numjelly =  31;

level87.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level87.ingredientSpawnDensity = 35;
level87.numIngredientsOnScreen = 2;
level87.numCherry = 0;
level87.numChesnut = 1;
]]
return level87;