local level64 = {};--{"numIngredientsOnScreen":1,"portals":0,2,0,4,1,3,1,5,2,4,2,6,3,5,3,7,4,6,4,8,5,5,5,7,6,4,6,6,7,3,7,5,8,2,8,4,"gameModeName":"Drop down","ingredients":1,2,"scoreTargets":78000,93000,120000,"ingredientSpawnDensity":15,"moveLimit":50,"numberOfColours":5,"randomSeed":0,"protocolVersion":"0.1","tileMap":18,18,18,18,18,18,18,18,18,2,2,2,2,2,2,2,2,2,3202,2,2,2,2,2,2,2,3202,0,3202,2,2,2,2,2,3202,0,5122,0,3202,2,2,2,3202,0,5122,2,5122,0,3202,2,3202,0,5122,2,2,2,5122,0,3202,0,5122,2,2,2,2,2,5122,0,5122,2,2,2,514,514,514,514,5634,514,514,514,514}


level64.candyDropMode = 0;
level64.moveLimit = 50;
level64.CandyMapDataTable = {
18,18,18,18,18,18,18,18,18,
2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,
2,2,3202,2,2,2,3202,2,2,
2,3202,0,3202,2,3202,0,3202,2,
3202,0,5122,0,3202,0,5122,0,3202,
0,5122,2,5122,0,5122,2,5122,0,
5122,2,2,2,5122,2,2,2,5122,
514,514,514,514,5634,514,514,514,514

};

level64.portalNum=0;

level64.newportalNum=0;

level64.oneStarScore =  100000;
level64.twoStarScore =  180000;
level64.threeStarScore =  210000;

level64.numberOfColours = 5;

level64.gameMode =  2;   --0 ：普通模式  1：消除果冻模式 2：运送果子 3：计时模式 4：收集特定糖果

level64.ingredientSpawnDensity = 15;
level64.numIngredientsOnScreen = 1;
level64.numCherry = 1;
level64.numChesnut = 2;
return level64;