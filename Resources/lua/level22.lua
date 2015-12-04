local level22 = {};--{"numberOfColours":4,"moveLimit":16,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,0,0,18,18,18,0,0,0,0,0,18,2,10,2,18,0,0,0,18,2,10,3082,10,2,18,0,2,2,10,3082,0,3082,10,2,2,2,10,10,0,0,0,10,10,2,2,2,10,5130,0,5130,10,2,2,0,2,2,10,5130,10,2,2,0,0,0,2,2,10,2,2,0,0,0,0,0,2,2,2,0,0,0,"portals":4,2,4,6,3,3,3,5,5,3,5,5,"gameModeName":"Light up","scoreTargets":40000,65000,85000}


level22.candyDropMode = 0;
level22.moveLimit = 18;
level22.CandyMapDataTable = {
	0,0,0,18,18,18,0,0,0,
	0,0,18,2,10,2,18,0,0,
	0,18,2,10,3082,10,2,18,0,
	2,2,10,3082,0,3082,10,2,2,
	2,10,10,0,0,0,10,10,2,
	2,2,10,5130,0,5130,10,2,2,
	0,2,2,10,5130,10,2,2,0,
	0,0,2,2,10,2,2,0,0,
	0,0,0,2,2,2,0,0,0
};

level22.portalNum=0;

level22.newportalNum=0;

level22.numjelly =  20;

level22.oneStarScore =  42400;
level22.twoStarScore =  80000;
level22.threeStarScore =  120000;

level22.numberOfColours = 4;

level22.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level22.ingredientSpawnDensity = 35;
level22.numIngredientsOnScreen = 2;
level22.numCherry = 0;
level22.numChesnut = 1;
]]
return level22;