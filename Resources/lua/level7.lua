local level7 = {};--{"gameModeName":"Light up","scoreTargets":60000,75000,85000,"numberOfColours":6,"moveLimit":50,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,6,6,6,2,6,6,6,2,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,2,6,6,6,6,6,6,6,2,2,2,2,6,6,6,2,2,2,0,2,2,2,2,2,2,2,0,"portals":}


level7.candyDropMode = 0;
level7.moveLimit = 10;
level7.CandyMapDataTable = {
	0,18,18,18,18,18,18,18,0,
	0,2,2,2,2,2,2,2,0,
	0,2,6,2,2,2,6,2,0,
	0,2,2,6,2,6,2,2,0,
	0,2,2,2,6,2,2,2,0,
	0,2,2,6,2,6,2,2,0,
	0,2,6,2,2,2,6,2,0,
	0,2,2,2,2,2,2,2,0,
	0,0,0,0,0,0,0,0,0,
};

level7.portalNum=0;

level7.newportalNum=0;

level7.numjelly =  9;

level7.oneStarScore =  15000;
level7.twoStarScore =  30000;
level7.threeStarScore =  40000;

level7.numberOfColours = 5;

level7.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果
return level7;