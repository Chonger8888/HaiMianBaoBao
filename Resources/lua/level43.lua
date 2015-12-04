local level43 = {};--{"scoreTargets":100000,150000,200000,"moveLimit":60,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":26,26,26,26,26,26,26,26,26,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,2,2,2,3074,2,2,2,0,0,2,2,2,0,2,2,2,0,0,2,2,2,5122,2,2,2,0,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,"portals":4,3,4,5,"gameModeName":"Light up"}


level43.candyDropMode = 0;
level43.moveLimit = 22;
level43.CandyMapDataTable = {
	0,0,0,0,26,0,0,0,0,
	0,0,0,10,10,10,0,0,0,
	0,0,10,10,10,10,10,0,0,
	0,2,96,96,96,96,96,2,0,
	0,2,96,96,96,96,96,2,0,
	0,2,96,96,96,96,96,2,0,
	2,2,2,10,10,10,2,2,2,
	2,2,2,10,10,10,2,2,2,
	2,2,2,10,10,10,2,2,2
};

level43.portalNum=0;

level43.newportalNum=0;

level43.numjelly =  18;

level43.oneStarScore =  40000;
level43.twoStarScore =  60000;
level43.threeStarScore =  80000;

level43.numberOfColours = 6;

level43.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level43.ingredientSpawnDensity = 35;
level43.numIngredientsOnScreen = 2;
level43.numCherry = 1;
level43.numChesnut = 3;
]]
return level43;