local level86 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level86.candyDropMode = 0;
level86.moveLimit = 33;
level86.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	18,0,18,18,0,18,18,0,18,
	10,18,10,10,18,10,10,18,10,
	138,10,138,138,138,138,138,10,138,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	10,10,10,10,10,10,10,10,10,
	2,0,2,2,0,2,2,0,2,
	0,0,0,0,0,0,0,0,0
};

level86.portalNum=0;

level86.newportalNum=0;

level86.oneStarScore =  60000;
level86.twoStarScore =  160000;
level86.threeStarScore =  260000;

level86.numberOfColours = 6;

level86.numjelly =  24;

level86.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level86.ingredientSpawnDensity = 35;
level86.numIngredientsOnScreen = 2;
level86.numCherry = 0;
level86.numChesnut = 1;
]]
return level86;