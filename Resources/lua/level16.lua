local level16 = {};--{"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,514,514,514,514,514,0,0,"ingredients":0,1,"portals":,"ingredientSpawnDensity":15,"gameModeName":"Drop down","scoreTargets":1000,2000,3000,"moveLimit":50,"numberOfColours":5}


level16.candyDropMode = 0;
level16.moveLimit = 12;
level16.CandyMapDataTable = {
	0,0,18,18,18,18,18,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,	
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,514,514,514,514,514,0,0
};

level16.portalNum=0;

level16.newportalNum=0;

level16.oneStarScore =  11800;
level16.twoStarScore =  26000;
level16.threeStarScore =  40000;

level16.numberOfColours = 5;

level16.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level16.ingredientSpawnDensity = 15;
level16.numIngredientsOnScreen = 1;
level16.numCherry = 0;
level16.numChesnut = 1;
return level16;