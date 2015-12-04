local level8 = {};--{"tileMap":18,18,18,18,0,18,18,18,18,2,6,6,2,0,2,6,6,2,2,6,6,2,2,2,6,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,6,6,2,2,2,2,2,2,6,6,6,2,2,2,0,2,2,6,6,6,2,2,0,0,0,2,2,2,2,2,0,0,"portals":,"gameModeName":"Light up","scoreTargets":20000,30000,45000,"moveLimit":20,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1"}

level8.candyDropMode = 0;
level8.moveLimit = 15;
level8.CandyMapDataTable = {
	18,18,18,18,0,18,18,18,18,
	2,6,6,2,0,2,6,6,2,
	2,6,6,2,2,2,6,6,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,6,6,6,2,2,2,
	2,2,2,6,6,6,2,2,2,
	0,2,2,6,6,6,2,2,0,
	0,0,2,2,2,2,2,0,0
};

level8.portalNum=0;

level8.newportalNum=0;

level8.numjelly =  17;

level8.oneStarScore = 20000;
level8.twoStarScore = 30000;
level8.threeStarScore = 40000;

level8.numberOfColours = 5;

level8.gameMode = 1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level8;