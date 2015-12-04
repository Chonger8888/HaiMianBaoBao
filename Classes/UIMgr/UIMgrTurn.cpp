// #include "cocos2d.h"
// #include "UIMgrTurn.h"
// 
// BaseUILayer::BaseUILayer()
// {
// 	m_LayerID = ID_Invalid;
// 	m_removeRes = false;
// 	UIMgrTurn::Get()->pushLayer(this);
// }
// 
// 
// BaseUILayer::~BaseUILayer()
// {
//     final();
// }
// 
// bool BaseUILayer::init()
// {
// 	if(!CCLayer::init())
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }
// 
// void BaseUILayer::final()
// {
// 
// }
// 
// void BaseUILayer::ShowLayer( BOOL bUpdate )
// {
// 
// }
// 
// void BaseUILayer::HideLayer()
// {
// 	this->setVisible(false);
// }
// 
// 
// /////////////////////////////////////////////////////////////////////////
// 
// UIMgrTurn::UIMgrTurn()
// {
// 	nowOpenMode = OpenModel_None;
// }
// 
// UIMgrTurn::~UIMgrTurn()
// {
//     std::vector<BaseUILayer*> vecLayer = m_MainLayerVec;
//     for (std::vector<BaseUILayer*>::iterator iter = vecLayer.begin();iter != vecLayer.end();++iter)
//     {
//         BaseUILayer* layer = (*iter);
//         CC_SAFE_DELETE(layer);
//     }
//     vecLayer.clear();
//     m_MainLayerVec.clear();
// }
// 
// BaseUILayer* UIMgrTurn::GetLayerByID(LayerID pID)
// {
// 	for (std::vector<BaseUILayer*>::iterator iter = m_MainLayerVec.begin();iter != m_MainLayerVec.end();++iter)
// 	{
// 		BaseUILayer* layer = (*iter);
// 		if (layer->getLayerID() == pID)
// 		{
// 			return layer;
// 		}
// 	}
// 	return NULL;
// }
// 
// void UIMgrTurn::removeLayer(LayerID pID)
// {
// 	for (std::vector<BaseUILayer*>::iterator iter = m_MainLayerVec.begin();iter != m_MainLayerVec.end();++iter)
// 	{
// 		BaseUILayer* layer = (*iter);
// 		if (layer->getLayerID() == pID)
// 		{
// 			m_MainLayerVec.erase(iter);
// 			break;
// 		}
// 	}
// }
// 
// void UIMgrTurn::pushLayer(BaseUILayer* pLayer)
// {
// 	for (std::vector<BaseUILayer*>::iterator iter = m_MainLayerVec.begin();iter != m_MainLayerVec.end();++iter)
// 	{
// 		BaseUILayer* layer = (*iter);
// 		if (layer == pLayer)
// 		{
// 			return ;
// 		}
// 	}
// 	m_MainLayerVec.push_back(pLayer);
// }
// 
// void UIMgrTurn::ClearReturnStack()
// {
// 	while( !m_ModelStack.empty() )
// 		m_ModelStack.pop();
// }
// 
// BOOL UIMgrTurn::returnLastOpen( BOOL bUpdate )
// {
// 	if(m_MainLayerVec.empty())
// 	{
// 		return false;
// 	}
// 	if( m_ModelStack.empty() )
// 	{
// 		return false;
// 	}
// 	
// 	OpenModel model = m_ModelStack.top();
// 	m_ModelStack.pop();
// 
// 	openModel(model, bUpdate);
// 	if( !m_ModelStack.empty() )
// 	{
// 		m_ModelStack.pop();
// 	}
// 	return true;
// }
// 
// OpenModel UIMgrTurn::getLastOpen()
// {
// 	OpenModel model = m_ModelStack.top();
// 	return model;
// }
// 
// void UIMgrTurn::openModel( OpenModel mode, BOOL bUpdate )
// {
// 	if( nowOpenMode == mode )
// 		return;
// 
// 	m_ModelStack.push(nowOpenMode);
// 	nowOpenMode = mode;
// 
// 	std::vector<LayerID> vecLayers;
// // 	switch(mode)
// // 	{
// // 	}
// 
// 	for (unsigned i=0; i<vecLayers.size(); i++)
// 	{
// 		LayerID layerID = vecLayers[i];
// 		BaseUILayer* pLayer = GetLayerByID(layerID);
// 		CCAssert( pLayer != NULL, "请检查相关类layerID的初始化" );
// 		pLayer->init();
// 		pLayer->ShowLayer( bUpdate );
// 	}
// }
// 
// void UIMgrTurn::UpdateLayerData()
// {
// 	for (std::vector<BaseUILayer*>::iterator iter = m_MainLayerVec.begin(); iter != m_MainLayerVec.end(); ++iter)
// 	{
// 		BaseUILayer* layer = (*iter);
// 		if( layer->isVisible() )
// 		{
// 			layer->UpdateUI();
// 		}
// 	}
// }
