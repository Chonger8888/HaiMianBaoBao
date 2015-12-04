#ifndef CANDY_INGREDIENTS__H
#define CANDY_INGREDIENTS__H

#include "cocos2d.h"
#include "CandyCommon.h"

USING_NS_CC;

class CandyCell;


typedef enum
{
	CANDY_INGREDIENT_CHERRY,
	CANDY_INGREDIENT_CHESNUT,
	CANDY_INGREDIENT_NUM,
}CandyIngredientType;


class CandyIngredients
{
	public:
		CandyIngredients();
		~CandyIngredients();


	public:
		CandyCell* createIngredients(CandyIndex index);
		void createIngredientsWithMapData(void);
		void createExitWithMapData(void);
		
	public:
		void updateIngredients(void);
		bool isNeedToCreateNewIngredient(void);
		
	private:
		int getRandomIndexFlag(int *array, int arrayNum);
		CandyColor getOneRemainIngredient(void);

	public:
		int numInMapCherry;
		int numInMapChesnut;
		int numDropDoneCherry;
		int numDropDoneChesnut;
		int moveCountFlag;
		
	public:
		static int numjelly;
		static int ingredientSpawnDensity;
		static int numIngredientsOnScreen;
		static int numCherry;
		static int numChesnut;
};

#endif
