local level24 = {};--{moveLimit:35,licoriceMax:0,protocolVersion:0.1,pepperCandyExplosionTurns:0,numberOfColours:5,scoreTargets:75000,165000,210000,pepperCandySpawn:0,pepperCandyMax:0,tileMap:18,18,18,0,0,0,18,18,18,2,10,10,18,18,18,10,10,2,3074,10,10,10,2,10,10,10,3074,0,2,10,10,10,10,10,2,0,0,2,2,10,10,10,2,2,0,0,2,10,10,10,10,10,2,0,5130,10,10,10,2,10,10,10,5130,10,10,10,2,2,2,10,10,10,6,10,10,0,0,0,10,10,6,randomSeed:0,gameModeName:Light up,portals:0,2,10,0,6,10,8,2,10,8,6,10,licoriceSpawn:0}


level24.candyDropMode = 0;
level24.moveLimit = 25;
level24.CandyMapDataTable = {
	18,18,18,0,0,0,18,18,18,
	2,2,2,2,0,2,2,2,2,
	3074,2,2,2,2,2,2,2,3074,
	0,3074,2,2,2,2,2,3074,0,
	0,0,2,2,2,2,2,0,0,
	0,5122,2,2,2,2,2,5122,0,
	5122,2,2,2,514,2,2,2,5122,
	2,2,2,514,0,514,2,2,2,
	514,514,514,0,0,0,514,514,514
};

level24.portalNum=0;

level24.newportalNum=0;

level24.oneStarScore =  6000;
level24.twoStarScore =  23000;
level24.threeStarScore =  50000;

level24.numberOfColours = 6;

level24.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level24.collectItem = {
	0,25,
	3,25,
};


--[[level24.ingredientSpawnDensity = 12;
level24.numIngredientsOnScreen = 2;
level24.numChesnut = 4;]]

return level24;