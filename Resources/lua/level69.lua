local level69 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level69.candyDropMode = 0;
level69.moveLimit = 33;
level69.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,96,96,2,96,96,2,2,
	2,2,96,96,2,96,96,2,2,
	2,2,96,96,2,96,96,2,2,
	642,642,608,608,642,608,608,642,642
};

level69.portalNum=0;

level69.newportalNum=0;

level69.oneStarScore =  40000;
level69.twoStarScore =  80000;
level69.threeStarScore =  100000;

level69.numberOfColours = 6;

level69.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level69.ingredientSpawnDensity = 10;
level69.numIngredientsOnScreen = 1;
level69.numCherry = 2;
level69.numChesnut = 1;
return level69;