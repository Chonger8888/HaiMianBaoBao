local level54 = {};--{"scoreTargets":25000,40000,60000,"moveLimit":55,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3074,2,3074,2,2,2,2,2,2,0,130,0,2,2,2,2,2,2,5122,2,5122,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,642,642,642,642,514,642,642,642,642,"ingredients":2,2,"portals":3,3,3,5,5,3,5,5,"ingredientSpawnDensity":15,"gameModeName":"Drop down"}


level54.candyDropMode = 0;
level54.moveLimit = 28;
level54.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,130,130,130,130,130,130,130,2,
	2,130,2,2,2,2,2,130,2,
	2,130,2,2,2,2,2,130,2,
	2,130,2,2,2,2,2,130,2,
	2,130,2,2,2,2,2,130,2,
	2,130,2,2,2,2,2,130,2,
	2,130,130,130,130,130,130,130,2,
	2,2,2,2,2,2,2,2,2
};

level54.portalNum=0;

level54.newportalNum=0;

level54.oneStarScore =  15000;
level54.twoStarScore =  40000;
level54.threeStarScore =  70000;

level54.numberOfColours = 6;

level54.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level54.collectItem = {
	0,60,	
};

return level54;