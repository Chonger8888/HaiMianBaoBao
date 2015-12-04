local level40= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level40.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level40.moveLimit = 23;  --  步数
level40.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,130,130,130,130,130,130,130,130,
	0,97,97,97,97,97,97,97,97,
	0,130,130,130,130,130,130,130,130,
};

level40.portalNum=0;

level40.newportalNum=0;

level40.oneStarScore =  20000;
level40.twoStarScore =  90000;
level40.threeStarScore =  150000;

level40.numberOfColours = 5;

level40.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level40.collectItem = {
	1,60,
	2,60,
};

--[[
level40.ingredientSpawnDensity = 12;
level40.numIngredientsOnScreen = 1;
level40.numCherry = 3;
level40.numChesnut = 3;
]]
return level40;