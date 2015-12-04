local level57 = {};--{"scoreTargets":25000,40000,60000,"moveLimit":55,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3074,2,3074,2,2,2,2,2,2,0,130,0,2,2,2,2,2,2,5122,2,5122,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,642,642,642,642,514,642,642,642,642,"ingredients":2,2,"portals":3,3,3,5,5,3,5,5,"ingredientSpawnDensity":15,"gameModeName":"Drop down"}


level57.candyDropMode = 0;
level57.moveLimit = 20;
level57.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,130,130,130,130,130,130,130,2,
	2,2,130,97,97,97,130,2,2,
	2,2,2,130,2,130,2,2,2,
	2,2,130,97,97,97,130,2,2,
	2,130,130,130,2,130,130,130,2,
	2,2,130,97,97,97,130,2,2,
	2,2,2,130,2,130,2,2,2,
	2,2,2,2,130,2,2,2,2
};

level57.portalNum=0;

level57.newportalNum=0;

level57.oneStarScore =  13000;
level57.twoStarScore =  60000;
level57.threeStarScore =  80000;

level57.numberOfColours = 6;

level57.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level57.collectItem = {
    2,30,
    1,30,	
	
};

return level57;