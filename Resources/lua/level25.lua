local level25= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level25.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level25.moveLimit = 20;  --  步数
level25.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,18,18,18,18,18,18,18,18,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,130,2,130,2,130,2,130,2,
	0,130,2,130,2,130,2,130,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
	0,2,2,2,2,2,2,2,2,
};

level25.portalNum=0;

level25.newportalNum=0;

level25.oneStarScore =  6000;
level25.twoStarScore =  18000;
level25.threeStarScore =  30000;

level25.numberOfColours = 6;

level25.gameMode =  4;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level25.collectItem = {
	1,25,
};

--[[
level25.ingredientSpawnDensity = 12;
level25.numIngredientsOnScreen = 1;
level25.numCherry = 3;
level25.numChesnut = 3;
]]
return level25;