local level5 = {};--{"scoreTargets":9000,11000,13000,"moveLimit":16,"numberOfColours":5,"randomSeed":221852,"protocolVersion":"0.1","tileMap":0,0,18,18,18,18,18,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,6,6,6,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,"portals":,"gameModeName":"Light up"}


level5.candyDropMode = 0;
level5.moveLimit = 11;
level5.CandyMapDataTable = {
	0,0,18,18,18,18,18,0,0,
	0,0,2,6,6,6,2,0,0,
	0,0,2,6,6,6,2,0,0,
	0,0,2,6,6,6,2,0,0,
	0,0,2,6,6,6,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0
};

level5.portalNum=0;

level5.newportalNum=0;

level5.oneStarScore =  13000;
level5.twoStarScore =  25000;
level5.threeStarScore =  43000;

level5.numjelly =  12;

level5.numberOfColours = 5;

level5.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果


return level5;