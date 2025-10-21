#include "_Render.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "_SaveLoadData.h"
#include <iostream>

extern LPDIRECT3DDEVICE9        g_pd3dDevice;                   // 렌더링에 사용될 D3D 디바이스
extern LPDIRECT3DVERTEXBUFFER9  g_pVB_Array[VB_MAX];            // 정점
extern LPDIRECT3DINDEXBUFFER9   g_pIB_Array[IB_MAX];            // 인덱스
extern LPDIRECT3DTEXTURE9       g_pTEXTURE_Array[TEXTURE_MAX];  // 텍스처
extern CPlayer  playerObj;                  // 플레이어 오브젝트
extern CEnemy*  enemyObj[ENEMY_MAX];        // 적 오브젝트

extern Timer    timer;                      // 타이머
extern int      nowGameData[NOWGAME_MAX];   // 현재 게임 정보
extern SaveData saveData[10];               // 저장 정보

D3DXPLANE frustumPlane[6];                  // 절두체 컬링 평면
D3DXCOLOR textColor = { 0.0f, 0.0f, 0.0f, 1.0f };   // 글자 색
extern bool isBtnOnMouse[BUTTON_MAX];

// 문자 만들고 출력
template <typename T, typename... Types>
void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* text, T arg, Types... args) {
    char str[64] = "";
    sprintf_s(str, text, arg, args...);
    _drawText(font, center, xLeft, yTop, xRight, yBottom, str);
}

// 텍스트 그리기
void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* str)
{
    DWORD DT;
    RECT strRect;
    if (center) DT = DT_NOCLIP | DT_CENTER | DT_VCENTER;
    else        DT = DT_NOCLIP;

    SetRect(&strRect, xLeft, yTop, xRight, yBottom);
    font->DrawText(NULL, str, -1, &strRect, DT, textColor);
}


// 화면 그리기
void Render(CObject** landformObj, CBullet* bullets[BULLET_MAX], SliderData* sliderInfo, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    if (NULL == g_pd3dDevice)   return;

    // 화면 지우기 (배경색)
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(180, 200, 255), 1.0f, 0);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    g_pd3dDevice->SetFVF(CUSTOMVERTEX::FVF);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))  // 렌더링 시작
    {
        D3DXVECTOR3 v3LookAt, v3Eye, v3Up;
        SettingTmViewProjection(&v3LookAt, &v3Eye, &v3Up, sceneState, sliderInfo);  // 시점, 투영 변환

        _SetAlphaTest();    // 알파 테스트 (어떠한 상황에도 뒤에 있는 것을 그릴 수 있지만 반투명이 불가능,  오직 투명 or 불투명)

        // 조명 설정
        if (sceneState.clickKey[KEY_POINTLIGHT])    // 랜턴
            _SetLight(D3DLIGHT_POINT, { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.1f, 0.1f, 0.1f, 0.5f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { playerObj.GetMatrix()->_41, playerObj.GetMatrix()->_42, playerObj.GetMatrix()->_43 }, { 0, 0, 0 }, 2.5f, 0.0f, 0.0f, 0.0f, 0);
        else    g_pd3dDevice->LightEnable(0, FALSE);

        if (sceneState.clickKey[KEY_SPOTLIGHT])     // 손전등
           _SetLight(D3DLIGHT_SPOT, { 0.6f, 0.6f, 0.6f, 1.0f }, { 0.2f, 0.2f, 0.2f, 0.5f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { playerObj.GetMatrix()->_41, playerObj.GetMatrix()->_42 - 1, playerObj.GetMatrix()->_43 }, { playerObj.GetMatrix()->_31, playerObj.GetMatrix()->_32, playerObj.GetMatrix()->_33 }, 20.0f, 1.0f, 0.2f, 0.7f, 1);
        else    g_pd3dDevice->LightEnable(1, FALSE);

        // 태양
        FLOAT sunDirY = dateInfo.sunDirection.y;
        D3DCOLORVALUE sunDiffuse = { 0.8f * -sunDirY, 0.8f * -sunDirY, 0.7f * -sunDirY, 1.0f };
        D3DCOLORVALUE sunAmbient = { 0.2f * -sunDirY, 0.2f * -sunDirY, 0.2f * -sunDirY, 1.0f };
        if (sceneState.clickKey[KEY_DIRECTIONALLIGHT])
            _SetLight(D3DLIGHT_DIRECTIONAL, sunDiffuse, sunAmbient, { 0.5f, 0.5f, 0.5f, 1.0f }, {0, 0, 0}, dateInfo.sunDirection, 0.0f, 0.0f, 0.0f, 0.0f, 2);
        else    g_pd3dDevice->LightEnable(2, FALSE);

        // 달
        _SetLight(D3DLIGHT_DIRECTIONAL, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.2f, 0.2f, 0.2f, 0.5f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0.0f, 1.0f, 0.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 3);
        
        
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);     // 스카이박스 그리기
        _SetMatrial({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.2f, 0.2f, 0.2f, 1.0f }, 0.01f); // 재질 설정
        
        D3DXMATRIX iMatrix = {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  v3Eye.x, v3Eye.y, v3Eye.z, 1};
        for (int skyBoxCount = 0; skyBoxCount < 6; skyBoxCount++)
            RenderVertices(&iMatrix, 50, g_pTEXTURE_Array[skyBoxCount + TEXTURE_SKYBOX_RIGHT], g_pVB_Array[VB_SKYBOX], D3DPT_TRIANGLEFAN, 4 * skyBoxCount, 2);
        

        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        _SetMatrial({ 0.8f, 0.6f, 0.4f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, 0.01f); // 재질 설정

        for (int groundCount = 0; groundCount < GROUND_X * GROUND_Z; groundCount++)     // 바닥 그리기
            RenderVertices(landformObj[OBJECT_LANDFORM_GROUND][groundCount].GetMatrix(), GROUND_RADIUS * 1.4f, g_pTEXTURE_Array[TEXTURE_GRASS], g_pVB_Array[VB_GRASS], D3DPT_TRIANGLEFAN, 0, 2);

        for (int wallCount = 0; wallCount < WALL_COUNT; wallCount++)                    // 벽 그리기
            RenderIndices(&landformObj[OBJECT_LANDFORM_WALL][wallCount], g_pTEXTURE_Array[TEXTURE_WALL], g_pVB_Array[VB_CUBE], g_pIB_Array[IB_CUBE], D3DPT_TRIANGLELIST, CUBE_VERTEX_COUNT, CUBE_TRIANGLE_COUNT);


        // 빌보드
        D3DXVECTOR3 v3BilboardX, v3BilboardZ;
        SetBilboardAngle(&v3BilboardX, &v3BilboardZ, v3LookAt, v3Eye);      // 빌보드 각도 설정
        for (int cubeCount = 0; cubeCount < TREE_COUNT; cubeCount++)        // 빌보드 그리기 (나무)
            RenderBilboard(landformObj[OBJECT_LANDFORM_TREE][cubeCount].GetMatrix(), landformObj[OBJECT_LANDFORM_TREE][cubeCount].GetRadius(), g_pTEXTURE_Array[TEXTURE_TREE], g_pVB_Array[VB_BILBOARD], v3BilboardX, v3BilboardZ, 0, D3DPT_TRIANGLEFAN);


        RenderEnemys(v3BilboardX, v3BilboardZ);             // 적 그리기
        RenderBullets(bullets, v3BilboardX, v3BilboardZ);
        
        DrawUI(font, pTextMetrics, dateInfo, sceneState);   // UI 그리기

        g_pd3dDevice->EndScene();                           // 렌더링 종료
    }
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);          // 화면에 출력
}

