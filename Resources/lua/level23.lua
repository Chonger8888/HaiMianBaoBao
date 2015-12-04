local level23 = {};--{"gameModeName":"Classic","scoreTargets":15000,25000,45000,"timeLimit":60,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":0,18,18,18,18,18,18,0,0,0,2,2,2,2,2,2,18,0,0,2,2,2,2,2,2,2,18,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,"portals":}


level23.candyDropMode = 0;
level23.moveLimit =18;
level23.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,0,2,2,2,2,0,2,
	0,2,2,0,6,6,0,2,2,
	0,2,2,6,0,0,6,2,2,
	0,2,2,6,0,0,6,2,2,
	0,2,2,0,6,6,0,2,2,
	0,2,0,2,2,2,2,0,2,
	0,2,2,2,2,2,2,2,2,
};

level23.portalNum=0;

level23.newportalNum=0;

level23.numjelly =  8;

level23.oneStarScore =  10000;
level23.twoStarScore =  20000;
level23.threeStarScore =  31000;

level23.numberOfColours = 5;

level23.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level23.ingredientSpawnDensity = 35
level23.numIngredientsOnScreen = 2
level23.numCherry = 1
level23.numChesnut = 3
]]
return level23;