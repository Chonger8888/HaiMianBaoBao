local level58= {};--{"numberOfColours":4,"pepperCandyExplosionTurns":0,"_itemsToOrder":{"quantity":13,"item":2},{"quantity":13,"item":4},{"quantity":13,"item":6},"tileMap":2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,130,2,130,2,130,2,130,2,2,2,2,2,2,2,2,2,2,"licoriceSpawn":0,"gameModeName":"Order","licoriceMax":0,"scoreTargets":10000,15000,25000,"ingredientSpawnDensity":15,"numIngredientsOnScreen":1,"protocolVersion":"0.1","randomSeed":0,"pepperCandyMax":0,"portals":,"moveLimit":9,"pepperCandySpawn":0,"ingredients":}

level58.candyDropMode = 0;  -- 是不是掉落模式，0表示不是，1表示是
level58.moveLimit = 10;  --  步数
level58.CandyMapDataTable = {
	0,0,0,0,0,0,0,0,0,
	0,22,22,22,22,22,22,22,22,
	0,6,6,6,6,6,6,6,6,
	0,6,6,6,6,6,6,6,6,
	0,6,6,6,6,6,6,6,6,
	0,6,0,6,0,6,0,6,0,
	0,2,0,6,0,6,0,6,0,
	0,2,0,2,0,6,0,6,0,
	0,2,0,2,0,2,0,6,0,
};

level58.portalNum=0;

level58.newportalNum=0;

level58.oneStarScore =  40000;
level58.twoStarScore =  100000;
level58.threeStarScore =  140000;

level58.numberOfColours =5;

level58.numjelly =  42;

level58.gameMode =  1;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

--[[level58.collectItem = {
	1,50,
};]]

--[[
level58.ingredientSpawnDensity = 12;
level58.numIngredientsOnScreen = 1;
level58.numCherry = 3;
level58.numChesnut = 3;
]]
return level58;