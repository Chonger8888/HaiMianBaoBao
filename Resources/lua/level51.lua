local level51 = {};--{"tileMap":0,22,0,22,0,22,0,22,0,0,3078,0,3078,0,3078,0,3078,0,0,0,0,0,0,0,0,0,0,0,0,22,0,22,0,22,0,0,0,0,3078,0,3078,0,3078,0,0,0,0,0,0,0,0,0,0,0,18,5122,5122,5122,5122,5122,5122,5122,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,"portals":2,4,2,6,4,4,4,6,6,4,6,6,7,1,7,6,5,1,5,6,3,1,3,6,1,1,1,6,"gameModeName":"Light up","scoreTargets":20000,60000,100000,"moveLimit":15,"numberOfColours":3,"randomSeed":0,"protocolVersion":"0.1"}


level51.candyDropMode = 0;
level51.moveLimit = 8;
level51.CandyMapDataTable = {
	0,22,0,22,0,22,0,22,0,
	0,3078,0,3078,0,3078,0,3078,0,
	0,0,0,0,0,0,0,0,0,
	0,0,22,0,22,0,22,0,0,
	0,0,3078,0,3078,0,3078,0,0,
	0,0,0,0,0,0,0,0,0,
	18,5122,5122,5122,5122,5122,5122,5122,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2
};

level51.portalNum=0;

level51.newportalNum=0;

level51.oneStarScore =  18000;
level51.twoStarScore =  100000;
level51.threeStarScore =  150000;

level51.numberOfColours = 3;

level51.numjelly =  14;

level51.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level51.ingredientSpawnDensity = 35;
level51.numIngredientsOnScreen = 2;
level51.numCherry = 0;
level51.numChesnut = 1;
]]
return level51;