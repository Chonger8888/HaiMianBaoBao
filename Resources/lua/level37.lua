local level37 = {};--{"tileMap":18,18,18,18,120,18,18,18,18,2,2,2,2,96,2,2,2,2,2,2,2,2,104,2,2,2,2,2,2,2,2,96,2,2,2,2,2,2,2,2,96,2,2,2,2,96,96,96,96,96,96,96,96,96,10,96,10,96,10,96,10,96,10,96,96,96,96,96,96,96,96,96,10,96,10,96,10,96,10,96,10,"portals":,"gameModeName":"Light up","scoreTargets":40000,60000,100000,"numberOfColours":5,"moveLimit":22,"randomSeed":0,"protocolVersion":"0.1"}


level37.candyDropMode = 0;
level37.moveLimit = 20;
level37.CandyMapDataTable = {
	18,18,18,18,116,18,18,18,18,
	2,2,2,2,96,2,2,2,2,
	2,2,2,2,100,2,2,2,2,
	2,2,2,2,96,2,2,2,2,
	2,2,2,2,96,2,2,2,2,
	96,96,96,96,96,96,96,96,96,
	6,96,6,96,6,96,6,96,6,
	96,96,96,96,96,96,96,96,96,
	6,96,6,96,6,96,6,96,6
};

level37.portalNum=0;

level37.newportalNum=0;

level37.numjelly =  12;

level37.oneStarScore =  16000;
level37.twoStarScore =  50000;
level37.threeStarScore =  85000;

level37.numberOfColours = 5;

level37.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level37.ingredientSpawnDensity = 35;
level37.numIngredientsOnScreen = 2;
level37.numCherry = 1;
level37.numChesnut = 3;
]]
return level37;