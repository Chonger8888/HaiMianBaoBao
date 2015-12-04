local level76 = {};--{"gameModeName":"Light up","scoreTargets":20000,35000,45000,"moveLimit":35,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,96,96,96,96,96,96,96,96,288,288,288,288,288,288,288,96,96,288,10,10,10,10,10,288,96,96,288,10,10,10,10,10,288,96,96,288,288,288,288,288,288,288,96,"portals":}


level76.candyDropMode = 0;
level76.moveLimit = 35;
level76.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	96,96,96,96,96,96,96,96,96,
	96,288,288,288,288,288,288,288,96,
	96,288,10,10,10,10,10,288,96,
	96,288,10,10,10,10,10,288,96,
	96,288,288,288,288,288,288,288,96
};

level76.portalNum=0;

level76.newportalNum=0;


level76.oneStarScore =  80000;
level76.twoStarScore =  150000;
level76.threeStarScore =  200000;

level76.numberOfColours = 6;

level76.numjelly =  10;

level76.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level76.ingredientSpawnDensity = 35;
level76.numIngredientsOnScreen = 2;
level76.numCherry = 0;
level76.numChesnut = 1;
]]
return level76;