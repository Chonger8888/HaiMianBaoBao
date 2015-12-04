local level63 = {};--{"scoreTargets":30000,70000,90000,"moveLimit":30,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,0,0,0,0,0,18,18,18,0,0,0,0,0,0,2,2,2,0,0,0,22,22,150,2,2,2,0,0,0,6,6,134,2,2,2,0,0,0,6,6,134,2,2,2,26,26,26,6,6,134,2,2,2,10,10,10,6,6,134,2,2,2,10,10,10,6,6,134,2,2,2,10,10,10,6,6,134,2,2,2,"portals":,"gameModeName":"Light up"}


level63.candyDropMode = 0;
level63.moveLimit = 30;
level63.CandyMapDataTable = {
	0,0,0,0,0,0,18,18,18,
	0,0,0,0,0,0,2,2,2,
	0,0,0,22,22,150,2,2,2,
	0,0,0,6,6,134,2,2,2,
	0,0,0,6,6,134,2,2,2,
	26,26,26,6,6,134,2,2,2,
	10,10,10,6,6,134,2,2,2,
	10,10,10,6,6,134,2,2,2,
	10,10,10,6,6,134,2,2,2
};

level63.portalNum=0;

level63.newportalNum=0;

level63.oneStarScore =  65000;
level63.twoStarScore =  100000;
level63.threeStarScore =  140000;

level63.numberOfColours = 6;

level63.numjelly =  33;

level63.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level63.ingredientSpawnDensity = 35;
level63.numIngredientsOnScreen = 2;
level63.numCherry = 0;
level63.numChesnut = 1;
]]


return level63;