// 시점, 투영 변환
void SettingTmViewProjection(D3DXVECTOR3* lookAt, D3DXVECTOR3* eye, D3DXVECTOR3* up, SceneState sceneState, SliderData* sliderInfo)
{
    D3DXMATRIX tempViewTM, tm_Camera = *playerObj.GetMatrix();
    D3DXVECTOR3 v3LookAt(D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43) + D3DXVECTOR3(tm_Camera._31, tm_Camera._32, tm_Camera._33));
    D3DXVECTOR3 v3Eye(D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43));
    D3DXVECTOR3 v3Up(0.0f, 1.0f, 0.0f);
    
    *lookAt = v3LookAt;
    *eye = v3Eye;
    *up = v3Up;

    // 시점 변환
    D3DXMatrixLookAtLH(&tempViewTM, &v3Eye, &v3LookAt, &v3Up);
    g_pd3dDevice->SetTransform(D3DTS_VIEW, &tempViewTM);
    if (sceneState.clickKey[KEY_TOPVIEWCAMERA])    // 스페이스바 누르면 탑뷰로 변경
    {
        D3DXVECTOR3 v3TopCameraEye = D3DXVECTOR3(tm_Camera._41, 50.0f, tm_Camera._43);
        D3DXVECTOR3 v3TopCameraLookAt = D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43);
        D3DXVECTOR3 v3TopCameraUp = { 0, 0, 1 };
        D3DXMATRIX topCameraTM;

        D3DXMatrixLookAtLH(&topCameraTM, &v3TopCameraEye, &v3TopCameraLookAt, &v3TopCameraUp);
        g_pd3dDevice->SetTransform(D3DTS_VIEW, &topCameraTM);
    }

    // 3d -> 2d 투영
    D3DXMATRIX tempProjectionTM;
    D3DXMatrixPerspectiveFovLH(&tempProjectionTM, 0.8f + sliderInfo[SLIDER_FIELDOFVIEW].value * 0.4f, (FLOAT)WIDTH_WINDOW / (FLOAT)HEIGHT_WINDOW, NEAR_Z, FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &tempProjectionTM);

    SetFrustumPlane(tempViewTM, tempProjectionTM);  // 절두체 컬링을 위한 평면
}

// 인덱스 렌더링
void RenderIndices(CObject* obj, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, LPDIRECT3DINDEXBUFFER9 pIB, D3DPRIMITIVETYPE primitiveType, UINT numberVertices, UINT primCount)
{
    if (!RenderCommon(obj->GetMatrix(), obj->GetRadius(), pTexture, pVB))
        return;

    g_pd3dDevice->SetIndices(pIB);
    g_pd3dDevice->DrawIndexedPrimitive(primitiveType, 0, 0, numberVertices, 0, primCount);
}

