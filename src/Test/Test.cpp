
#include "stdafx.h"
#include "resource.h"

#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"

#include "Include/Common/ICVariant.h"
#include "Include/Common/ISPlugin.h"
#include "Include/Common/ISModule.h"
#include "Include/BaseMisc/ICTest.h"
#include "Include/UIEngine/IUIMsgLoop.h"
#include "Include/UIEngine/IUITimer.h"
#include "Include/UIEngine/IUIBrush.h"
#include "Include/UIEngine/IUIWin.h"
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUITexture.h"
#include "Include/UIEngine/IUIWebkit.h"
#include "Include/UIEngine/IUILayoutDefault.h"
#include "Include/UIEngine/IUIBackBlur.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUIStatic.h"
#include "Include/UIEngine/IUIAnimate.h"
#include "Include/UIEngine/IUITextField.h"
#include "Include/UIEngine/IUIButton.h"
#include "Include/UIEngine/IUIFactory.h"
#include "Include/UIEngine/IUITooltips.h"

[ module(exe, uuid = "{91C6F9F7-EE96-4F7A-8F4C-13D8EF179C40}", 
		 name = "Test", 
		 helpstring = "Test 1.0 类型库",
		 resource_name = "IDR_TEST") ]
class CTestModule
{

 int i ;
public:
	CComSinkTimerCallbackPtr<CTestModule> _timer_callback ;
	CComSinkUIEventCallbackPtr<CTestModule> _event_callback ;

	CComPtr<IUITextField> pEdit ;
	CComPtr<IUIWebkit> pWebkit ;

	HRESULT OnEvent(IUIFrame* pFrame, INT nEventId, tEventArg* pArgs)
	{
		if (pEdit && pWebkit)
		{
			CComBSTR str ;
			pEdit->GetText(&str) ;
			pWebkit->SetUrl(str) ;
		}
		return S_OK ;
	}

