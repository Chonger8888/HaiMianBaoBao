local level15 = {};--{"gameModeName":"Classic","scoreTargets":15000,25000,45000,"timeLimit":60,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,18,0,0,2,2,2,2,2,2,2,18,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,"portals":}


level15.candyDropMode = 0;
level15.moveLimit = 30;
level15.CandyMapDataTable = {
	0,18,18,18,18,18,18,18,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0
};

level15.portalNum=0;

level15.newportalNum=0;

level15.oneStarScore =  30000;
level15.twoStarScore =  55000;
level15.threeStarScore =  80000;

level15.numberOfColours = 5;

level15.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level15.timeLimit = 60
--[[
level15.ingredientSpawnDensity = 35
level15.numIngredientsOnScreen = 2
level15.numCherry = 1
level15.numChesnut = 3
]]
return level15;