// 버텍스 렌더링
void RenderVertices(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primCount)
{
    if (!RenderCommon(pTm, radius, pTexture, pVB))
        return;

    g_pd3dDevice->DrawPrimitive(primitiveType, startVertex, primCount);
}

// 렌더링 공통 부분
BOOL RenderCommon(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB)
{
    if (!IsSphereInFrustumPlane({ pTm->_41, pTm->_42,pTm->_43 }, radius, frustumPlane)) // 절두체 컬링
        return FALSE;

    g_pd3dDevice->SetTexture(0, pTexture);
    g_pd3dDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
    g_pd3dDevice->SetTransform(D3DTS_WORLD, pTm);
    return TRUE;
}

// 빌보드 렌더링
void RenderBilboard(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 g_pTextureBilboard, LPDIRECT3DVERTEXBUFFER9 g_pVB_Bilboard, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ, int startVertex, D3DPRIMITIVETYPE primitiveType)
{
    pTm->_11 = v3BilboardX.x;
    pTm->_12 = v3BilboardX.y;
    pTm->_13 = v3BilboardX.z;
    pTm->_21 = 0.0f;
    pTm->_22 = 1.0f;
    pTm->_23 = 0.0f;
    pTm->_31 = v3BilboardZ.x;
    pTm->_32 = v3BilboardZ.y;
    pTm->_33 = v3BilboardZ.z;

    RenderVertices(pTm, radius, g_pTextureBilboard, g_pVB_Bilboard, primitiveType, startVertex, 2);
}

// 빌보드 각도 설정
void SetBilboardAngle(D3DXVECTOR3* v3BilboardX, D3DXVECTOR3* v3BilboardZ, D3DXVECTOR3 v3LookAt, D3DXVECTOR3 v3Eye)
{
    D3DXVECTOR3 v3CameraFront = v3Eye - v3LookAt;

    D3DXVec3Cross(v3BilboardX, &v3CameraFront, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    D3DXVec3Normalize(v3BilboardX, v3BilboardX);

    D3DXVec3Cross(v3BilboardZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), v3BilboardX);
    D3DXVec3Normalize(v3BilboardZ, v3BilboardZ);
}

// 적 그리기
void RenderEnemys(D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ)
{
    int enemy1NumberVertices = sizeof(enemy1Vertices) / sizeof(enemy1Vertices[0]);
    int enemy1PrimCount = sizeof(enemy1Indices) / sizeof(enemy1Indices[0]);

    for (int enemyCount = 0; enemyCount < ENEMY_MAX; enemyCount++)
    {
        if (enemyObj[enemyCount] == NULL)
            continue;

        RenderIndices(enemyObj[enemyCount], g_pTEXTURE_Array[TEXTURE_ENEMY_TURTLE], g_pVB_Array[VB_ENEMY1], g_pIB_Array[IB_ENEMY1], D3DPT_TRIANGLELIST, enemy1NumberVertices, enemy1PrimCount);

        // 체력 게이지
        VOID* pVertices;
        g_pVB_Array[VB_ENEMYHPBAR]->Lock(0, sizeof(enemyHpBarVertices), (void**)&pVertices, 0);   // Lock(lock할 시작점, 크기, 버퍼의 주소, 0)
        enemyHpBarVertices[5].position.x = enemyHpBarVertices[6].position.x = enemyObj[enemyCount]->GetNowHpRate() - 0.5f;
        memcpy(pVertices, enemyHpBarVertices, sizeof(enemyHpBarVertices));              // 버퍼에 값을 넣는다
        g_pVB_Array[VB_ENEMYHPBAR]->Unlock();

        RenderBilboard(&enemyObj[enemyCount]->GetHpBarMatrix(), enemyObj[enemyCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_HPBAR_RED], g_pVB_Array[VB_ENEMYHPBAR], v3BilboardX, v3BilboardZ, 0, D3DPT_TRIANGLEFAN);    // 체력게이지 바탕(빨강)
        RenderBilboard(&enemyObj[enemyCount]->GetHpBarMatrix(), enemyObj[enemyCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_HPBAR_GREEN], g_pVB_Array[VB_ENEMYHPBAR], v3BilboardX, v3BilboardZ, 4, D3DPT_TRIANGLEFAN);  // 체력게이치 현재 체력(초록)
    }
}

// 총알 그리기
void RenderBullets(CBullet** bullets, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ)
{
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)
    {
        if (bullets[bulletCount] == NULL)
            continue;

        if (bullets[bulletCount]->GetFireSprite().GetIsPlaySprite())    // 접촉 시 불꽃 그림
            RenderBilboard(bullets[bulletCount]->GetMatrix(), bullets[bulletCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_FIRE], g_pVB_Array[VB_BULLETFIRE], v3BilboardX, v3BilboardZ, bullets[bulletCount]->GetFireSprite().GetNowTextureCount() * 4, D3DPT_TRIANGLEFAN);
        else                                                            // 접촉하기 전에는 총알 그림
            RenderIndices(bullets[bulletCount], g_pTEXTURE_Array[TEXTURE_BULLETCOLOR], g_pVB_Array[VB_BULLET], g_pIB_Array[IB_BULLET], D3DPT_TRIANGLELIST, 12, 20);
    }
}