	CTestModule():_timer_callback(this),_event_callback(this)
	{

		HINSTANCE hUser32 = LoadLibrary( L"user32.dll" );
		if( hUser32 )
		{
			typedef BOOL ( WINAPI* LPSetProcessDPIAware )( void );
			LPSetProcessDPIAware pSetProcessDPIAware = ( LPSetProcessDPIAware )GetProcAddress( hUser32,
				"SetProcessDPIAware" );
			if( pSetProcessDPIAware )
			{
				pSetProcessDPIAware();
			}
			FreeLibrary( hUser32 );
		}

		Common::Util::Init() ;

		CWeakPtr<ISModule> wpModule ;
		Common::Util::GetService(&wpModule) ;
		wpModule->LoadModule(_T("BaseMisc")) ;
		wpModule->LoadModule(_T("UIEngine")) ;

/*

*/
		CWeakPtr<IUIFactory> pFactory ;
		Common::Util::GetService(&pFactory) ;
		if (pFactory)
		{
			pFactory->LoadTagConfigFromFile(_T("C:/res/tag.xml")) ;
		}


		CComPtr<IUIBrush> pBrush ;
		Common::Util::CreateObject(&pBrush) ;
		pBrush->SetColor(RGB(255, 255, 255)) ;
		pBrush->SetBrushType(BRUSH::RECT_FILL) ;

				CComPtr<IUITexture> pTexture ;
		Common::Util::CreateObject(&pTexture) ;
		pTexture->LoadFromFile(_T("c:/3.png")) ;
		pTexture->SetDrawGrid(CRect(30,30,30,30)) ;
		pTexture->SetDrawType(TEXTURE::DRAW::GRID) ;

		CWeakPtr<IUITooltips> wpTooltips ;
		Common::Util::GetService(&wpTooltips) ;
		wpTooltips->SetTooltipsDraw(pTexture) ;
		wpTooltips->SetTooltipsPadding(CRect(20,20,20,20)) ;

		//CComPtr<IUIBrush> pBrush ;
		//Common::Util::CreateObject(&pBrush) ;
		//pBrush->SetColor(RGB(0, 0, 133)) ;
		//pBrush->SetBrushType(BRUSH::RECT_FILL) ;

		//CComPtr<IUIBrush> pBrush2 ;
		//Common::Util::CreateObject(&pBrush2) ;
		//pBrush2->SetColor(RGB(255, 0, 0)) ;

		//CComPtr<IUIWin> pWin ;
		//Common::Util::CreateObject(&pWin) ;
		//DEBUG_ASSERT(pWin) ;
		//CComPtr<IUITexture> pTexture ;
		//Common::Util::CreateObject(&pTexture) ;
		//pTexture->LoadFromFile(_T("c:/3.png")) ;
		//pTexture->SetDrawGrid(CRect(30,30,30,30)) ;
		//pTexture->SetDrawType(TEXTURE::DRAW::GRID) ;
		//pWin->SetBkgDraw(pTexture) ;

		////pWin->SetToolWindow(TRUE) ;
		////pWin->SetTopMost(TRUE) ;
		//pWin->SetLayerWin(TRUE) ;
		//pWin->CreateWin(NULL, NULL) ;
		//pWin->ShowWin(SW_SHOW) ;
		//pWin->SetWinSize(CSize(800, 641)) ;
		//pWin->SetTitle(_T("guodong")) ;
		//pWin->SetDoubleBuffer(TRUE) ;
		//pWin->SetPadding(CRect(20,80,20,35)) ;
		//pWin->SetWindowBorder(CRect(20,20,20,20)) ;
		////pWin->SetAutoWidth(TRUE) ;
		////pWin->SetAutoHeight(TRUE) ;
		//CComPtr<IUILayoutVertical> pLayout ;
		//Common::Util::CreateObject(&pLayout) ;
		//pLayout->SetFillItemIndex(-1) ;
		//pWin->SetLayouter(pLayout) ;


		////
		//CComPtr<IUIFrame> pFrameUrl ;
		//Common::Util::CreateObject(&pFrameUrl) ;
		//pWin->AddChildBack(pFrameUrl) ;
		//pFrameUrl->SetAutoHeight(TRUE) ;
		//pFrameUrl->SetWidthAsParent(TRUE) ;
		//pFrameUrl->SetSize(CSize(200, 100)) ;
		//pFrameUrl->SetMargin(CRect(0,0,0,10)) ;
		////pFrameUrl->SetBkgDraw(pBrush) ;
		//{
		//	CComPtr<IUILayoutHorizontal> pLayout ;
		//	Common::Util::CreateObject(&pLayout) ;
		//	pLayout->SetFillItemIndex(1) ;
		//	pFrameUrl->SetLayouter(pLayout) ;
		//}

		//CComPtr<IUITextField> pEdit ;
		//Common::Util::CreateObject(&pEdit) ;
		//pEdit->SetSize(CSize(0, 200)) ;
		////pEdit->SetHeightAsParent(TRUE) ;
		//pEdit->SetBkgDraw(pBrush2) ;
		//pEdit->SetPadding(CRect(10,10,10,10)) ;
		////pEdit->SetSingleLine(TRUE) ;
		//pEdit->SetLineHeight(35) ;
		//pEdit->SetPassWord(TRUE) ;
		//pFrameUrl->AddChildBack(pEdit) ;

		//this->pEdit = pEdit ;

		//CComPtr<IUIButton> pButton ;
		//Common::Util::CreateObject(&pButton) ;
		//pButton->SetAutoSize(TRUE) ;
		//pButton->SetPadding(CRect(5, 5, 5, 5)) ;
		//pButton->SetText(_T("确 认")) ;

		//_event_callback->Hook_OnEvent(&CTestModule::OnEvent) ;
		//pButton->AddEventListener(UI::EVENT::BUTTON_CLICK, _event_callback) ;

		////pButton->SetEnableDrag(TRUE) ;
		//{
		//	CComPtr<IUITexture> p1 ;
		//	Common::Util::CreateObject(&p1) ;
		//	p1->LoadFromFile(_T("C:/png/button/button_normal.png")) ;
		//	p1->SetDrawGrid(CRect(20,10,20,10)) ;
		//	p1->SetDrawType(TEXTURE::DRAW::GRID) ;
		//	pButton->SetNormalBkgDraw(p1) ;
		//}

		//{
		//	CComPtr<IUITexture> p1 ;
		//	Common::Util::CreateObject(&p1) ;
		//	p1->LoadFromFile(_T("C:/png/button/button_hover.png")) ;
		//	p1->SetDrawGrid(CRect(20,10,20,10)) ;
		//	p1->SetDrawType(TEXTURE::DRAW::GRID) ;
		//	pButton->SetHighlightBkgDraw(p1) ;
		//}

		//{
		//	CComPtr<IUITexture> p1 ;
		//	Common::Util::CreateObject(&p1) ;
		//	p1->LoadFromFile(_T("C:/png/button/button_press.png")) ;
		//	p1->SetDrawGrid(CRect(20,10,20,10)) ;
		//	p1->SetDrawType(TEXTURE::DRAW::GRID) ;
		//	pButton->SetPushedBkgDraw(p1) ;
		//}
		//pFrameUrl->AddChildBack(pButton) ;

		//CComPtr<IUIWebkit> pWeb ;
		//Common::Util::CreateObject(&pWeb) ;
		//pWeb->SetSize(CSize(200, 400)) ;
		//pWeb->SetWidthAsParent(TRUE) ;
		//pWeb->LoadUrl(_T("http://www.baidu.com")) ;
		//pWin->AddChildBack(pWeb) ;

		//this->pWebkit = pWeb ;

		////CComPtr<IUIStatic> pStatic ;
		////Common::Util::CreateObject(&pStatic) ;
		////pStatic->SetWidthAsParent(TRUE) ;
		////pStatic->SetSize(CSize(400, 400)) ;
		////pStatic->SetAutoHeight(TRUE) ;
		////pStatic->SetTextColor(RGB(255, 255, 255)) ;
		////CString s = _T("双色球属于双区投注的乐透型彩号码区的33") ;
		////for (int i = 0 ; i < 1 ; ++i)
		////{
		////	s = s + _T("爱上大声地爱的阿斯达阿斯达啊实打实") ;	
		////}
		////pStatic->SetText(CComBSTR(s)) ;
		////pStatic->SetMutiLine(TRUE) ;
		//////pWin->AddChildBack(pStatic) ;

		//

		//
		//

		//


		///*
		//for (int j = 0; j < 1 ; ++j)
		//{
		//	CComPtr<IUIFrame> pFrame ;
		//	Common::Util::CreateObject(&pFrame) ;
		//	pFrame->SetAutoSize(TRUE) ;
		//	
		//	CComPtr<IUILayoutHorizontal> pLayout ;
		//	Common::Util::CreateObject(&pLayout) ;
		//	pFrame->SetLayouter(pLayout) ;

		//	for(int i = 0 ; i < 5 ; ++i)
		//	{
		//		CComPtr<IUIAnimate> pAnimate ;
		//		Common::Util::CreateObject(&pAnimate) ;
		//		pAnimate->SetSize(CSize(38, 42)) ;

		//		for (int i = 1; i <= 6; i++)
		//		{
		//			CString str ;
		//			str.Format(_T("C:/animation/%d.png"),i) ; ;
		//			CComPtr<IUITexture> pTexture ;
		//			Common::Util::CreateObject(&pTexture) ;
		//			pTexture->LoadFromFile(CComBSTR(str)) ;
		//			pTexture->SetDrawType(TEXTURE::DRAW::HOLE) ;
		//			pAnimate->AddFrame(pTexture) ;
		//		}
		//		pFrame->AddChildBack(pAnimate) ;
		//	}

		//	pWin->AddChildBack(pFrame) ;
		//}
		//*/
		CComPtr<IUIElement> pElement ;
		pFactory->CreateFromFile(_T("C://res/ui.xml"), _T("Main"), &pElement) ;
		CComQIPtr<IUIWin> pWin = pElement ;
		if (pWin)
		{
			pWin->CreateWin(NULL, NULL) ;
			pWin->ShowWin(SW_SHOW) ;
		}

		CWeakPtr<IUIMsgLoop> wpLoop ;
		Common::Util::GetService(&wpLoop) ;
		wpLoop->StartLoop() ;
	}

};
		 
