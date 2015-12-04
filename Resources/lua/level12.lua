local level12= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level12.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level12.moveLimit = 15;  --  步数
level12.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,0,18,0,0,18,0,18,
	0,2,0,0,2,2,0,0,2,
	0,0,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
};

level12.portalNum=0;

level12.newportalNum=0;

level12.oneStarScore =  8000;
level12.twoStarScore =  11000;
level12.threeStarScore =  13000;

level12.numberOfColours = 6;

level12.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level12.collectItem = {
	3,20,
	4,20,
};

--[[
level12.ingredientSpawnDensity = 12;
level12.numIngredientsOnScreen = 1;
level12.numCherry = 3;
level12.numChesnut = 3;
]]
return level12;