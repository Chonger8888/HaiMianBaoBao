local level29 = {}; --{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level29.candyDropMode = 0;
level29.moveLimit = 26;
level29.CandyMapDataTable = {
	18,0,0,18,0,18,0,0,18,
	2,0,0,2,0,2,0,0,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
};

level29.portalNum=0;

level29.newportalNum=0;

level29.oneStarScore =  6000;
level29.twoStarScore =  35000;
level29.threeStarScore =  60000;

level29.numberOfColours = 6;

level29.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level29.collectItem = {
	5,25,
	2,25,	
};

level29.ingredientSpawnDensity = 5;
level29.numIngredientsOnScreen = 2;
level29.numCherry = 2;
level29.numChesnut = 2;

return level29;