// 알파 테스트 (어떠한 상황에도 뒤에 있는 것을 그릴 수 있지만 반투명이 불가능,  오직 투명 or 불투명)
void _SetAlphaTest()
{
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);        // 알파 블렌딩 끄기
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);          // 알파 테스트 켜기
    g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);           // 알파 테스트 투명/불투명 기준값
    g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);      // 기준값보다 크면 그린다
}

// 알파 블렌딩 (랜더링 순서에 따라 뒤에 있는 것이 안 보임)
void _SetAlphaBlend()
{
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);         // 알파 테스트 끄기
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);         // 알파 블렌딩 켜기
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // 소스 알파 블렌딩, 새로 그려질 그림
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// 반대 알파값 블렌딩, 원래 있던 그림
}

// 조명 설정
void _SetLight(D3DLIGHTTYPE lightType, D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DVECTOR position, D3DVECTOR direction, FLOAT range, FLOAT falloff, FLOAT theta, FLOAT phi, DWORD lightIndex)
{
    D3DLIGHT9 d3dLight;
    ZeroMemory(&d3dLight, sizeof(d3dLight));
    d3dLight.Type = lightType;

    d3dLight.Diffuse = diffuse;      // 확산광
    d3dLight.Ambient = ambient;      // 주변광
    d3dLight.Specular = specular;    // 반사광

    switch (lightType)
    {
    case D3DLIGHT_POINT:
        d3dLight.Position = position;
        d3dLight.Range = range;
        break;

    case D3DLIGHT_SPOT:
        d3dLight.Position = position;
        d3dLight.Direction = direction;

        d3dLight.Range = range;
        d3dLight.Falloff = falloff;
        d3dLight.Theta = theta;
        d3dLight.Phi = phi;

        d3dLight.Attenuation0 = 0.005f;
        d3dLight.Attenuation1 = 0.005f;
        d3dLight.Attenuation2 = 0.005f;
        break;

    case D3DLIGHT_DIRECTIONAL:
        d3dLight.Direction = direction;
        break;
    }

    g_pd3dDevice->SetLight(lightIndex, &d3dLight);
    g_pd3dDevice->LightEnable(lightIndex, TRUE);
}

// 재질 설정
void _SetMatrial(D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DCOLORVALUE emissive, FLOAT power)
{
    D3DMATERIAL9 d3dMaterial;
    ZeroMemory(&d3dMaterial, sizeof(d3dMaterial));
    d3dMaterial.Diffuse = diffuse;
    d3dMaterial.Ambient = ambient;
    d3dMaterial.Specular = specular;

    d3dMaterial.Emissive = emissive;  // 자체발광
    //d3dMaterial.Power = power;        // Speculare에 쓰여지는 Power

    g_pd3dDevice->SetMaterial(&d3dMaterial);
}

// 절두체 평면 설정
void SetFrustumPlane(D3DXMATRIX tempViewTM, D3DXMATRIX tempProjectionTM)
{
    D3DXMATRIX viewProjMatrix;
    D3DXMatrixMultiply(&viewProjMatrix, &tempViewTM, &tempProjectionTM);

    // 평면의 방정식 ax + by + cz + d에서
    // 법선벡터가 단위벡터일때 (a, b, c)가 그대로 법선 벡터가 된다.

    // 절두체 평면을 담을 배열
    frustumPlane[0] = D3DXPLANE(viewProjMatrix._13, viewProjMatrix._23, viewProjMatrix._33, viewProjMatrix._43); // near
    frustumPlane[1] = D3DXPLANE(viewProjMatrix._14 - viewProjMatrix._13, viewProjMatrix._24 - viewProjMatrix._23, 
        viewProjMatrix._34 - viewProjMatrix._33, viewProjMatrix._44 - viewProjMatrix._43); // far
    frustumPlane[2] = D3DXPLANE(viewProjMatrix._14 - viewProjMatrix._12, viewProjMatrix._24 - viewProjMatrix._22,
        viewProjMatrix._34 - viewProjMatrix._32, viewProjMatrix._44 - viewProjMatrix._42); // top
    frustumPlane[3] = D3DXPLANE(viewProjMatrix._14 + viewProjMatrix._12, viewProjMatrix._24 + viewProjMatrix._22, 
        viewProjMatrix._34 + viewProjMatrix._32, viewProjMatrix._44 + viewProjMatrix._42); // bottom
    frustumPlane[4] = D3DXPLANE(viewProjMatrix._14 - viewProjMatrix._11, viewProjMatrix._24 - viewProjMatrix._21, 
        viewProjMatrix._34 - viewProjMatrix._31, viewProjMatrix._44 - viewProjMatrix._41); // right
    frustumPlane[5] = D3DXPLANE(viewProjMatrix._14 + viewProjMatrix._11, viewProjMatrix._24 + viewProjMatrix._21, 
        viewProjMatrix._34 + viewProjMatrix._31, viewProjMatrix._44 + viewProjMatrix._41); // left

    for (int i = 0; i < 6; i++)
        D3DXPlaneNormalize(&frustumPlane[i], &frustumPlane[i]);
}

