local level85 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level85.candyDropMode = 0;
level85.moveLimit = 33;
level85.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,0,0,0,18,18,0,
	10,10,10,10,0,10,10,10,10,
	10,10,10,10,10,10,10,10,10,
	0,10,10,10,10,10,10,10,0,
	0,0,10,10,10,10,10,0,0,
	0,0,0,10,10,10,0,0,0,
	0,0,0,0,296,0,0,0,0,
	0,0,0,0,0,0,0,0,0
};

level85.portalNum=0;

level85.newportalNum=0;

level85.oneStarScore =  60000;
level85.twoStarScore =  100000;
level85.threeStarScore =  140000;

level85.numberOfColours = 6;

level85.numjelly =  33;

level85.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level85.ingredientSpawnDensity = 35;
level85.numIngredientsOnScreen = 2;
level85.numCherry = 0;
level85.numChesnut = 1;
]]
return level85;