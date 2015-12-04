local level17 = {};--{"portals":,"numIngredientsOnScreen":4,"gameModeName":"Drop down","scoreTargets":40000,50000,60000,"ingredients":4,0,"ingredientSpawnDensity":1,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,0,18,0,18,0,18,0,18,2,0,2,0,2,0,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,514,2,2,2,2,2,2,2,514,0,514,514,2,2,2,514,514,0,0,0,0,514,514,514,0,0,0,"moveLimit":19}


level17.candyDropMode = 0;
level17.moveLimit = 15;
level17.CandyMapDataTable = {
	18,0,18,0,18,0,18,0,18,
	2,0,2,0,2,0,2,0,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	514,2,2,2,2,2,2,2,514,
	0,514,514,2,2,2,514,514,0,
	0,0,0,514,514,514,0,0,0
};

level17.portalNum=0;

level17.newportalNum=0;

level17.oneStarScore =  22700;
level17.twoStarScore =  40000;
level17.threeStarScore =  60000;

level17.numberOfColours = 5;

level17.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level17.ingredientSpawnDensity = 1;
level17.numIngredientsOnScreen = 2;
level17.numCherry = 2;
level17.numChesnut = 0;


return level17;