extern bool cullingOn;

// 절두체 컬링
BOOL IsSphereInFrustumPlane(const D3DXVECTOR3& center, float radius, D3DXPLANE planes[6])
{
    if (!cullingOn)
        return true;

    for (int i = 0; i < 6; ++i)
    {
        float distance = planes[i].a * center.x + planes[i].b * center.y + planes[i].c * center.z + planes[i].d;
        if (distance < -radius)     return false;   // 거리가 -반지름보다 작으면 평면 밖
    }
    return true;
}


// UI 그리기
void DrawUI(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    g_pd3dDevice->SetFVF(SCREEN_VERTEX::FVF);

    _SetAlphaBlend();   // 알파 블렌딩 (랜더링 순서에 따라 뒤에 있는 것이 안 보임)

    switch (sceneState.nowSceneType)
    {
    case SCENE_SCORE:  DrawScoreScene(font);
    case SCENE_TITLE:  DrawTitleScene(font);                                    break;
    case SCENE_GAME:   DrawGameScene(font, pTextMetrics, dateInfo, sceneState); break;
    case SCENE_RESULT: DrawResultScene(font);                                   break;
    }
}

// UI
// 타이틀의 점수 창 UI
void DrawScoreScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 16, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f,        HEIGHT_WINDOW / 10.0f, 0, 0, "순위");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 2.0f, HEIGHT_WINDOW / 10.0f, 0, 0, "점수");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 3.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "킬");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 4.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "생존기록");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 6.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "기록일시");


    for (int i = 0; i < 10; i++)
    {
        if (!saveData[i].score)
            break;

        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f,        HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", i + 1);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 2.0f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", saveData[i].score);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 3.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", saveData[i].killCount);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 4.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d월 %d일", saveData[i].aliveTime[0], saveData[i].aliveTime[1]);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 6.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d/%d/%d", saveData[i].realTime[0], saveData[i].realTime[1], saveData[i].realTime[2]);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 8.2f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d:%d", saveData[i].realTime[3], saveData[i].realTime[4]);
    }
}

// 타이틀 UI
void DrawTitleScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, NULL);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices, sizeof(SCREEN_VERTEX));         // 흰 바탕

    if (isBtnOnMouse[BUTTON_PLAY])  g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 4, sizeof(SCREEN_VERTEX));     // 플레이 버튼

    if (isBtnOnMouse[BUTTON_SCORE]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 8, sizeof(SCREEN_VERTEX));     // 점수 버튼

    if (isBtnOnMouse[BUTTON_END]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_RED_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_RED]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 12, sizeof(SCREEN_VERTEX));    // 종료 버튼

    _drawText(font, TRUE, titleSceneVertices[4].x, titleSceneVertices[4].y, titleSceneVertices[5].x, titleSceneVertices[7].y, "플레이");
    _drawText(font, TRUE, titleSceneVertices[8].x, titleSceneVertices[8].y, titleSceneVertices[9].x, titleSceneVertices[11].y, "점수");
    _drawText(font, TRUE, titleSceneVertices[12].x, titleSceneVertices[12].y, titleSceneVertices[13].x, titleSceneVertices[15].y, "종료");
}

// 게임씬 UI
void DrawGameScene(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    for (int btnNum = 0; btnNum < 5; btnNum++)                  // 버튼 그리기 (우상단)
    {
        g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_PLAY + btnNum]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices + 4 * (btnNum + 1), sizeof(SCREEN_VERTEX));
    }

    DrawHelpWindow(sceneState, font, pTextMetrics, dateInfo);   // 도움말 그리기 (좌상단)
    DrawLevelUpUI(sceneState, font, pTextMetrics);              // 레벨업 보너스 선택 화면
    DrawPlayerLvHpExp(font);                      // 플레이어 레벨, HP, 경험치 그리기 (좌하단)
    DrawCrossCenterLine(sceneState);              // 마우스 조준모드 십자선 그리기
    DrawMenuUI(sceneState, font, pTextMetrics);   // 메뉴 UI
}

// 결과창 UI
void DrawResultScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, NULL);
    if (nowGameData[NOWGAME_RANKING] < 10)
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices + 8, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 1.75,  HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "순위");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 2.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "점수");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 3.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "킬");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 4.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "생존기록");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 6.25f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "기록일시");

    for (int i = 0; i < 10; i++)
    {
        if (!saveData[i].score)
            break;

        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 1.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", i + 1);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 2.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", saveData[i].score);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 3.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", saveData[i].killCount);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 4.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d 월  %d 일", saveData[i].aliveTime[0], saveData[i].aliveTime[1]);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 6.25f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d / %d / %d", saveData[i].realTime[0], saveData[i].realTime[1], saveData[i].realTime[2]);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 7.5f,  HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d : %d", saveData[i].realTime[3], saveData[i].realTime[4]);
    }

    if (isBtnOnMouse[BUTTON_TONEXT]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BROWN]); // 다음으로 버튼
    else                             g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BROWN_Light]);

    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices + 4, sizeof(SCREEN_VERTEX));
    _drawText(font, TRUE, resultSceneVertices[4].x, resultSceneVertices[4].y, resultSceneVertices[5].x, resultSceneVertices[7].y, "다음으로");
}


