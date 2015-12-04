local level62 = {};--{"scoreTargets":20000,40000,80000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,18,0,2,2,2,2,2,2,2,2,2,130,2,2,2,2,2,2,2,130,2,130,2,2,2,2,2,130,2,2,2,130,2,2,2,130,2,2,2,2,2,130,2,130,2,2,2,2,2,2,2,130,2,2,2,2,130,130,130,130,130,130,130,130,130,514,514,514,514,514,514,514,514,514,"ingredients":2,2,"portals":,"ingredientSpawnDensity":12,"gameModeName":"Drop down"}


level62.candyDropMode = 0;
level62.moveLimit = 33;
level62.CandyMapDataTable = {
	0,18,18,18,18,18,18,18,0,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	130,130,130,130,130,130,130,130,130,
	2,2,2,2,2,2,2,2,2,
	130,130,130,130,130,130,130,130,130,
	97,97,97,97,97,97,97,97,97,
	514,514,514,514,514,514,514,514,514
};

level62.portalNum=0;

level62.newportalNum=0;

level62.oneStarScore =  40000;
level62.twoStarScore =  90000;
level62.threeStarScore =  130000;

level62.numberOfColours = 6;

level62.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level62.ingredientSpawnDensity = 10;
level62.numIngredientsOnScreen = 1;
level62.numCherry = 2;
level62.numChesnut = 2;
return level62;