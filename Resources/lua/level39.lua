local level39= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level39.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level39.moveLimit = 25;  --  步数
level39.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,130,2,2,2,2,2,2,130,
	0,130,130,2,2,2,2,130,130,
	0,130,130,130,2,2,130,130,130,
	0,130,130,130,2,2,130,130,130,
	0,130,130,2,130,130,2,130,130,
	0,130,2,130,130,130,130,2,130,
	0,2,130,130,130,130,130,130,2,
};

level39.portalNum=0;

level39.newportalNum=0;

level39.oneStarScore =  6000;
level39.twoStarScore =  28000;
level39.threeStarScore =  50000;

level39.numberOfColours = 6;

level39.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level39.collectItem = {
	1,30,
};

--[[
level39.ingredientSpawnDensity = 12;
level39.numIngredientsOnScreen = 1;
level39.numCherry = 3;
level39.numChesnut = 3;
]]
return level39;