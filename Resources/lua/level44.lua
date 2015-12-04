local level44 = {};--{"scoreTargets":100000,150000,200000,"moveLimit":60,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":26,26,26,26,26,26,26,26,26,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,2,2,2,3074,2,2,2,0,0,2,2,2,0,2,2,2,0,0,2,2,2,5122,2,2,2,0,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,104,104,104,10,10,10,104,104,104,"portals":4,3,4,5,"gameModeName":"Light up"}


level44.candyDropMode = 0;
level44.moveLimit = 30;
level44.CandyMapDataTable = {
	26,26,26,26,26,26,26,26,26,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	96,96,96,96,96,96,96,96,96,
	10,10,10,10,10,10,10,10,10,
	96,96,96,96,96,96,96,96,96,
	10,10,10,10,10,10,10,10,10,
	104,104,104,104,104,104,104,104,104
};

level44.portalNum=0;

level44.newportalNum=0;

level44.numjelly =  36;

level44.oneStarScore =  75000;
level44.twoStarScore =  120000;
level44.threeStarScore =  160000;

level44.numberOfColours = 6;

level44.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level44.ingredientSpawnDensity = 35;
level44.numIngredientsOnScreen = 2;
level44.numCherry = 1;
level44.numChesnut = 3;
]]
return level44;