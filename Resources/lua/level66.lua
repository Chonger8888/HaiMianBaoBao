local level66 = {};--{"tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,96,2,2,2,2,2,2,2,96,96,96,2,2,2,2,2,96,138,138,138,96,2,2,2,96,96,138,138,138,96,96,2,2,2,96,138,138,138,96,2,2,2,2,2,96,96,96,2,2,2,2,2,2,2,96,2,2,2,2,2,2,2,2,2,2,2,2,2,"portals":,"gameModeName":"Light up","scoreTargets":20000,50000,90000,"moveLimit":15,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1"}


level66.candyDropMode = 0;
level66.moveLimit = 20;
level66.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,138,96,2,2,2,96,138,2,
	2,138,96,2,2,2,96,138,2,
	2,138,96,2,2,2,96,138,2,
	2,138,96,2,2,2,96,138,2,
	2,138,96,2,2,2,96,138,2,
	2,138,96,96,96,96,96,138,2,
	2,138,138,138,138,138,138,138,2,
	2,2,2,2,2,2,2,2,2
};

level66.portalNum=0;

level66.newportalNum=0;

level66.oneStarScore =  40000;
level66.twoStarScore =  130000;
level66.threeStarScore =  180000;

level66.numberOfColours = 5;

level66.numjelly =  19;

level66.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level66.ingredientSpawnDensity = 35;
level66.numIngredientsOnScreen = 2;
level66.numCherry = 0;
level66.numChesnut = 1;
]]
return level66;