local level49 = {};--{"scoreTargets":30000,60000,90000,"moveLimit":30,"numberOfColours":4,"randomSeed":0,"numIngredientsOnScreen":2,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,3074,3074,2,3074,3074,2,2,2,2,0,0,2,0,0,2,2,2,2,0,5122,2,5122,0,2,2,2,2,0,2,2,2,0,2,2,2,2,0,3074,2,3074,0,2,2,2,2,0,0,2,0,0,2,2,2,2,5122,5122,2,5122,5122,2,2,514,514,514,514,514,514,514,514,514,"ingredients":3,4,"portals":3,1,3,3,5,1,5,3,6,1,6,7,2,1,2,7,3,5,3,7,5,5,5,7,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level49.candyDropMode = 0;
level49.moveLimit = 19;
level49.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,3074,3074,2,3074,3074,2,2,
	2,2,0,0,2,0,0,2,2,
	2,2,0,5122,2,5122,0,2,2,
	97,97,7265,97,97,97,7265,97,97,
	2,2,0,3074,2,3074,0,2,2,
	2,2,0,0,2,0,0,2,2,
	2,2,5122,5122,2,5122,5122,2,2,
	514,514,514,514,514,514,514,514,514
};

level49.portalNum=0;

level49.newportalNum=0;

level49.oneStarScore =  62000;
level49.twoStarScore =  110000;
level49.threeStarScore =  150000;

level49.numberOfColours = 4;

level49.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level49.ingredientSpawnDensity = 6;
level49.numIngredientsOnScreen = 2;
level49.numCherry = 3;
level49.numChesnut = 3;
return level49;