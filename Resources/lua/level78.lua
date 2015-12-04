local level78 = {};--{"gameModeName":"Light up","scoreTargets":20000,60000,100000,"moveLimit":50,"numberOfColours":6,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3074,3074,2,2,2,2,2,3074,3074,0,0,2,2,2,2,2,0,0,5126,5408,130,2,2,2,130,5408,5126,6,288,130,2,2,2,130,288,6,6,288,130,2,2,2,130,288,6,6,288,130,2,2,2,130,288,6,"portals":0,3,0,5,1,3,1,5,7,3,7,5,8,3,8,5}


level78.candyDropMode = 0;
level78.moveLimit = 50;
level78.CandyMapDataTable = {
	18,18,18,18,18,18,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	3074,3074,2,2,2,2,2,3074,3074,
	0,0,2,2,2,2,2,0,0,
	5126,5408,130,2,2,2,130,5408,5126,
	6,288,130,2,2,2,130,288,6,
	6,288,130,2,2,2,130,288,6,
	6,288,130,2,2,2,130,288,6
};

level78.portalNum=0;

level78.newportalNum=0;


level78.oneStarScore =  60000;
level78.twoStarScore =  130000;
level78.threeStarScore =  150000;

level78.numberOfColours = 6;

level78.numjelly =  8;

level78.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level78.ingredientSpawnDensity = 35;
level78.numIngredientsOnScreen = 2;
level78.numCherry = 0;
level78.numChesnut = 1;
]]
return level78;