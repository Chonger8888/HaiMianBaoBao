local level70 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level70.candyDropMode = 0;
level70.moveLimit = 33;
level70.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	130,130,130,130,130,130,130,130,130,
	608,608,608,608,608,608,608,608,608
};

level70.portalNum=0;

level70.newportalNum=0;

level70.oneStarScore =  40000;
level70.twoStarScore =  80000;
level70.threeStarScore =  100000;

level70.numberOfColours = 6;

level70.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level70.ingredientSpawnDensity = 10;
level70.numIngredientsOnScreen = 1;
level70.numCherry = 1;
level70.numChesnut = 1;
return level70;