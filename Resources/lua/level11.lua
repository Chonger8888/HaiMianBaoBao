local level11 = {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level11.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level11.moveLimit = 12;  --  步数
level11.CandyMapDataTable = {
	0,0,0,18,18,18,0,0,0,
	0,0,0,2,2,2,0,0,0,
	0,0,0,2,2,2,0,0,0,
	18,18,18,2,2,2,18,18,18,
	2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,
	0,0,0,2,2,2,0,0,0,
	0,0,0,2,2,2,0,0,0,
	0,0,0,2,2,2,0,0,0
};

level11.portalNum=0;

level11.newportalNum=0;

level11.oneStarScore =  5000;
level11.twoStarScore =  13000;
level11.threeStarScore =  18000;

level11.numberOfColours = 5;

level11.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level11.collectItem = {
	4,20,
};

--[[
level11.ingredientSpawnDensity = 12;
level11.numIngredientsOnScreen = 1;
level11.numCherry = 3;
level11.numChesnut = 3;
]]
return level11;