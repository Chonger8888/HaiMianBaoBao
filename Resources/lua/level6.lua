local level6 = {};--{"scoreTargets":9000,11000,13000,"moveLimit":16,"numberOfColours":5,"randomSeed":221852,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,"portals":,"gameModeName":"Light up"}


level6.candyDropMode = 0;
level6.moveLimit = 5;
level6.CandyMapDataTable = {
	0,18,18,18,18,18,18,0,0,
	0,2,2,2,2,2,2,0,0,
	0,2,6,6,6,6,2,0,0,
	0,2,6,6,6,6,2,0,0,
	0,2,6,6,6,6,2,0,0,
	0,2,2,2,2,2,2,0,0,
	0,2,2,2,2,2,2,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0
};

level6.portalNum=0;

level6.newportalNum=0;

level6.oneStarScore =  12000;
level6.twoStarScore =  22000;
level6.threeStarScore =  35000;

level6.numberOfColours = 5;

level6.numjelly =  12;

level6.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果


return level6;