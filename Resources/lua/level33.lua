local level33 = {};--{"scoreTargets":2500,8000,20000,"ingredients":2,0,0,"ingredientSpawnDensity":7,"numberOfColours":5,"randomSeed":0,"moveLimit":15,"protocolVersion":"0.1","tileMap":0,0,0,18,18,18,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,512,512,512,512,512,512,512,512,512,"portals":,"numIngredientsOnScreen":1,"gameModeName":"Drop down"}


level33.candyDropMode = 0;
level33.moveLimit = 14;
level33.CandyMapDataTable = {
	0,0,0,18,18,18,0,0,0,
	0,0,0,2,2,2,0,0,0,
	0,0,2,2,2,2,2,0,0,
	0,0,2,2,2,2,2,0,0,
	0,2,2,2,2,2,2,2,0,
	0,2,2,2,2,2,2,2,0,
	96,96,96,96,96,96,96,96,96,
	96,96,96,96,96,96,96,96,96,
	512,512,512,512,512,512,512,512,512
};

level33.portalNum=0;

level33.newportalNum=0;

level33.oneStarScore =  23000;
level33.twoStarScore =  55000;
level33.threeStarScore =  88000;

level33.numberOfColours = 5;

level33.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level33.ingredientSpawnDensity = 7;
level33.numIngredientsOnScreen = 1;
level33.numCherry = 2;
level33.numChesnut = 0;

return level33;