// 도움말 그리기
void DrawHelpWindow(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo)
{
    RECT strRect;
    char str[64] = "";

    if (sceneState.openHelp)
    {
        g_pd3dDevice->SetTexture(0, NULL);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices, sizeof(SCREEN_VERTEX));
        DrawHelpTexts(font, pTextMetrics, dateInfo);   // 도움말
    }
    else
    {
        if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
            textColor = { 1.0f, 1.0f, 1.0f, 1.0f };

        _drawText(font, FALSE, 10, 12, 0, 0, "일시: %d월 %d일 %d시   ", dateInfo.month, dateInfo.day, (int)dateInfo.clock);
        _drawText(font, FALSE, 10, 12 + pTextMetrics.tmHeight, 0, 0, "fps: %.2f", 1.0f / timer.GetDeltaTime());
        _drawText(font, FALSE, 10, 12 + pTextMetrics.tmHeight * 3, 0, 0, "[F1] 도움말 열기");
    }

    if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
        textColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    _drawText(font, FALSE, WIDTH_WINDOW * 0.35f, HEIGHT_WINDOW * 0.02f, 0, 0, "High Score: %d", nowGameData[NOWGAME_BESTSCORE]);
    _drawText(font, FALSE, WIDTH_WINDOW * 0.35f, HEIGHT_WINDOW * 0.02f + pTextMetrics.tmHeight, 0, 0, "Score: %d", nowGameData[NOWGAME_SCORE]);

    if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
        textColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

// 도움말 글자
void DrawHelpTexts(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo)
{
    RECT strRect;
    int textHeight = pTextMetrics.tmHeight;
    char* helpTexts[11] = { "이동: wasd / ↑←↓→", "회전: 마우스 좌우 회전", "      우클릭으로 회전 고정", "점프: 스페이스 바", "1.카메라 전환    2.랜턴 on/off", "3.손전등 on/off  4.태양 on/off", 
        "TAB.마우스 조준 모드 변경", "ESC.메뉴         Q.종료", "우상단 버튼(왼쪽부터 순서대로)", "    시간 재생/정지, 다음 시간, ", "    다음 날, 다음 달, 메뉴" };

    if (font == NULL)
        return;

    for (int i = 0; i < 11; i++)
        _drawText(font, FALSE, 10, 12 + (textHeight + 1) * i, 0, 0, helpTexts[i]);

    _drawText(font, FALSE, 10, 12 + (textHeight + 1) * 11, 0, 0, "일시: %d월 %d일 %d시   ", dateInfo.month, dateInfo.day, (int)dateInfo.clock);
    _drawText(font, FALSE, 10, 12 + (textHeight + 1) * 12, 0, 0, "fps: %.2f", 1.0f / timer.GetDeltaTime());
}

// 십자선 그리기
void DrawCrossCenterLine(SceneState sceneState)
{
    if (sceneState.mouseCrossFocusMode)
    {
        g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_CROSSLINE]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices + 24, sizeof(SCREEN_VERTEX));
    }
}

// 플레이어 레벨, HP, 경험치 그리기 (좌하단)
void DrawPlayerLvHpExp(LPD3DXFONT font)
{
    _SetAlphaBlend();

    // 플레이어 레벨
    g_pd3dDevice->SetTexture(0, NULL);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 16, sizeof(SCREEN_VERTEX));
    _drawText(font, FALSE, PLAYERHPMIN, (int)(HEIGHT_WINDOW / 8.0f * 6.25f), 0, 0, " Lv. %d", playerObj.GetLevel());

    // 플레이어 체력
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_HPBAR_RED]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_HPBAR_GREEN]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 4, sizeof(SCREEN_VERTEX));

    // 플레이어 경험치
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_EXPBAR_GRAY]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 8, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_EXPBAR_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 12, sizeof(SCREEN_VERTEX));

    _SetAlphaTest();
}

