local level50 = {};--{"tileMap":18,18,18,18,0,18,18,18,18,2,10,10,2,0,2,10,10,2,2,10,10,2,0,2,10,10,2,3074,3074,3074,3074,0,3074,3074,3074,3074,0,0,0,0,0,0,0,0,0,5122,5122,5122,5122,0,5122,5122,5122,5122,2,10,10,2,0,2,10,10,2,2,10,10,2,0,2,10,10,2,2,2,2,2,0,2,2,2,2,"portals":0,3,0,5,1,3,1,5,2,3,2,5,3,3,3,5,5,3,5,5,6,3,6,5,7,3,7,5,8,3,8,5,"gameModeName":"Light up","scoreTargets":32000,"50000",70000,"moveLimit":14,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1"}


level50.candyDropMode = 0;
level50.moveLimit = 15;
level50.CandyMapDataTable = {
	18,18,18,18,0,18,18,18,18,
	2,10,10,2,0,2,10,10,2,
	2,10,10,2,0,2,10,10,2,
	3074,3074,3074,3074,0,3074,3074,3074,3074,
	0,0,0,0,0,0,0,0,0,
	5122,5122,5122,5122,0,5122,5122,5122,5122,
	2,10,10,2,0,2,10,10,2,
	2,10,10,2,0,2,10,10,2,
	2,2,2,2,0,2,2,2,2
};

level50.portalNum=0;

level50.newportalNum=0;

level50.numjelly =  16;

level50.oneStarScore =  32000;
level50.twoStarScore =  50000;
level50.threeStarScore =  70000;

level50.numberOfColours = 5;

level50.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level50.ingredientSpawnDensity = 35;
level50.numIngredientsOnScreen = 2;
level50.numCherry = 0;
level50.numChesnut = 1;
]]
return level50;