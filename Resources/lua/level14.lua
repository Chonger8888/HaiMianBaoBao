local level14 = {};--{moveLimit:25,pepperCandyExplosionTurns:0,protocolVersion:0.1,numberOfColours:5,scoreTargets:22000,44000,66000,gameModeName:Light up,tileMap:0,0,0,0,0,0,0,0,0,0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,0,0,3094,6,6,6,6,6,6,3094,0,0,6,6,6,6,6,6,0,0,5126,6,6,6,6,6,6,5126,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,licoriceSpawn:0,randomSeed:0,licoriceMax:0,portals:0,3,10,0,5,10,7,3,10,7,5,10,pepperCandySpawn:0,pepperCandyMax:0}


level14.candyDropMode = 0;
level14.moveLimit = 13;
level14.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	3074,3074,2,2,2,2,2,3074,3074,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	5122,5122,2,2,2,2,2,5122,5122,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2
};

level14.portalNum=0;

level14.newportalNum=0;

level14.oneStarScore =  10000;
level14.twoStarScore =  30000;
level14.threeStarScore =  50000;

level14.numberOfColours = 5;

level14.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level14.collectItem = {
	0,30,
	4,30,
};

return level14;