#pragma once

#ifdef IMAGE3D_EXPORTS
#define IMAGE3D_API __declspec(dllexport)
#else
#ifdef USE3DIMAGE_DLL
#define IMAGE3D_API __declspec(dllimport)
#else
#define IMAGE3D_API 
#endif
#endif

namespace IMAGE3D
{
    struct PARAM3DTRANSFORM
    {
        int     nRotateX;
        int     nRotateY;
        int     nRotateZ;
        int     nOffsetZ;
    };

    struct Quad;
    class IMAGE3D_API C3DTransform
    {
    public:
        C3DTransform()
        {
            m_pSrcBits = 0;
            Initialize();
        }
        virtual ~C3DTransform();

        void  Render(const PARAM3DTRANSFORM & param3d) ;
        BOOL SetImage(LPBYTE pSour,LPBYTE pDest,int nWid,int nHei,int nBitsPixel) ;

    protected:
        void  Initialize();
        void  GetQuadByAnimateValue(int nDegreeX, int nDegreeY, int nDegreeZ, int nZOffset, Quad* pOut) ;
        DWORD ColorAlphaBlend(DWORD dwDest, DWORD dwSrc) ;

    protected:
        int     m_nSrcWndWidth,m_nSrcWndHeight ;
        int     m_nBitsPixel ;
        int     m_nSrcPitch ;
        LPBYTE  m_pSrcBits ;
        LPBYTE  m_pDstBits ;
    } ;
}
