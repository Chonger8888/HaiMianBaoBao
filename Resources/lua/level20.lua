local level20 = {};--{"scoreTargets":45000,75000,100000,"licoriceSpawn":0,"protocolVersion":"0.1","randomSeed":0,"pepperCandySpawn":0,"moveLimit":40,"gameModeName":"Light up","portals":8,2,0,8,6,0,0,2,1024,0,6,1024,"licoriceMax":0,"pepperCandyExplosionTurns":0,"numberOfColours":6,"pepperCandyMax":0,"tileMap":18,18,18,18,0,22,22,22,22,2,2,2,2,0,6,6,6,6,3074,2,2,2,0,6,6,6,3078,0,6,6,6,22,6,6,6,0,0,6,6,6,6,6,6,6,0,0,6,6,6,6,6,6,6,0,5126,6,6,6,0,2,2,2,5122,6,6,6,6,0,2,2,2,2,6,6,6,6,0,2,2,2,2}

level20.candyDropMode = 0;
level20.moveLimit = 20;
level20.CandyMapDataTable = {
	18,18,18,18,0,22,22,22,22,
	2,2,2,2,0,6,6,6,6,
	3074,2,2,2,0,6,6,6,3078,
	0,2,2,2,18,2,2,2,0,
	0,2,2,10,10,10,2,2,0,
	0,2,2,2,2,2,2,2,0,
	5126,6,6,6,0,2,2,2,5122,
	6,6,6,6,0,2,2,2,2,
	6,6,6,6,0,2,2,2,2
};

level20.portalNum=0;

level20.newportalNum=0;

level20.numjelly =  27;

level20.oneStarScore =  33000;
level20.twoStarScore =  60000;
level20.threeStarScore =  90000;

level20.numberOfColours = 5;

level20.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level20.ingredientSpawnDensity = 35;
level20.numIngredientsOnScreen = 2;
level20.numCherry = 0;
level20.numChesnut = 1;
]]
return level20;