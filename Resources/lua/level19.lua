local level19 = {};--{"tileMap":0,0,18,18,18,18,0,0,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,18,2,2,2,2,18,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,514,2,2,2,2,2,2,514,0,0,514,514,514,514,514,514,0,0,"ingredients":1,3,"portals":,"ingredientSpawnDensity":35,"gameModeName":"Drop down","scoreTargets":40000,65000,100000,"moveLimit":35,"numberOfColours":5,"randomSeed":0,"numIngredientsOnScreen":2,"protocolVersion":"0.1"}


level19.candyDropMode = 0;
level19.moveLimit = 12;
level19.CandyMapDataTable = {
    0,0,0,0,0,0,0,0,0,
	0,18,0,0,18,18,0,0,18,
	0,0,2,2,2,2,2,2,0,
	0,0,2,2,2,2,2,2,0,	
	0,0,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,514,514,514,514,514,514,514,514
};

level19.portalNum=0;

level19.newportalNum=0;

level19.oneStarScore =  53000;
level19.twoStarScore =  80000;
level19.threeStarScore =  110000;

level19.numberOfColours = 5;

level19.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level19.ingredientSpawnDensity =5;
level19.numIngredientsOnScreen = 2;
level19.numCherry = 2;
level19.numChesnut = 3;
return level19;