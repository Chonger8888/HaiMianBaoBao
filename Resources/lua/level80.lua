local level80 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level80.candyDropMode = 0;
level80.moveLimit = 50;
level80.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	10,10,10,10,10,10,10,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
	10,10,130,10,0,10,130,10,10,
};

level80.portalNum=0;

level80.newportalNum=0;


level80.oneStarScore =  40000;
level80.twoStarScore =  60000;
level80.threeStarScore =  80000;

level80.numberOfColours = 6;

level80.numjelly =  51;

level80.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level80;