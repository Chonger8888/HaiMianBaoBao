local level3 = {};--{"tileMap":0,0,0,0,0,0,0,0,0,0,0,18,18,18,18,18,0,0,0,18,2,2,2,2,2,18,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,"portals":,"gameModeName":"Classic moves","scoreTargets":4000,6000,8000,"moveLimit":18,"numberOfColours":5,"randomSeed":5596420,"protocolVersion":"0.1"}

level3.candyDropMode = 0;

level3.moveLimit = 8;

level3.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,18,18,18,18,18,0,0,
	0,18,2,2,2,2,2,18,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,0,2,2,2,2,2,0,0,
	0,0,0,0,0,0,0,0,0
}

level3.portalNum=0;

level3.newportalNum=0;

level3.oneStarScore =  5000;
level3.twoStarScore =  8000;
level3.threeStarScore =  10000;

level3.numberOfColours = 5;

level3.gameMode =  0;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level3.randomSeed = 927762023;   --随机种子
return level3;