local level46 = {};--{"scoreTargets":30000,60000,90000,"moveLimit":30,"numberOfColours":4,"randomSeed":0,"numIngredientsOnScreen":2,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,3074,3074,2,3074,3074,2,2,2,2,0,0,2,0,0,2,2,2,2,0,5122,2,5122,0,2,2,2,2,0,2,2,2,0,2,2,2,2,0,3074,2,3074,0,2,2,2,2,0,0,2,0,0,2,2,2,2,5122,5122,2,5122,5122,2,2,514,514,514,514,514,514,514,514,514,"ingredients":3,4,"portals":3,1,3,3,5,1,5,3,6,1,6,7,2,1,2,7,3,5,3,7,5,5,5,7,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level46.candyDropMode = 0;
level46.moveLimit = 24;
level46.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,3074,3074,2,3074,3074,2,2,
	2,2,0,0,2,0,0,2,2,
	2,2,0,5122,2,5122,0,2,2,
	2,2,7170,2,2,2,7170,2,2,
	2,2,0,3074,2,3074,0,2,2,
	2,2,0,0,2,0,0,2,2,
	2,2,5122,5122,2,5122,5122,2,2,
	514,514,514,514,514,514,514,514,514
};

level46.portalNum=0;

level46.newportalNum=0;

level46.oneStarScore =  76000;
level46.twoStarScore =  200000;
level46.threeStarScore =  300000;

level46.numberOfColours = 4;

level46.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level46.ingredientSpawnDensity = 8;
level46.numIngredientsOnScreen = 2;
level46.numCherry = 3;
level46.numChesnut = 4;
return level46;