local level73 = {};--{"scoreTargets":20000,40000,75000,"moveLimit":33,"numberOfColours":6,"randomSeed":0,"numIngredientsOnScreen":1,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,2,2,96,96,2,96,96,2,2,642,642,608,608,642,608,608,642,642,"ingredients":1,1,"portals":,"ingredientSpawnDensity":10,"gameModeName":"Drop down"}


level73.candyDropMode = 0;
level73.moveLimit = 50;
level73.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,10,3082,3082,3082,3082,3082,10,2,
	2,10,0,0,0,0,0,10,2,
	2,10,7178,7178,7178,7178,0,10,2,
	2,10,0,0,0,0,0,10,2,
	2,10,7178,7178,7178,7178,0,10,2,
	2,10,0,0,0,0,0,10,2,
	2,10,5130,5130,5130,5130,5130,10,2,
	2,2,2,2,2,2,2,2,2
};

level73.portalNum=0;

level73.newportalNum=0;


level73.oneStarScore =  60000;
level73.twoStarScore =  120000;
level73.threeStarScore =  150000;

level73.numberOfColours = 6;

level73.numjelly =  32;

level73.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

return level73;