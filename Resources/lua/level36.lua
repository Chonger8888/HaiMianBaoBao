local level36 = {};--{protocolVersion:0.2,licoriceMax:0,randomSeed:0,licoriceSpawn:0,portals:0,2,10,0,4,10,8,2,10,8,4,10,4,4,10,4,6,10,pepperCandyMax:0,numberOfColours:6,pepperCandyExplosionTurns:0,gameModeName:Light up,tileMap:18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,3074,1,2,1,2,1,2,1,3074,0,1,1,4,4,4,1,1,0,5121,1,4,4,3076,4,4,1,5121,4,4,4,4,0,4,4,4,4,4,4,4,4,5124,4,4,4,4,1,4,4,4,4,4,4,4,1,1,4,4,4,4,4,4,4,1,moveLimit:40,pepperCandySpawn:0,scoreTargets:40000,70000,100000}


level36.candyDropMode = 1;
level36.moveLimit = 18;
level36.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	3074,1,2,1,2,1,2,1,3074,
	0,1,1,4,4,4,1,1,0,
	5121,1,4,4,3076,4,4,1,5121,
	4,4,4,4,0,4,4,4,4,
	4,4,4,4,5124,4,4,4,4,
	1,4,4,4,4,4,4,4,1,
	1,4,4,4,4,4,4,4,1
};

level36.portalNum=0;

level36.newportalNum=0;

level36.numjelly =  39;

level36.oneStarScore =  42000;
level36.twoStarScore =  65000;
level36.threeStarScore =  93000;

level36.numberOfColours = 6;

level36.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level36;