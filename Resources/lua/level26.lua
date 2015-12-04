local level26 = {};--{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level26.candyDropMode = 0;
level26.moveLimit = 16;
level26.CandyMapDataTable = {
	0,18,18,18,18,18,18,18,18,
	0,2,2,2,2,2,2,2,2,
	0,2,2,130,130,130,130,2,2,
	0,2,2,130,2,2,130,2,2,
	0,2,2,130,2,2,130,2,2,
	0,2,2,130,130,130,130,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
};

level26.portalNum=0;

level26.newportalNum=0;

level26.oneStarScore =  18000;
level26.twoStarScore =  70000;
level26.threeStarScore = 130000;

level26.numberOfColours = 5;

level26.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level26.collectItem = {
	0,30,
	4,30,
	
};

level26.ingredientSpawnDensity = 7;
level26.numIngredientsOnScreen = 2;
level26.numCherry = 3;
level26.numChesnut = 3;

return level26;