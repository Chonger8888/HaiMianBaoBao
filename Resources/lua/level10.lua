local level10 = {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level10.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level10.moveLimit = 12;  --  步数
level10.CandyMapDataTable = {
	0,18,0,18,0,18,0,18,0,
	0,2,0,2,0,2,0,2,0,
	0,0,2,0,2,0,2,0,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,0,0,0,0,0,0,0,0,
};

level10.portalNum=0;

level10.newportalNum=0;

level10.oneStarScore =  5000;
level10.twoStarScore =  13000;
level10.threeStarScore =  20000;

level10.numberOfColours = 5;

level10.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level10.collectItem = {
	0,20,
	1,20,
	2,20,
};

--[[
level10.ingredientSpawnDensity = 12;
level10.numIngredientsOnScreen = 1;
level10.numCherry = 3;
level10.numChesnut = 3;
]]
return level10;