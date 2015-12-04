local level31 = {};--{"ingredientSpawnDensity":5,"randomSeed":0,"moveLimit":35,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,18,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,96,96,96,96,96,96,96,0,0,96,96,96,96,96,96,96,0,0,608,608,608,608,608,608,608,0,"portals":,"gameModeName":"Drop down","scoreTargets":40000,70000,90000,"ingredients":2,2,"numIngredientsOnScreen":1,"numberOfColours":5}


level31.candyDropMode = 0;
level31.moveLimit = 28;
level31.CandyMapDataTable = {
	0,18,18,18,18,18,18,18,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,96,96,96,96,96,96,96,0,
	0,96,96,96,96,96,96,96,0,
	0,608,608,608,608,608,608,608,0
};

level31.portalNum=0;

level31.newportalNum=0;

level31.oneStarScore =  45000;
level31.twoStarScore =  90000;
level31.threeStarScore =  140000;

level31.numberOfColours = 5;

level31.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果


level31.ingredientSpawnDensity = 5;
level31.numIngredientsOnScreen = 1;
level31.numCherry = 2;
level31.numChesnut = 2;

return level31;