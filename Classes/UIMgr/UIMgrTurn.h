// #pragma  once
// 
// #include "Singleton_t.h"
// #include <stack>
// #include <vector>
// 
// enum OpenModel
// {
// 	OpenModel_None,
// 	OpenModel_Count,
// };
// enum LayerID
// {
// 	ID_Invalid,
// 	ID_Count,
// };
// 
// class BaseUILayer : public cocos2d::CCLayer
// {
// public:
// 	BaseUILayer();
// 	virtual ~BaseUILayer();
// 
// public:
// 	virtual bool init();
// 	virtual void final();
// 
// 	virtual void UpdateUI(){}
// 	virtual void ShowLayer( BOOL bUpdate = true );
// 	virtual void HideLayer();
// 
// 	LayerID getLayerID()	{	return m_LayerID;			}
// 	BOOL	IsRemoveRes()	{	return m_removeRes;			}
// 
// protected:
// 	LayerID				m_LayerID;
// 	BOOL				m_removeRes;	// 切换到另一个界面时，释放当前界面否
// };
// 
// typedef std::vector<BaseUILayer*> MainLayerVec;
// 
// 
// class UIMgrTurn : public TSingleton<UIMgrTurn>
// {
// public:
// 	UIMgrTurn();
// 	virtual~UIMgrTurn();
// 
// 	void openModel(OpenModel mode, BOOL bUpdate = true);
// 	BOOL returnLastOpen( BOOL bUpdate = true );
// 	void ClearReturnStack();
// 	OpenModel getLastOpen();
// 
// 	void pushLayer(BaseUILayer* pLayer);
// 	void removeLayer(LayerID pID);
// 	BaseUILayer* GetLayerByID(LayerID pID);
// 	OpenModel getNowOpenMode(){return nowOpenMode;}
// 
// 	void UpdateLayerData();
// 
// private:
// 	OpenModel				nowOpenMode;
// 	std::stack<OpenModel>	m_ModelStack;
// 	MainLayerVec			m_MainLayerVec;
// };
