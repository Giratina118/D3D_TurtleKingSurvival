#ifndef __RENDER_H__
#define __RENDER_H__

#include "_VertexData.h"

class CObject;
class CBullet;

void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* str);	// 텍스트 그리기

// 3d render
void Render(CObject** landformObj, CBullet* bullets[BULLET_MAX], SliderData* sliderInfo, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState); // 그리기
void SettingTmViewProjection(D3DXVECTOR3* lookAt, D3DXVECTOR3* eye, D3DXVECTOR3* up, SceneState sceneState, SliderData* sliderInfo); // 시점, 투영 변환
void RenderIndices(CObject* obj, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, LPDIRECT3DINDEXBUFFER9 pIB, D3DPRIMITIVETYPE primitiveType, UINT numberVertices, UINT primCount);
void RenderVertices(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primCount);
BOOL RenderCommon(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB);			// 그리기 공통 부분

void RenderBilboard(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 g_pTextureBilboard, LPDIRECT3DVERTEXBUFFER9 g_pVB_Bilboard, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ, int startVertex, D3DPRIMITIVETYPE primitiveType); // 빌보드 그리기
void SetBilboardAngle(D3DXVECTOR3* v3BilboardX, D3DXVECTOR3* v3BilboardZ, D3DXVECTOR3 v3LookAt, D3DXVECTOR3 v3Eye); // 빌보드 각도 설정
void RenderEnemys(D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ);						// 적 그리기
void RenderBullets(CBullet** bullets, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ);	// 총알 그리기

void _SetAlphaTest();   // 알파 테스트 (뒤에 있는 것을 그릴 수 있지만 반투명이 불가능,  오직 투명 or 불투명)
void _SetAlphaBlend();  // 알파 블렌드 (뒤에 있는 것을 그릴 수 없지만 반투명이 가능)
void _SetLight(D3DLIGHTTYPE lightType, D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DVECTOR position, D3DVECTOR direction, FLOAT range, FLOAT falloff, FLOAT theta, FLOAT phi, DWORD lightIndex); // 조명 설정
void _SetMatrial(D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DCOLORVALUE emissive, FLOAT power);	// 재질 설정

void SetFrustumPlane(D3DXMATRIX tempViewTM, D3DXMATRIX tempProjectionTM);                   // 절두체 평면 설정
BOOL IsSphereInFrustumPlane(const D3DXVECTOR3& center, float radius, D3DXPLANE planes[6]);  // 절두체 판정

// UI (2d render)
void DrawUI(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState);			// UI 그리기
void DrawScoreScene(LPD3DXFONT font);	// 타이틀의 점수 창 UI
void DrawTitleScene(LPD3DXFONT font);	// 타이틀 UI
void DrawGameScene(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState);	// 게임씬 UI
void DrawResultScene(LPD3DXFONT font);	// 결과창 UI

void DrawHelpWindow(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo);	// 도움말 그리기
void DrawHelpTexts(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo);							// 도움말 글자 부분
void DrawCrossCenterLine(SceneState sceneState);	// 마우스 조준모드 십자선 그리기
void DrawPlayerLvHpExp(LPD3DXFONT font);			// 플레이어 레벨, HP, 경험치 그리기 (좌하단)
void DrawMenuUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics);		// 메뉴창 그리기
void DrawLevelUpUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics);	// 레벨업 보너스 선택 화면
void SetLevelUpBonusCardTexts(char lvUpCardTexts[5][32], char* cardName, char* cardEffect1, char* cardEffect2, char* cardEffect3);  // 레벨업 카드 글자 부분
void DrawSliderHorizontal(LPDIRECT3DTEXTURE9 textureEmptySlider, LPDIRECT3DTEXTURE9 textureFillSlider, LPDIRECT3DTEXTURE9 textureSliderHandle, int startVertex);	// 슬라이더 그리기

#endif