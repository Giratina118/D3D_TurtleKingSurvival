#ifndef __RENDER_H__
#define __RENDER_H__

#include "_VertexData.h"

class CObject;
class CBullet;

void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* str);	// �ؽ�Ʈ �׸���

// 3d render
void Render(CObject** landformObj, CBullet* bullets[BULLET_MAX], SliderData* sliderInfo, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState); // �׸���
void SettingTmViewProjection(D3DXVECTOR3* lookAt, D3DXVECTOR3* eye, D3DXVECTOR3* up, SceneState sceneState, SliderData* sliderInfo); // ����, ���� ��ȯ
void RenderIndices(CObject* obj, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, LPDIRECT3DINDEXBUFFER9 pIB, D3DPRIMITIVETYPE primitiveType, UINT numberVertices, UINT primCount);
void RenderVertices(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primCount);
BOOL RenderCommon(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB);			// �׸��� ���� �κ�

void RenderBilboard(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 g_pTextureBilboard, LPDIRECT3DVERTEXBUFFER9 g_pVB_Bilboard, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ, int startVertex, D3DPRIMITIVETYPE primitiveType); // ������ �׸���
void SetBilboardAngle(D3DXVECTOR3* v3BilboardX, D3DXVECTOR3* v3BilboardZ, D3DXVECTOR3 v3LookAt, D3DXVECTOR3 v3Eye); // ������ ���� ����
void RenderEnemys(D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ);						// �� �׸���
void RenderBullets(CBullet** bullets, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ);	// �Ѿ� �׸���

void _SetAlphaTest();   // ���� �׽�Ʈ (�ڿ� �ִ� ���� �׸� �� ������ �������� �Ұ���,  ���� ���� or ������)
void _SetAlphaBlend();  // ���� ���� (�ڿ� �ִ� ���� �׸� �� ������ �������� ����)
void _SetLight(D3DLIGHTTYPE lightType, D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DVECTOR position, D3DVECTOR direction, FLOAT range, FLOAT falloff, FLOAT theta, FLOAT phi, DWORD lightIndex); // ���� ����
void _SetMatrial(D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DCOLORVALUE emissive, FLOAT power);	// ���� ����

void SetFrustumPlane(D3DXMATRIX tempViewTM, D3DXMATRIX tempProjectionTM);                   // ����ü ��� ����
BOOL IsSphereInFrustumPlane(const D3DXVECTOR3& center, float radius, D3DXPLANE planes[6]);  // ����ü ����

// UI (2d render)
void DrawUI(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState);			// UI �׸���
void DrawScoreScene(LPD3DXFONT font);	// Ÿ��Ʋ�� ���� â UI
void DrawTitleScene(LPD3DXFONT font);	// Ÿ��Ʋ UI
void DrawGameScene(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState);	// ���Ӿ� UI
void DrawResultScene(LPD3DXFONT font);	// ���â UI

void DrawHelpWindow(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo);	// ���� �׸���
void DrawHelpTexts(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo);							// ���� ���� �κ�
void DrawCrossCenterLine(SceneState sceneState);	// ���콺 ���ظ�� ���ڼ� �׸���
void DrawPlayerLvHpExp(LPD3DXFONT font);			// �÷��̾� ����, HP, ����ġ �׸��� (���ϴ�)
void DrawMenuUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics);		// �޴�â �׸���
void DrawLevelUpUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics);	// ������ ���ʽ� ���� ȭ��
void SetLevelUpBonusCardTexts(char lvUpCardTexts[5][32], char* cardName, char* cardEffect1, char* cardEffect2, char* cardEffect3);  // ������ ī�� ���� �κ�
void DrawSliderHorizontal(LPDIRECT3DTEXTURE9 textureEmptySlider, LPDIRECT3DTEXTURE9 textureFillSlider, LPDIRECT3DTEXTURE9 textureSliderHandle, int startVertex);	// �����̴� �׸���

#endif