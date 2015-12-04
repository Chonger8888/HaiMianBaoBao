local level52 = {};--{"scoreTargets":60000,80000,120000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,154,18,18,18,18,2,2,2,2,138,2,2,2,2,2,2,2,2,138,2,2,2,2,2,2,2,2,138,2,2,2,2,2,2,2,2,138,2,2,2,2,2,2,2,2,138,2,2,2,2,96,96,96,138,138,138,96,96,96,10,10,96,138,138,138,96,10,10,138,10,96,138,138,138,96,10,138,"portals":,"gameModeName":"Light up"}


level52.candyDropMode = 0;
level52.moveLimit = 28;
level52.CandyMapDataTable = {
	18,18,18,18,154,18,18,18,18,
	2,2,2,2,138,2,2,2,2,
	2,2,2,2,138,2,2,2,2,
	2,2,2,2,138,2,2,2,2,
	2,2,2,2,138,2,2,2,2,
	2,2,2,2,138,2,2,2,2,
	96,96,96,138,138,138,96,96,96,
	10,10,2,138,138,138,2,10,10,
	138,10,2,138,138,138,2,10,138
};

level52.portalNum=0;

level52.newportalNum=0;

level52.oneStarScore =  80000;
level52.twoStarScore =  120000;
level52.threeStarScore =  160000;

level52.numberOfColours = 6;

level52.numjelly =  23;

level52.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level52.ingredientSpawnDensity = 35;
level52.numIngredientsOnScreen = 2;
level52.numCherry = 0;
level52.numChesnut = 1;
]]
return level52;