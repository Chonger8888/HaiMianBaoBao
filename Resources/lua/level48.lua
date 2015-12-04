local level48 = {};--{"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,514,514,514,514,514,0,0,"ingredients":0,1,"portals":,"ingredientSpawnDensity":15,"gameModeName":"Drop down","scoreTargets":1000,2000,3000,"moveLimit":50,"numberOfColours":5}


level48.candyDropMode = 0;
level48.moveLimit = 24;
level48.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,18,18,0,0,0,
	0,0,0,2,2,2,2,0,0,
	0,0,2,2,2,2,2,2,0,	
	0,2,2,2,2,2,2,2,2,
	0,130,3202,130,130,130,130,3202,130,
	0,2,0,97,97,97,97,0,2,
	0,0,5122,2,2,2,2,5122,0,
	0,0,514,514,514,514,514,514,0
};

level48.portalNum=0;

level48.newportalNum=0;

level48.oneStarScore =  43000;
level48.twoStarScore =  120000;
level48.threeStarScore =  200000;

level48.numberOfColours = 5;

level48.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level48.ingredientSpawnDensity = 8;
level48.numIngredientsOnScreen = 1;
level48.numCherry = 2;
level48.numChesnut = 2;
return level48;