local level21 = {};--{moveLimit:30,portals:,licoriceSpawn:0,protocolVersion:0.1,licoriceMax:0,numberOfColours:4,pepperCandyMax:0,scoreTargets:75000,150000,230000,pepperCandyExplosionTurns:0,gameModeName:Light up,tileMap:20,22,22,22,0,22,22,22,20,6,6,6,6,0,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,0,6,6,6,6,4,6,6,6,0,6,6,6,4,4,4,6,6,0,6,6,4,4,4,4,4,6,0,6,4,4,4,4,4,4,4,0,4,4,4,4,randomSeed:0,pepperCandySpawn:0}


level21.candyDropMode = 0;
level21.moveLimit = 18;
level21.CandyMapDataTable = {
	20,22,22,22,0,22,22,22,20,
	6,6,6,6,0,6,6,6,6,
	6,6,6,6,0,6,6,6,6,
	6,6,6,6,0,6,6,6,6,
	6,6,6,6,0,6,6,6,6,
	4,6,6,6,0,6,6,6,4,
	4,4,6,6,0,6,6,4,4,
	4,4,4,6,0,6,4,4,4,
	4,4,4,4,0,4,4,4,4
};

level21.portalNum=0;

level21.newportalNum=0;

level21.numjelly =  72;

level21.oneStarScore =  74000;
level21.twoStarScore =  160000;
level21.threeStarScore =  230000;

level21.numberOfColours = 4;

level21.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[
level21.ingredientSpawnDensity = 35;
level21.numIngredientsOnScreen = 2;
level21.numCherry = 0;
level21.numChesnut = 1;
]]
return level21;