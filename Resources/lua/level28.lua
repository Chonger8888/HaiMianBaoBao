local level28 = {};--{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level28.candyDropMode = 0;
level28.moveLimit = 18;
level28.CandyMapDataTable = {
	3094,3094,3094,3094,3094,3094,3094,3094,3094,
	0,0,0,0,0,0,0,0,0,
	5122,5122,5122,5122,5122,5122,5122,5122,5122,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
	
};

level28.portalNum=0;

level28.newportalNum=0;

level28.numjelly =  9;

level28.oneStarScore =  25000;
level28.twoStarScore =  50000;
level28.threeStarScore =  72000;

level28.numberOfColours = 5;

level28.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level28.ingredientSpawnDensity = 5;
level28.numIngredientsOnScreen = 2;
level28.numCherry = 2;
level28.numChesnut = 2;
return level28;