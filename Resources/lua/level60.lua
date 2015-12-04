local level60 = {};--{"portals":,"timeLimit":120,"gameModeName":"Classic","scoreTargets":22000,33000,44000,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,130,130,130,130,130,130,130,130,2,2,2,2,2,2,2,2,2,130,130,130,130,130,130,130,130,130,2,2,2,2,130,2,2,2,2,2,2,2,2,130,2,2,2,2,0,0,0,2,130,2,0,0,0}


level60.candyDropMode = 0;
level60.moveLimit = 40;
level60.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,130,2,2,2,2,
	2,2,2,130,2,130,2,2,2,
	2,2,130,2,2,2,130,2,2,
	2,130,2,2,2,2,2,130,2,
	2,2,130,2,2,2,130,2,2,
	2,2,2,130,2,130,2,2,2,
	2,2,2,2,130,2,2,2,2,
	0,0,0,2,2,2,0,0,0
};

level60.portalNum=0;

level60.newportalNum=0;

level60.oneStarScore =  70000;
level60.twoStarScore =  130000;
level60.threeStarScore =  170000;

level60.numberOfColours = 5;

level60.gameMode =  3;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level60.timeLimit = 60;

--[[
level60.ingredientSpawnDensity = 35;
level60.numIngredientsOnScreen = 2;
level60.numCherry = 0;
level60.numChesnut = 1;
]]
return level60;