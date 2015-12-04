local level59= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level59.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level59.moveLimit = 15;  --  步数
level59.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	0,0,18,18,18,18,18,18,18,
	0,0,130,2,2,2,2,2,130,
	0,0,2,130,2,2,2,130,2,
	0,0,2,2,3202,2,3202,2,2,
	0,0,2,3074,0,130,0,3074,2,
	0,0,2,0,5130,10,5130,0,2,
	0,0,0,5130,10,10,10,5130,0,
};

level59.portalNum=0;

level59.newportalNum=0;

level59.oneStarScore =  16000;
level59.twoStarScore =  80000;
level59.threeStarScore =  105000;

level59.numberOfColours = 5;

level59.numjelly =  8;

level59.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[level59.collectItem = {
	1,50,
};]]

--[[
level59.ingredientSpawnDensity = 12;
level59.numIngredientsOnScreen = 1;
level59.numCherry = 3;
level59.numChesnut = 3;
]]
return level59;