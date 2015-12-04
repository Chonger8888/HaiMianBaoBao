local level38 = {};--{"randomSeed":0,"moveLimit":50,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,104,2,104,2,10,2,104,2,104,104,2,104,2,104,2,104,2,104,104,2,104,2,104,2,104,2,104,104,2,104,2,104,2,104,2,104,104,2,104,2,104,2,104,2,104,104,2,104,2,104,2,104,2,104,"portals":,"gameModeName":"Light up","scoreTargets":60000,120000,150000,"numberOfColours":6}


level38.candyDropMode = 0;
level38.moveLimit = 36;
level38.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	104,2,104,2,10,2,104,2,104,
	104,2,104,2,104,2,104,2,104,
	104,2,104,2,104,2,104,2,104,
	104,2,104,2,104,2,104,2,104,
	104,2,104,2,104,2,104,2,104,
	104,2,104,2,104,2,104,2,104
};

level38.portalNum=0;

level38.newportalNum=0;

level38.numjelly =  30;

level38.oneStarScore =  70000;
level38.twoStarScore =  150000;
level38.threeStarScore =  210000;

level38.numberOfColours = 6;

level38.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level38.ingredientSpawnDensity = 35;
level38.numIngredientsOnScreen = 2;
level38.numCherry = 1;
level38.numChesnut = 3;
]]

return level38;