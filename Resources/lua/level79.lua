local level79 = {};--{"gameModeName":"Drop down","scoreTargets":40000,70000,100000,"ingredientSpawnDensity":8,"moveLimit":40,"numberOfColours":5,"numIngredientsOnScreen":1,"randomSeed":0,"protocolVersion":"0.1","ingredients":2,2,"tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,130,130,130,130,130,130,130,130,130,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,514,514,800,514,514,514,800,514,514,"portals":}


level79.candyDropMode = 0;
level79.moveLimit = 40;
level79.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	130,130,130,130,130,130,130,130,130,
	1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,
	514,514,800,514,514,514,800,514,514
};

level79.portalNum=0;

level79.newportalNum=0;

level79.oneStarScore =  80000;
level79.twoStarScore =  150000;
level79.threeStarScore =  180000;

level79.numberOfColours = 6;

level79.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level79.ingredientSpawnDensity = 8;
level79.numIngredientsOnScreen = 1;
level79.numCherry = 2;
level79.numChesnut = 2;
return level79;