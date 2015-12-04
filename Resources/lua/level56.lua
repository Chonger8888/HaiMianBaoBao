local level56 = {};--{"scoreTargets":25000,40000,60000,"moveLimit":55,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3074,2,3074,2,2,2,2,2,2,0,130,0,2,2,2,2,2,2,5122,2,5122,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,642,642,642,642,514,642,642,642,642,"ingredients":2,2,"portals":3,3,3,5,5,3,5,5,"ingredientSpawnDensity":15,"gameModeName":"Drop down"}


level56.candyDropMode = 0;
level56.moveLimit = 32;
level56.CandyMapDataTable = {
	0,0,0,0,0,0,18,18,18,
	0,0,0,0,0,2,2,130,130,
	0,0,0,0,2,2,2,2,130,
	0,0,0,2,2,2,2,2,130,
	0,0,2,2,2,2,2,2,130,
	0,2,2,2,2,2,2,2,130,
	2,2,2,2,2,2,2,2,130,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
};

level56.portalNum=0;

level56.newportalNum=0;

level56.oneStarScore =  20000;
level56.twoStarScore =  75000;
level56.threeStarScore =  90000;

level56.numberOfColours = 6;

level56.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level56.collectItem = {
    0,55,
    5,55,	
	
};
return level56;