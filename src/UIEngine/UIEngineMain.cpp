#include "stdafx.h"

FUNC_API int ModuleMain()
{
	// IUIBase
	Common::Util::RegisterComponentString(_T("814325CB-000D-445e-9EAB-21190A5E4472"), _T("49F5DE2D-90CE-4301-9196-27BA33CC8D0D"), _T("UIEngine.dll")) ;
	// IUIElement
	Common::Util::RegisterComponentString(_T("0BC76408-37B0-45bf-80A6-E22BD66B602F"), _T("AF8CD66A-3C32-4d46-B395-5AFA2D1DAFA3"), _T("UIEngine.dll")) ;
	// IUIFrame
	Common::Util::RegisterComponentString(_T("051D90C7-E7AB-4ee1-A171-826CA957518A"), _T("7BC72638-E9EA-41ec-89E9-F4678EA5939B"), _T("UIEngine.dll")) ;
	// IUIControl
	Common::Util::RegisterComponentString(_T("F432F0A9-96F2-43fa-9EE6-8395B1D9102E"), _T("FFC6EA36-F6C6-4cdf-A24E-1AC035C66C97"), _T("UIEngine.dll")) ;
	// IUIWin
	Common::Util::RegisterComponentString(_T("C7A57F75-5780-454f-95DA-977F7C256B60"), _T("FA0ED798-DEBF-42e2-BA6A-9AB45A9F147B"), _T("UIEngine.dll")) ;

	// IUIFont
	Common::Util::RegisterComponentString(_T("2A179EB5-BEED-4582-9FA9-5CFCD150B4F3"), _T("0AD9ACD4-96AE-4960-AD07-16F7D631079A"), _T("UIEngine.dll")) ;
	// IUIQuad
	Common::Util::RegisterComponentString(_T("A0864053-25FD-4c38-AFDA-22F402CE988A"), _T("2B4C05AC-7695-475b-9DA8-30164B71ECB7"), _T("UIEngine.dll")) ;
	// IUISplit
	Common::Util::RegisterComponentString(_T("5FE55867-4383-46d8-9DB5-BEC4D6926D8D"), _T("671957AE-3CF9-4eed-AC13-FD82E83E0CE4"), _T("UIEngine.dll")) ;
	// IUIHittest
	Common::Util::RegisterComponentString(_T("3AB42272-4630-4bac-B1CD-F995FD91A50F"), _T("E093B174-92B0-4eff-BA5F-062F552778B4"), _T("UIEngine.dll")) ;

	// IUIBrush
	Common::Util::RegisterComponentString(_T("0A8F6858-743D-433B-AE72-D08ED19271A6"), _T("9C4B9085-E329-496f-9484-1A5FC221ABB1"), _T("UIEngine.dll")) ;
	// IUICanvas
	Common::Util::RegisterComponentString(_T("661BAF54-ECCC-4A6F-9D71-27E4EA61B342"), _T("73717462-7951-4d02-9EA9-322F5182D1CA"), _T("UIEngine.dll")) ;
	// IUITexture
	Common::Util::RegisterComponentString(_T("674A3F15-17D1-4d06-B96D-0F11ED0E6670"), _T("431A3385-CAAF-4354-98CC-7FE3AA4889D6"), _T("UIEngine.dll")) ;
	// IUIText
	Common::Util::RegisterComponentString(_T("01595DF1-DA93-4AE2-B8E9-728CA7C46A4C"), _T("ABE0840E-3497-4E7A-AC5F-15D53D6AFD70"), _T("UIEngine.dll")) ;
	
	// IUIRender
	Common::Util::RegisterComponentString(_T("9017C760-2EDB-42fb-AB7F-F44D10D6C605"), _T("88F1455C-4752-4ee6-83B6-66BF6F9E0F5C"), _T("UIEngine.dll")) ;
	// IUIMsgLoop
	Common::Util::RegisterServiceString(_T("DF7BBD5E-490E-4594-8329-E17A6E09C50D"), _T("70348E9C-1F85-4052-BD93-45DCEA342B3C"), _T("UIEngine.dll")) ;
	// IUIExtWnd
	Common::Util::RegisterServiceString(_T("D24D28E2-1D21-4531-B6CC-B745E72F0BB1"), _T("BFB0B72B-2498-4745-B7EB-E5F8E580CCB9"), _T("UIEngine.dll")) ;
	// IUITimer
	Common::Util::RegisterServiceString(_T("C55D0347-1253-41B3-9F4E-D496C11BF5C3"), _T("53B839C9-764B-4ec1-9580-A6168F24246C"), _T("UIEngine.dll")) ;
	// IUIWinMgr
	Common::Util::RegisterServiceString(_T("5C250BB4-957F-48dc-9052-0DEB61C3B020"), _T("43605EC1-82A4-4ffd-8DBC-0D10B182A353"), _T("UIEngine.dll")) ;
	// IUIFactory
	Common::Util::RegisterServiceString(_T("7743D14E-67B4-4114-BC58-26B2DF9644D7"), _T("66B68817-907D-43ce-9DE0-0FB566E02303"), _T("UIEngine.dll")) ;
	// IUIFactory
	Common::Util::RegisterServiceString(_T("725F55E6-8BD3-4a30-98C3-E5D210D06790"), _T("E50AE8D8-3BEB-4e6a-8E47-1DB0FE7DB9B4"), _T("UIEngine.dll")) ;
	// IUITooltips
	Common::Util::RegisterServiceString(_T("5B8597E4-9AE6-4b34-ADEC-B3EB709E4833"), _T("DAE19002-027F-4960-9FDB-B06136BC517A"), _T("UIEngine.dll")) ;

	// IUI3DTransfrom
	Common::Util::RegisterComponentString(_T("BB28ACEF-069B-42c7-8A6F-5AA19FF41204"), _T("16793B15-E911-416a-A46D-B78750F871D5"), _T("UIEngine.dll")) ;

	// IUILayoutDock
	Common::Util::RegisterComponentString(_T("B4361B60-780F-4451-8168-7066A8739EB3"), _T("032FF0EF-0A58-4ff3-916A-49CF9EC9AB67"), _T("UIEngine.dll")) ;
	// IUILayoutVertical
	Common::Util::RegisterComponentString(_T("9933F090-96AC-43bd-948D-984D1EB8A68C"), _T("51430FE6-17A7-4053-BC04-077E5BF86F52"), _T("UIEngine.dll")) ;
	// IUILayoutHorizontal
	Common::Util::RegisterComponentString(_T("FFD71F3B-DD35-47aa-90F4-581BC3761D75"), _T("62316E13-2B60-464f-9877-ED343344F7F4"), _T("UIEngine.dll")) ;
	// IUILayoutMenu
	Common::Util::RegisterComponentString(_T("04D7CB10-D3BB-4a07-9D79-BFB300EB2F1C"), _T("BB21164C-9877-4eb2-89B8-1ACE7F7A8868"), _T("UIEngine.dll")) ;

	// IUIWebkit
	Common::Util::RegisterComponentString(_T("8124371B-D0A0-43b8-86D4-09CE4F6C2ED1"), _T("9D21F203-B88A-49ec-829F-5C521537DB60"), _T("UIEngine.dll")) ;
	// IUIBackBlur
	Common::Util::RegisterComponentString(_T("83A50E93-82C1-43c6-8E3F-2E24F2DA7D60"), _T("A2F55359-A080-435b-8A8C-649D7B75C8E8"), _T("UIEngine.dll")) ;
	// IUIStatic
	Common::Util::RegisterComponentString(_T("C0CCC861-A94C-498f-95C4-4ECA8C16F2EF"), _T("6A536450-119D-4ED2-9697-AEEC2D3D4EEB"), _T("UIEngine.dll")) ;
	// IUIButton
	Common::Util::RegisterComponentString(_T("42FB084C-7535-43B5-87DE-E6533C323A0B"), _T("EDF3CBEE-93A6-44f1-AF06-5B8E882C3BD9"), _T("UIEngine.dll")) ;
	// IUIAnimate
	Common::Util::RegisterComponentString(_T("22244093-8C80-45c3-B2C0-FF0EA3DD5803"), _T("33B87A71-8EDD-45cc-9622-88CCA6D72E0B"), _T("UIEngine.dll")) ;
	// IUICaret
	Common::Util::RegisterComponentString(_T("82B0BE5C-1AA9-4ac1-8085-8B89AFD2439D"), _T("F22D285D-6636-466c-873B-DE8B743CD351"), _T("UIEngine.dll")) ;
	// IUITextField
	Common::Util::RegisterComponentString(_T("DDB55AC5-C978-466c-B405-D242DCAC7B7F"), _T("73DD2117-8AC6-4935-AE8A-F15DF376589D"), _T("UIEngine.dll")) ;
	// IUIScroll
	Common::Util::RegisterComponentString(_T("E386D85B-BF83-4bdc-9CFA-0916C4002F29"), _T("4CD999BB-1384-460f-8252-38C3B82A8CBA"), _T("UIEngine.dll")) ;
	
	return 0 ;
}


FUNC_API int ModuleInit()
{
	return 0 ;
}