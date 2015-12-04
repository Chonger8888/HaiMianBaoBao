local level34 = {};--{"gameModeName":"Drop down","scoreTargets":20000,50000,75000,"ingredientSpawnDensity":5,"moveLimit":20,"numberOfColours":4,"numIngredientsOnScreen":1,"randomSeed":0,"protocolVersion":"0.1","ingredients":1,1,"tileMap":0,0,18,18,18,18,18,0,0,0,0,2,2,2,2,2,0,0,0,0,2,3074,2,3074,2,0,0,0,0,3074,0,3074,0,3074,0,0,0,0,0,5122,0,5122,0,0,0,0,0,5122,2,5122,2,5122,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,514,514,514,514,514,0,0,"portals":2,3,2,5,3,2,3,4,4,3,4,5,5,2,5,4,6,3,6,5}


level34.candyDropMode = 0;
level34.moveLimit = 14;
level34.CandyMapDataTable = {
	0,0,18,18,18,18,18,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,3074,2,3074,2,0,0,
	0,0,3074,0,3074,0,3074,0,0,
	0,0,0,5122,0,5122,0,0,0,
	0,0,5122,2,5122,2,5122,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,514,514,514,514,514,0,0
};

level34.portalNum=0;

level34.newportalNum=0;

level34.oneStarScore =  20000;
level34.twoStarScore =  35000;
level34.threeStarScore =  68000;

level34.numberOfColours = 4;

level34.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level34.ingredientSpawnDensity = 5;
level34.numIngredientsOnScreen = 1;
level34.numCherry = 1;
level34.numChesnut = 1;

return level34;