// 메뉴창 그리기
void DrawMenuUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics)
{
    if (!sceneState.isOpenMenu)
        return;

    if (sceneState.isOpenMenu == 1) // 왼쪽에 튀어나와 있는 플레이어 정보
    {
        menuVertices[4].color = menuVertices[5].color = menuVertices[6].color = menuVertices[7].color = 0xbffffffff;
        menuVertices[8].color = menuVertices[9].color = menuVertices[10].color = menuVertices[11].color = 0xff909090;
    }
    else // 왼쪽에 튀어나와 있는 설정
    {
        menuVertices[4].color = menuVertices[5].color = menuVertices[6].color = menuVertices[7].color = 0xff909090;
        menuVertices[8].color = menuVertices[9].color = menuVertices[10].color = menuVertices[11].color = 0xffffffff;
    }

    _SetAlphaTest();
    // 가운데 큰 사각형 설정 백그라운드
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices, sizeof(SCREEN_VERTEX));
    _SetAlphaBlend();

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BTN]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 4, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 8, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, (menuVertices[4].x + menuVertices[5].x) * 0.5f - pTextMetrics.tmAveCharWidth * 6, (menuVertices[4].y + menuVertices[7].y) * 0.5f - pTextMetrics.tmHeight * 0.5f, 0, 0, "플레이어 정보");
    _drawText(font, FALSE, (menuVertices[8].x + menuVertices[9].x) * 0.5f - pTextMetrics.tmAveCharWidth * 2, (menuVertices[8].y + menuVertices[11].y) * 0.5f - pTextMetrics.tmHeight * 0.5f, 0, 0, "설정");


    if (sceneState.isOpenMenu == 1)         // 정보
    {
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 4, 0, 0, "레벨 :  %d", playerObj.GetLevel());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 6, 0, 0, "체력 :  %d / %d", playerObj.GetHpNow(), playerObj.GetHpMax());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 8, 0, 0, "경험치 :  %d / %d", playerObj.GetNowExp(), playerObj.GetLevelUpExp());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 12, 0, 0, "이동속도 :  %.2f", playerObj.GetMoveSpeed());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 14, 0, 0, "공격력 :  %d", playerObj.GetAttackDamage());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 16, 0, 0, "공격 딜레이 :  %.2f", playerObj.GetAttackDelay());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 18, 0, 0, "자연 회복량 :  %d", playerObj.GetHpRecoveryRate());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 20, 0, 0, "자연 회복 딜레이 :  %.2f", playerObj.GetHpRecoveryDelay());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 22, 0, 0, "경험치 획득 배율 :  %.2f", playerObj.GetExpBonusRate());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 25, 0, 0, "총알 분사 :  %d     총알 연사 :  %d      더 큰 총알 :  %d", playerObj.GetAttackSpreadLevel(), playerObj.GetAttackBurstLevel(), playerObj.GetBulletSizeLevel());
    }
    else if (sceneState.isOpenMenu == 2)    // 설정
    {
        // 슬라이더
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 0);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 20);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 40);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 60);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 80);

        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5].x) * 0.4f, menuSliderVertices[5].y, 0, 0, "시야각");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 20].x) * 0.4f, menuSliderVertices[5 + 20].y, 0, 0, "시야 범위");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 40].x) * 0.4f, menuSliderVertices[5 + 40].y, 0, 0, "마우스 회전 감도");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 60].x) * 0.4f, menuSliderVertices[5 + 60].y, 0, 0, "BGM");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 80].x) * 0.4f, menuSliderVertices[5 + 80].y, 0, 0, "SE");

        // 타이틀로 버튼
        if (isBtnOnMouse[BUTTON_TOTITLE]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
        else                              g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 12, sizeof(SCREEN_VERTEX));
        _drawText(font, TRUE, menuVertices[12].x, menuVertices[12].y, menuVertices[13].x, menuVertices[15].y, "타이틀 화면으로");

        // FPS
        g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_OUTLINERECT]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 16, sizeof(SCREEN_VERTEX));
        _drawText(font, FALSE, menuVertices[40].x, menuVertices[40].y, 0, 0, "FPS");
        _drawText(font, TRUE, menuVertices[16].x, menuVertices[16].y, menuVertices[17].x, menuVertices[19].y, "%d", timer.GetFPS());
        
        if (sceneState.clickSetFPS)
        {
            int fpsArray[5] = { 30, 45, 60, 90, 120 };
            for (int fpsType = 0; fpsType < 5; fpsType++)
            {
                g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 20 + 4 * fpsType, sizeof(SCREEN_VERTEX));
                _drawText(font, TRUE, menuVertices[20 + 4 * fpsType].x, menuVertices[20 + 4 * fpsType].y, menuVertices[21 + 4 * fpsType].x, menuVertices[23 + 4 * fpsType].y, "%d", fpsArray[fpsType]);
            }
        }
    }
}

