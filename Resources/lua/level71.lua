local level71 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level71.candyDropMode = 0;
level71.moveLimit = 40;
level71.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,10,10,10,10,10,10,0,2,
	2,10,10,10,10,10,0,10,2,
	2,10,10,10,10,0,10,10,2,
	2,10,10,10,0,10,10,10,2,
	2,10,10,0,10,10,10,10,2,
	2,10,0,10,10,10,10,10,2,
	2,0,10,10,10,10,10,10,2,
	2,2,2,2,2,2,2,2,2
};

level71.portalNum=0;

level71.newportalNum=0;


level71.oneStarScore =  40000;
level71.twoStarScore =  130000;
level71.threeStarScore =  180000;

level71.numberOfColours = 6;

level71.numjelly =  42;

level71.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level71;