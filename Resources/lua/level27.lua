local level27 = {};--{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level27.candyDropMode = 0;
level27.moveLimit = 22;
level27.CandyMapDataTable = {
	0,0,0,18,18,18,0,0,0,
	0,0,2,2,3074,2,2,0,0,
	0,2,2,3074,0,3074,2,2,0,
	2,2,2,0,0,0,2,2,2,
	2,2,2,0,0,0,2,2,2,
	0,2,2,0,0,0,2,2,0,
	0,0,2,5122,0,5122,2,0,0,
	0,0,0,2,5122,2,0,0,0,
	0,0,0,2,2,2,0,0,0,
};

level27.portalNum=0;

level27.newportalNum=0;

level27.oneStarScore =  4000;
level27.twoStarScore =  15000;
level27.threeStarScore =  23500;

level27.numberOfColours = 5;

level27.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level27.collectItem = {
	3,20,
	2,20,
	0,20,
	
};

level27.ingredientSpawnDensity = 10;
level27.numIngredientsOnScreen = 2;
level27.numCherry = 2;
level27.numChesnut = 2;
return level27;