// 레벨업 보너스 선택 화면
void DrawLevelUpUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics)
{
    if (!sceneState.onLevelUpScreen)
        return;

    _SetAlphaTest();

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_LVUP_BG_BROWN]);  // 바탕 부분
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_LVUP_BG_WHITE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 4, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 8, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 12, sizeof(SCREEN_VERTEX));

    //_drawText(font, TRUE, levelUpScreenVertices[16].x, levelUpScreenVertices[16].y, levelUpScreenVertices[18].x, levelUpScreenVertices[18].y, "Level Up Bonus Card");


    for (int lvUpCard = 0; lvUpCard < 3; lvUpCard++)    // 레벨업 보너스 카드 3개
    {
        char lvUpCardTexts[4][32] = { "", "", "", "" };
        char lvUpCardEffectNum[32] = "";

        switch (playerObj.GetLevelUpBonusNum()[lvUpCard])
        {
        case HP_MAX_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "최대 체력 증가", "플레이어의", "최대 체력이", "20 증가한다");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetHpMax(), playerObj.GetHpMax() + 20);
            break;

        case HP_RECOVER_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "체력 회복량 증가", "플레이어의", "회복 주기가 짧아지고", "회복량이 2 증가한다");
            sprintf_s(lvUpCardEffectNum, "%d -> %d,  %.2f -> %.2f", playerObj.GetHpRecoveryRate(), playerObj.GetHpRecoveryRate() + 2, playerObj.GetHpRecoveryDelay(), playerObj.GetHpRecoveryDelay() * 0.95f);
            break;

        case MOVE_SPEED_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "이동 속도 증가", "플레이어의", "이동 속도가", "증가한다");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetMoveSpeed(), playerObj.GetMoveSpeed() + 0.2f);
            break;

        case ATTACK_DAMAGE_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "공격력 증가", "플레이어의", "공격 데마지가", "2 증가한다");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackDamage(), playerObj.GetAttackDamage() + 2);
            break;

        case ATTACK_SPEED_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "공격 속도 증가", "플레이어의", "공격 딜레이가", "짧아진다");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetAttackDelay(), playerObj.GetAttackDelay() * 0.95f);
            break;

        case GET_EXP_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "획득 경험치 증가", "플레이어의", "획득 경험치 배율이", "1.1배 증가한다");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetExpBonusRate(), playerObj.GetExpBonusRate() + 0.1f);
            break;

        case BULLET_SPREAD_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "총알 분사", "총알을 레벨만큼", "옆으로 퍼뜨려서 발사", " +1");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackSpreadLevel(), playerObj.GetAttackSpreadLevel() + 1);
            if (playerObj.GetAttackSpreadLevel() >= SPREADLEVELMAX) sprintf_s(lvUpCardEffectNum, "%d (Level MAX)", playerObj.GetAttackSpreadLevel());
            break;

        case BULLET_BURST_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "총알 연사", "총알을 레벨만큼", "연달아 발사", " +1");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackBurstLevel(), playerObj.GetAttackBurstLevel() + 1);
            if (playerObj.GetAttackBurstLevel() >= BURSTLEVELMAX)  sprintf_s(lvUpCardEffectNum, "%d (Level MAX)", playerObj.GetAttackBurstLevel());
            break;

        case BULLET_SIZE_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "더 큰 총알", "총알이 커지고", "데미지가 증가한다", "크기 +10%, 데미지 +20%");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetBulletSizeLevel(), playerObj.GetBulletSizeLevel() + 1);
            if (playerObj.GetBulletSizeLevel() >= BULLETSIZELEVELMAX)  sprintf_s(lvUpCardEffectNum, "%d (Level MAX)", playerObj.GetBulletSizeLevel());
            break;

        default:
            break;
        }
        
        _drawText(font, FALSE, levelUpScreenVertices[4 * (lvUpCard + 1)].x + WIDTH_WINDOW / 40, levelUpScreenVertices[4 * (lvUpCard + 1)].y + pTextMetrics.tmHeight * 4, 0, 0, lvUpCardTexts[0]);
        _drawText(font, FALSE, levelUpScreenVertices[4 * (lvUpCard + 1)].x + WIDTH_WINDOW / 40, levelUpScreenVertices[4 * (lvUpCard + 1)].y + pTextMetrics.tmHeight * 9, 0, 0, lvUpCardTexts[1]);
        _drawText(font, FALSE, levelUpScreenVertices[4 * (lvUpCard + 1)].x + WIDTH_WINDOW / 40, levelUpScreenVertices[4 * (lvUpCard + 1)].y + pTextMetrics.tmHeight * 10, 0, 0, lvUpCardTexts[2]);
        _drawText(font, FALSE, levelUpScreenVertices[4 * (lvUpCard + 1)].x + WIDTH_WINDOW / 40, levelUpScreenVertices[4 * (lvUpCard + 1)].y + pTextMetrics.tmHeight * 11, 0, 0, lvUpCardTexts[3]);
        _drawText(font, FALSE, levelUpScreenVertices[4 * (lvUpCard + 1)].x + WIDTH_WINDOW / 40, levelUpScreenVertices[4 * (lvUpCard + 1)].y + pTextMetrics.tmHeight * 14, 0, 0, lvUpCardEffectNum);
    }
}

// 레벨업 카드 글자
void SetLevelUpBonusCardTexts(char lvUpCardTexts[5][32], char* cardName, char* cardEffect1, char* cardEffect2, char* cardEffect3)
{
    strcat_s(lvUpCardTexts[0], cardName);
    strcat_s(lvUpCardTexts[1], cardEffect1);
    strcat_s(lvUpCardTexts[2], cardEffect2);
    strcat_s(lvUpCardTexts[3], cardEffect3);
}

// 슬라이더 그리기
void DrawSliderHorizontal(LPDIRECT3DTEXTURE9 textureEmptySlider, LPDIRECT3DTEXTURE9 textureFillSlider, LPDIRECT3DTEXTURE9 textureSliderHandle, int startVertex)
{
    g_pd3dDevice->SetTexture(0, textureEmptySlider);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, textureEmptySlider);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex + 4, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, textureEmptySlider);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex + 8, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, textureFillSlider);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex + 12, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex + 4, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, textureSliderHandle);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuSliderVertices + startVertex + 16, sizeof(SCREEN_VERTEX));
}