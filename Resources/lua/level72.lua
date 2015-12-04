local level72 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level72.candyDropMode = 0;
level72.moveLimit = 30;
level72.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,96,96,2,96,96,2,2,
	2,2,96,96,2,96,96,2,2,
	2,2,96,96,2,96,96,2,2,
	130,130,130,130,130,130,130,130,130,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	608,608,608,608,608,608,608,608,608
};

level72.portalNum=0;

level72.newportalNum=0;

level72.oneStarScore =  40000;
level72.twoStarScore =  90000;
level72.threeStarScore = 120000;

level72.numberOfColours = 6;

level72.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level72.ingredientSpawnDensity = 8;
level72.numIngredientsOnScreen = 1;
level72.numCherry = 2;
level72.numChesnut = 2;
return level72;