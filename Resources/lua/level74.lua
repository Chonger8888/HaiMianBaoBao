local level74 = {};--{"gameModeName":"Drop down","scoreTargets":50000,75000,125000,"ingredientSpawnDensity":15,"moveLimit":15,"numberOfColours":4,"numIngredientsOnScreen":1,"randomSeed":0,"protocolVersion":"0.1","ingredients":1,"tileMap":112,146,112,112,112,112,112,146,18,130,96,2,2,2,96,96,96,130,96,130,96,2,96,96,96,130,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,130,130,130,130,130,130,130,130,130,642,642,642,642,642,642,642,642,642,"portals":}


level74.candyDropMode = 0;
level74.moveLimit = 15;
level74.CandyMapDataTable = {
	112,146,112,112,112,112,112,146,18,
	130,96,2,2,2,96,96,96,130,
	96,130,96,2,96,96,96,130,96,
	96,96,96,96,96,96,96,96,96,
	96,96,96,96,96,96,96,96,96,
	96,96,96,96,96,96,96,96,96,
	96,96,96,96,96,96,96,96,96,
	130,130,130,130,130,130,130,130,130,
	642,642,642,642,642,642,642,642,642
};

level74.portalNum=0;

level74.newportalNum=0;

level74.oneStarScore =  30000;
level74.twoStarScore =  160000;
level74.threeStarScore =  200000;

level74.numberOfColours = 4;

level74.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level74.ingredientSpawnDensity = 15;
level74.numIngredientsOnScreen = 1;
level74.numCherry = 0;
level74.numChesnut = 1;
return level74;