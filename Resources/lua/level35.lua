local level35 = {};--{"scoreTargets":100000,150000,200000,"moveLimit":60,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":26,26,26,26,26,26,26,26,26,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,2,2,2,3074,2,2,2,0,0,2,2,2,0,2,2,2,0,0,2,2,2,5122,2,2,2,0,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,"portals":4,3,4,5,"gameModeName":"Light up"}


level35.candyDropMode = 0;
level35.moveLimit = 28;
level35.CandyMapDataTable = {
	26,26,26,26,26,26,26,26,26,
	3082,10,10,10,10,10,10,10,3082,
	0,3082,10,10,10,10,10,3082,0,
	0,0,2,2,3074,2,2,0,0,
	0,0,0,2,0,2,0,0,0,
	0,0,2,2,5122,2,2,0,0,
	5216,5216,96,10,10,10,96,5216,5216,
	96,96,96,10,10,10,96,96,96,
	96,96,96,10,10,10,96,96,96
};

level35.portalNum=0;

level35.newportalNum=0;

level35.numjelly =  34;

level35.oneStarScore =  75000;
level35.twoStarScore =  195000;
level35.threeStarScore =  260000;

level35.numberOfColours = 5;

level35.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level35.ingredientSpawnDensity = 35;
level35.numIngredientsOnScreen = 2;
level35.numCherry = 1;
level35.numChesnut = 3;
]]
return level35;