local level1 = {};--{"tileMap":0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,18,18,18,18,18,18,18,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"portals":,"gameModeName":"Classic moves","scoreTargets":300,400,500,"moveLimit":6,"numberOfColours":6,"randomSeed":1088126,"protocolVersion":"0.1"}

level1.candyDropMode = 0;
level1.moveLimit = 8;
level1.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};

level1.portalNum=0;

level1.newportalNum=0;

level1.oneStarScore =  500;
level1.twoStarScore =  1000;
level1.threeStarScore =  1500;

level1.numberOfColours = 5;

level1.gameMode =  0;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level1.randomSeed = 10151018;   --随机种子
return level1;