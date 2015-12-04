local level82 = {};--{"scoreTargets":60000,80000,120000,"moveLimit":45,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,96,2,96,96,800,608,800,608,800,608,800,608,800,"ingredients":2,2,"portals":,"ingredientSpawnDensity":15,"gameModeName":"Drop down"}


level82.candyDropMode = 0;
level82.moveLimit = 45;
level82.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	96,96,2,96,96,96,2,96,96,
	800,608,800,608,800,608,800,608,800
};

level82.portalNum=0;

level82.newportalNum=0;

level82.oneStarScore =  80000;
level82.twoStarScore =  140000;
level82.threeStarScore =  180000;

level82.numberOfColours = 6;

level82.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level82.ingredientSpawnDensity = 15;
level82.numIngredientsOnScreen = 1;
level82.numCherry = 2;
level82.numChesnut = 2;
return level82;