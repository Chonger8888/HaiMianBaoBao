local level68 = {};--{"scoreTargets":70000,90000,125000,"moveLimit":35,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,0,18,18,18,18,2,2,2,2,0,2,2,2,2,2,2,2,10,26,10,2,2,2,3074,3074,10,138,138,138,10,3074,3074,0,0,10,138,138,138,10,0,0,5122,5122,10,138,138,138,10,5122,5122,2,2,2,10,10,10,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,0,2,2,2,2,"portals":0,3,0,5,1,3,1,5,7,3,7,5,8,3,8,5,"gameModeName":"Light up"}


level68.candyDropMode = 0;
level68.moveLimit = 35;
level68.CandyMapDataTable = {
	18,18,18,18,0,18,18,18,18,
	2,2,2,2,0,2,2,2,2,
	2,2,10,10,26,10,10,2,2,
	3074,3074,10,138,138,138,10,3074,3074,
	0,0,10,138,138,138,10,0,0,
	5122,5122,10,138,138,138,10,5122,5122,
	2,2,10,10,10,10,10,2,2,
	2,2,2,2,0,2,2,2,2,
	2,2,2,2,0,2,2,2,2
};

level68.portalNum=0;

level68.newportalNum=0;


level68.oneStarScore =  80000;
level68.twoStarScore =  160000;
level68.threeStarScore =  200000;

level68.numberOfColours = 6;

level68.numjelly =  25;

level68.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level68.ingredientSpawnDensity = 35;
level68.numIngredientsOnScreen = 2;
level68.numCherry = 0;
level68.numChesnut = 1;
]]
return level68;