local level65 = {};--{"scoreTargets":140000,175000,250000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":146,26,26,26,26,26,26,26,146,130,10,10,10,10,10,10,10,130,130,10,10,10,3082,10,10,10,130,130,10,10,0,0,0,10,10,130,130,10,10,0,7178,0,10,10,130,130,10,10,0,0,0,10,10,130,130,10,10,10,5130,10,10,10,130,130,10,10,10,10,10,10,10,130,130,10,10,10,10,10,10,10,130,"portals":4,2,4,4,4,4,4,6,"gameModeName":"Light up"}


level65.candyDropMode = 0;
level65.moveLimit = 40;
level65.CandyMapDataTable = {
	146,26,26,26,26,26,26,26,146,
	130,10,10,10,10,10,10,10,130,
	130,10,10,10,0,10,10,10,130,
	130,10,10,10,0,10,10,10,130,
	130,10,10,10,0,10,10,10,130,
	130,10,10,10,0,10,10,10,130,
	130,10,10,10,0,10,10,10,130,
	130,10,10,10,10,10,10,10,130,
	130,10,10,10,10,10,10,10,130
};

level65.portalNum=0;

level65.newportalNum=0;

level65.oneStarScore =  120000;
level65.twoStarScore =  200000;
level65.threeStarScore =  250000;

level65.numberOfColours = 6;

level65.numjelly =  58;

level65.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level65.ingredientSpawnDensity = 35;
level65.numIngredientsOnScreen = 2;
level65.numCherry = 0;
level65.numChesnut = 1;
]]
return level65;