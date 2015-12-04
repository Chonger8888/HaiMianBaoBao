local level4 = {};--{"scoreTargets":4500,6000,9000,"moveLimit":15,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,18,0,2,2,2,2,2,0,18,2,18,2,2,2,2,2,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,0,2,0,0,2,2,2,2,2,0,0,"portals":,"gameModeName":"Classic moves"}

level4.candyDropMode = 0;
level4.moveLimit = 11;
level4.CandyMapDataTable = {
	0,0,18,18,18,18,18,0,0,
	0,0,2,2,2,2,2,0,0,
	18,18,2,2,2,2,2,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
};

level4.portalNum=0;

level4.newportalNum=0;

level4.oneStarScore =  7000;
level4.twoStarScore =  10000;
level4.threeStarScore =  14000;

level4.numberOfColours = 5;

level4.gameMode =  0;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level4;