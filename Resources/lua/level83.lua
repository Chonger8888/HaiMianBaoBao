local level83 = {};--{"gameModeName":"Light up","scoreTargets":60000,70000,80000,"moveLimit":20,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":22,22,18,18,18,18,18,22,22,6,6,2,2,2,2,2,6,6,2,2,2,2,2,2,2,2,2,2,2,96,96,96,96,96,2,2,2,2,96,288,288,288,96,2,2,2,2,96,96,96,96,96,2,2,2,2,2,2,2,2,2,2,2,10,10,2,2,2,2,2,10,10,10,10,2,2,2,2,2,10,10,"portals":}


level83.candyDropMode = 0;
level83.moveLimit = 20;
level83.CandyMapDataTable = {
	22,22,18,18,18,18,18,22,22,
	6,6,2,2,2,2,2,6,6,
	2,2,2,2,2,2,2,2,2,
	2,2,96,96,96,96,96,2,2,
	2,2,96,288,288,288,96,2,2,
	2,2,96,96,96,96,96,2,2,
	2,2,2,2,2,2,2,2,2,
	10,10,2,2,2,2,2,10,10,
	10,10,2,2,2,2,2,10,10
};

level83.portalNum=0;

level83.newportalNum=0;


level83.oneStarScore =  40000;
level83.twoStarScore =  60000;
level83.threeStarScore =  80000;

level83.numberOfColours = 5;

level83.numjelly =  16;

level83.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level83.ingredientSpawnDensity = 35;
level83.numIngredientsOnScreen = 2;
level83.numCherry = 0;
level83.numChesnut = 1;
]]
return level83;