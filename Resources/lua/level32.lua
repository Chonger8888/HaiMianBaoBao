local level32 = {}; --{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level32.candyDropMode = 0;
level32.moveLimit = 20;
level32.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,3074,3074,3074,2,2,2,
	2,2,2,0,0,0,2,2,2,
	2,2,2,5122,5122,5122,2,2,2,
	2,2,2,2,3074,2,2,2,2,
	2,2,2,3074,0,3074,2,2,2,
	2,2,2,0,0,0,2,2,2,
	2,2,2,0,0,0,2,2,2,
	514,514,514,5634,5634,5634,514,514,514
};

level32.portalNum=0;

level32.newportalNum=0;

level32.oneStarScore =  45000;
level32.twoStarScore =  80000;
level32.threeStarScore =  120000;

level32.numberOfColours = 5;

level32.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level32.ingredientSpawnDensity = 5;
level32.numIngredientsOnScreen = 2;
level32.numCherry = 2;
level32.numChesnut = 2;

return level32;