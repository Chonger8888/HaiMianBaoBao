local level81 = {};--{"randomSeed":0,"moveLimit":45,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3074,3074,3074,3074,3074,3074,3074,3074,3074,0,0,0,0,0,0,0,0,0,5408,5254,5412,5254,5412,5254,5412,5254,5408,130,292,134,292,134,292,134,292,130,288,134,292,134,292,134,292,134,288,130,292,134,292,134,292,134,292,130,"portals":0,3,0,5,1,3,1,5,2,3,2,5,3,3,3,5,4,3,4,5,5,3,5,5,6,3,6,5,7,3,7,5,8,3,8,5,"gameModeName":"Light up","scoreTargets":30000,80000,140000,"numberOfColours":5}


level81.candyDropMode = 0;
level81.moveLimit = 45;
level81.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	3074,3074,3074,3074,3074,3074,3074,3074,3074,
	0,0,0,0,0,0,0,0,0,
	5408,5254,5412,5254,5412,5254,5412,5254,5408,
	130,292,134,292,134,292,134,292,130,
	288,134,292,134,292,134,292,134,288,
	130,292,134,292,134,292,134,292,130
};

level81.portalNum=0;

level81.newportalNum=0;


level81.oneStarScore =  60000;
level81.twoStarScore =  120000;
level81.threeStarScore =  180000;

level81.numberOfColours = 5;

level81.numjelly =  28;

level81.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level81.ingredientSpawnDensity = 35;
level81.numIngredientsOnScreen = 2;
level81.numCherry = 0;
level81.numChesnut = 1;
]]
return level81;