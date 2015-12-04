local level84 = {};--{"portals":,"gameModeName":"Light up","scoreTargets":33000,160000,200000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,10,2,10,2,10,2,2,2,10,10,138,138,138,10,10,2,2,2,138,0,138,0,138,2,2,2,10,138,138,138,138,138,10,2,2,2,138,0,138,0,138,2,2,2,10,10,138,138,138,10,10,2,2,2,10,2,10,2,10,2,2,2,2,2,2,2,2,2,2,2}


level84.candyDropMode = 0;
level84.moveLimit = 50;
level84.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,10,2,10,2,10,2,2,
	2,10,10,138,138,138,10,10,2,
	2,2,138,0,138,0,138,2,2,
	2,10,138,138,138,138,138,10,2,
	2,2,138,0,138,0,138,2,2,
	2,10,10,138,138,138,10,10,2,
	2,2,10,2,10,2,10,2,2,
	2,2,2,2,2,2,2,2,2
};

level84.portalNum=0;

level84.newportalNum=0;


level84.oneStarScore =  60000;
level84.twoStarScore =  160000;
level84.threeStarScore =  260000;

level84.numberOfColours = 6;

level84.numjelly =  33;

level84.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level84.ingredientSpawnDensity = 35;
level84.numIngredientsOnScreen = 2;
level84.numCherry = 0;
level84.numChesnut = 1;
]]
return level84;