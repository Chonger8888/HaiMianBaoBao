local level13 = {};--{moveLimit:25,pepperCandyExplosionTurns:0,protocolVersion:0.1,numberOfColours:5,scoreTargets:22000,44000,66000,gameModeName:Light up,tileMap:0,0,0,0,0,0,0,0,0,0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,0,0,3094,6,6,6,6,6,6,3094,0,0,6,6,6,6,6,6,0,0,5126,6,6,6,6,6,6,5126,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,licoriceSpawn:0,randomSeed:0,licoriceMax:0,portals:0,3,10,0,5,10,7,3,10,7,5,10,pepperCandySpawn:0,pepperCandyMax:0}


level13.candyDropMode = 0;
level13.moveLimit = 15;
level13.CandyMapDataTable = {
	0,0,0,0,18,0,0,0,0,
	0,0,0,18,6,18,0,0,0,
	0,0,18,6,6,6,18,0,0,
	0,18,6,6,6,6,6,18,0,
	18,6,6,6,6,6,6,6,18,
	0,2,6,6,6,6,6,2,0,
	0,0,2,6,6,6,2,0,0,
	0,0,0,2,6,2,0,0,0,
	0,0,0,0,2,0,0,0,0
};

level13.portalNum=0;

level13.newportalNum=0;

level13.numjelly =  25;

level13.oneStarScore =  27000;
level13.twoStarScore =  50000;
level13.threeStarScore =  65000;

level13.numberOfColours = 5;

level13.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level13;