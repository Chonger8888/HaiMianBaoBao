local level47 = {};--{"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,514,514,514,514,514,0,0,"ingredients":0,1,"portals":,"ingredientSpawnDensity":15,"gameModeName":"Drop down","scoreTargets":1000,2000,3000,"moveLimit":50,"numberOfColours":5}


level47.candyDropMode = 0;
level47.moveLimit = 13;
level47.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,0,18,18,18,113,146,18,
	0,0,0,2,2,2,97,130,130,
	0,0,0,2,2,2,97,97,97,
	0,0,0,2,2,0,2,2,2,
	0,0,0,2,2,2,2,2,2,
	0,0,0,514,514,514,514,514,514
};

level47.portalNum=0;

level47.newportalNum=0;

level47.oneStarScore =  30000;
level47.twoStarScore =  45000;
level47.threeStarScore =  68000;

level47.numberOfColours = 5;

level47.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level47.ingredientSpawnDensity = 6;
level47.numIngredientsOnScreen = 1;
level47.numCherry = 0;
level47.numChesnut = 3;
return level47;