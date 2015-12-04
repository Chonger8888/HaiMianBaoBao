local level18 = {};--{"numberOfColours":4,"moveLimit":16,"randomSeed":0,"protocolVersion":"0.1","numIngredientsOnScreen":1,"tileMap":0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,18,18,18,18,0,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,514,514,514,514,514,514,514,514,514,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"portals":,"ingredientSpawnDensity":2,"gameModeName":"Drop down","ingredients":0,7,"scoreTargets":70000,80000,90000}

level18.candyDropMode = 0;
level18.moveLimit = 16;
level18.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,18,18,18,18,18,0,0,
	0,2,2,2,2,2,2,2,0,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	514,514,514,514,514,514,514,514,514,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0
};

level18.portalNum=0;

level18.newportalNum=0;

level18.oneStarScore =  72400;
level18.twoStarScore =  120000;
level18.threeStarScore =  167000;

level18.numberOfColours = 4;

level18.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level18.ingredientSpawnDensity = 2;
level18.numIngredientsOnScreen = 1;
level18.numCherry = 0;
level18.numChesnut = 7;

return level18;