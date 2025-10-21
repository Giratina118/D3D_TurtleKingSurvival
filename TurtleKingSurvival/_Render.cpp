#include "_Render.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "_SaveLoadData.h"
#include <iostream>

extern LPDIRECT3DDEVICE9        g_pd3dDevice;                   // �������� ���� D3D ����̽�
extern LPDIRECT3DVERTEXBUFFER9  g_pVB_Array[VB_MAX];            // ����
extern LPDIRECT3DINDEXBUFFER9   g_pIB_Array[IB_MAX];            // �ε���
extern LPDIRECT3DTEXTURE9       g_pTEXTURE_Array[TEXTURE_MAX];  // �ؽ�ó
extern CPlayer  playerObj;                  // �÷��̾� ������Ʈ
extern CEnemy*  enemyObj[ENEMY_MAX];        // �� ������Ʈ

extern Timer    timer;                      // Ÿ�̸�
extern int      nowGameData[NOWGAME_MAX];   // ���� ���� ����
extern SaveData saveData[10];               // ���� ����

D3DXPLANE frustumPlane[6];                  // ����ü �ø� ���
D3DXCOLOR textColor = { 0.0f, 0.0f, 0.0f, 1.0f };   // ���� ��
extern bool isBtnOnMouse[BUTTON_MAX];

// ���� ����� ���
template <typename T, typename... Types>
void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* text, T arg, Types... args) {
    char str[64] = "";
    sprintf_s(str, text, arg, args...);
    _drawText(font, center, xLeft, yTop, xRight, yBottom, str);
}

// �ؽ�Ʈ �׸���
void _drawText(LPD3DXFONT font, BOOL center, int xLeft, int yTop, int xRight, int yBottom, const char* str)
{
    DWORD DT;
    RECT strRect;
    if (center) DT = DT_NOCLIP | DT_CENTER | DT_VCENTER;
    else        DT = DT_NOCLIP;

    SetRect(&strRect, xLeft, yTop, xRight, yBottom);
    font->DrawText(NULL, str, -1, &strRect, DT, textColor);
}


// ȭ�� �׸���
void Render(CObject** landformObj, CBullet* bullets[BULLET_MAX], SliderData* sliderInfo, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    if (NULL == g_pd3dDevice)   return;

    // ȭ�� ����� (����)
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(180, 200, 255), 1.0f, 0);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    g_pd3dDevice->SetFVF(CUSTOMVERTEX::FVF);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))  // ������ ����
    {
        D3DXVECTOR3 v3LookAt, v3Eye, v3Up;
        SettingTmViewProjection(&v3LookAt, &v3Eye, &v3Up, sceneState, sliderInfo);  // ����, ���� ��ȯ

        _SetAlphaTest();    // ���� �׽�Ʈ (��� ��Ȳ���� �ڿ� �ִ� ���� �׸� �� ������ �������� �Ұ���,  ���� ���� or ������)

        // ���� ����
        if (sceneState.clickKey[KEY_POINTLIGHT])    // ����
            _SetLight(D3DLIGHT_POINT, { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.1f, 0.1f, 0.1f, 0.5f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { playerObj.GetMatrix()->_41, playerObj.GetMatrix()->_42, playerObj.GetMatrix()->_43 }, { 0, 0, 0 }, 2.5f, 0.0f, 0.0f, 0.0f, 0);
        else    g_pd3dDevice->LightEnable(0, FALSE);

        if (sceneState.clickKey[KEY_SPOTLIGHT])     // ������
           _SetLight(D3DLIGHT_SPOT, { 0.6f, 0.6f, 0.6f, 1.0f }, { 0.2f, 0.2f, 0.2f, 0.5f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { playerObj.GetMatrix()->_41, playerObj.GetMatrix()->_42 - 1, playerObj.GetMatrix()->_43 }, { playerObj.GetMatrix()->_31, playerObj.GetMatrix()->_32, playerObj.GetMatrix()->_33 }, 20.0f, 1.0f, 0.2f, 0.7f, 1);
        else    g_pd3dDevice->LightEnable(1, FALSE);

        // �¾�
        FLOAT sunDirY = dateInfo.sunDirection.y;
        D3DCOLORVALUE sunDiffuse = { 0.8f * -sunDirY, 0.8f * -sunDirY, 0.7f * -sunDirY, 1.0f };
        D3DCOLORVALUE sunAmbient = { 0.2f * -sunDirY, 0.2f * -sunDirY, 0.2f * -sunDirY, 1.0f };
        if (sceneState.clickKey[KEY_DIRECTIONALLIGHT])
            _SetLight(D3DLIGHT_DIRECTIONAL, sunDiffuse, sunAmbient, { 0.5f, 0.5f, 0.5f, 1.0f }, {0, 0, 0}, dateInfo.sunDirection, 0.0f, 0.0f, 0.0f, 0.0f, 2);
        else    g_pd3dDevice->LightEnable(2, FALSE);

        // ��
        _SetLight(D3DLIGHT_DIRECTIONAL, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.2f, 0.2f, 0.2f, 0.5f }, { 0.0f, 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0.0f, 1.0f, 0.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 3);
        
        
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);     // ��ī�̹ڽ� �׸���
        _SetMatrial({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.2f, 0.2f, 0.2f, 1.0f }, 0.01f); // ���� ����
        
        D3DXMATRIX iMatrix = {1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  v3Eye.x, v3Eye.y, v3Eye.z, 1};
        for (int skyBoxCount = 0; skyBoxCount < 6; skyBoxCount++)
            RenderVertices(&iMatrix, 50, g_pTEXTURE_Array[skyBoxCount + TEXTURE_SKYBOX_RIGHT], g_pVB_Array[VB_SKYBOX], D3DPT_TRIANGLEFAN, 4 * skyBoxCount, 2);
        

        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        _SetMatrial({ 0.8f, 0.6f, 0.4f, 1.0f }, { 0.8f, 0.8f, 0.8f, 1.0f }, { 0.1f, 0.1f, 0.1f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, 0.01f); // ���� ����

        for (int groundCount = 0; groundCount < GROUND_X * GROUND_Z; groundCount++)     // �ٴ� �׸���
            RenderVertices(landformObj[OBJECT_LANDFORM_GROUND][groundCount].GetMatrix(), GROUND_RADIUS * 1.4f, g_pTEXTURE_Array[TEXTURE_GRASS], g_pVB_Array[VB_GRASS], D3DPT_TRIANGLEFAN, 0, 2);

        for (int wallCount = 0; wallCount < WALL_COUNT; wallCount++)                    // �� �׸���
            RenderIndices(&landformObj[OBJECT_LANDFORM_WALL][wallCount], g_pTEXTURE_Array[TEXTURE_WALL], g_pVB_Array[VB_CUBE], g_pIB_Array[IB_CUBE], D3DPT_TRIANGLELIST, CUBE_VERTEX_COUNT, CUBE_TRIANGLE_COUNT);


        // ������
        D3DXVECTOR3 v3BilboardX, v3BilboardZ;
        SetBilboardAngle(&v3BilboardX, &v3BilboardZ, v3LookAt, v3Eye);      // ������ ���� ����
        for (int cubeCount = 0; cubeCount < TREE_COUNT; cubeCount++)        // ������ �׸��� (����)
            RenderBilboard(landformObj[OBJECT_LANDFORM_TREE][cubeCount].GetMatrix(), landformObj[OBJECT_LANDFORM_TREE][cubeCount].GetRadius(), g_pTEXTURE_Array[TEXTURE_TREE], g_pVB_Array[VB_BILBOARD], v3BilboardX, v3BilboardZ, 0, D3DPT_TRIANGLEFAN);


        RenderEnemys(v3BilboardX, v3BilboardZ);             // �� �׸���
        RenderBullets(bullets, v3BilboardX, v3BilboardZ);
        
        DrawUI(font, pTextMetrics, dateInfo, sceneState);   // UI �׸���

        g_pd3dDevice->EndScene();                           // ������ ����
    }
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);          // ȭ�鿡 ���
}

// ����, ���� ��ȯ
void SettingTmViewProjection(D3DXVECTOR3* lookAt, D3DXVECTOR3* eye, D3DXVECTOR3* up, SceneState sceneState, SliderData* sliderInfo)
{
    D3DXMATRIX tempViewTM, tm_Camera = *playerObj.GetMatrix();
    D3DXVECTOR3 v3LookAt(D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43) + D3DXVECTOR3(tm_Camera._31, tm_Camera._32, tm_Camera._33));
    D3DXVECTOR3 v3Eye(D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43));
    D3DXVECTOR3 v3Up(0.0f, 1.0f, 0.0f);
    
    *lookAt = v3LookAt;
    *eye = v3Eye;
    *up = v3Up;

    // ���� ��ȯ
    D3DXMatrixLookAtLH(&tempViewTM, &v3Eye, &v3LookAt, &v3Up);
    g_pd3dDevice->SetTransform(D3DTS_VIEW, &tempViewTM);
    if (sceneState.clickKey[KEY_TOPVIEWCAMERA])    // �����̽��� ������ ž��� ����
    {
        D3DXVECTOR3 v3TopCameraEye = D3DXVECTOR3(tm_Camera._41, 50.0f, tm_Camera._43);
        D3DXVECTOR3 v3TopCameraLookAt = D3DXVECTOR3(tm_Camera._41, tm_Camera._42, tm_Camera._43);
        D3DXVECTOR3 v3TopCameraUp = { 0, 0, 1 };
        D3DXMATRIX topCameraTM;

        D3DXMatrixLookAtLH(&topCameraTM, &v3TopCameraEye, &v3TopCameraLookAt, &v3TopCameraUp);
        g_pd3dDevice->SetTransform(D3DTS_VIEW, &topCameraTM);
    }

    // 3d -> 2d ����
    D3DXMATRIX tempProjectionTM;
    D3DXMatrixPerspectiveFovLH(&tempProjectionTM, 0.8f + sliderInfo[SLIDER_FIELDOFVIEW].value * 0.4f, (FLOAT)WIDTH_WINDOW / (FLOAT)HEIGHT_WINDOW, NEAR_Z, FAR_Z / 2.0f + FAR_Z * sliderInfo[SLIDER_VIEWFAR].value);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &tempProjectionTM);

    SetFrustumPlane(tempViewTM, tempProjectionTM);  // ����ü �ø��� ���� ���
}

// �ε��� ������
void RenderIndices(CObject* obj, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, LPDIRECT3DINDEXBUFFER9 pIB, D3DPRIMITIVETYPE primitiveType, UINT numberVertices, UINT primCount)
{
    if (!RenderCommon(obj->GetMatrix(), obj->GetRadius(), pTexture, pVB))
        return;

    g_pd3dDevice->SetIndices(pIB);
    g_pd3dDevice->DrawIndexedPrimitive(primitiveType, 0, 0, numberVertices, 0, primCount);
}

// ���ؽ� ������
void RenderVertices(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB, D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT primCount)
{
    if (!RenderCommon(pTm, radius, pTexture, pVB))
        return;

    g_pd3dDevice->DrawPrimitive(primitiveType, startVertex, primCount);
}

// ������ ���� �κ�
BOOL RenderCommon(D3DXMATRIX* pTm, FLOAT radius, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DVERTEXBUFFER9 pVB)
{
    if (!IsSphereInFrustumPlane({ pTm->_41, pTm->_42,pTm->_43 }, radius, frustumPlane)) // ����ü �ø�
        return FALSE;

    g_pd3dDevice->SetTexture(0, pTexture);
    g_pd3dDevice->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
    g_pd3dDevice->SetTransform(D3DTS_WORLD, pTm);
    return TRUE;
}

// ������ ������
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

// ������ ���� ����
void SetBilboardAngle(D3DXVECTOR3* v3BilboardX, D3DXVECTOR3* v3BilboardZ, D3DXVECTOR3 v3LookAt, D3DXVECTOR3 v3Eye)
{
    D3DXVECTOR3 v3CameraFront = v3Eye - v3LookAt;

    D3DXVec3Cross(v3BilboardX, &v3CameraFront, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    D3DXVec3Normalize(v3BilboardX, v3BilboardX);

    D3DXVec3Cross(v3BilboardZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), v3BilboardX);
    D3DXVec3Normalize(v3BilboardZ, v3BilboardZ);
}

// �� �׸���
void RenderEnemys(D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ)
{
    int enemy1NumberVertices = sizeof(enemy1Vertices) / sizeof(enemy1Vertices[0]);
    int enemy1PrimCount = sizeof(enemy1Indices) / sizeof(enemy1Indices[0]);

    for (int enemyCount = 0; enemyCount < ENEMY_MAX; enemyCount++)
    {
        if (enemyObj[enemyCount] == NULL)
            continue;

        RenderIndices(enemyObj[enemyCount], g_pTEXTURE_Array[TEXTURE_ENEMY_TURTLE], g_pVB_Array[VB_ENEMY1], g_pIB_Array[IB_ENEMY1], D3DPT_TRIANGLELIST, enemy1NumberVertices, enemy1PrimCount);

        // ü�� ������
        VOID* pVertices;
        g_pVB_Array[VB_ENEMYHPBAR]->Lock(0, sizeof(enemyHpBarVertices), (void**)&pVertices, 0);   // Lock(lock�� ������, ũ��, ������ �ּ�, 0)
        enemyHpBarVertices[5].position.x = enemyHpBarVertices[6].position.x = enemyObj[enemyCount]->GetNowHpRate() - 0.5f;
        memcpy(pVertices, enemyHpBarVertices, sizeof(enemyHpBarVertices));              // ���ۿ� ���� �ִ´�
        g_pVB_Array[VB_ENEMYHPBAR]->Unlock();

        RenderBilboard(&enemyObj[enemyCount]->GetHpBarMatrix(), enemyObj[enemyCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_HPBAR_RED], g_pVB_Array[VB_ENEMYHPBAR], v3BilboardX, v3BilboardZ, 0, D3DPT_TRIANGLEFAN);    // ü�°����� ����(����)
        RenderBilboard(&enemyObj[enemyCount]->GetHpBarMatrix(), enemyObj[enemyCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_HPBAR_GREEN], g_pVB_Array[VB_ENEMYHPBAR], v3BilboardX, v3BilboardZ, 4, D3DPT_TRIANGLEFAN);  // ü�°���ġ ���� ü��(�ʷ�)
    }
}

// �Ѿ� �׸���
void RenderBullets(CBullet** bullets, D3DXVECTOR3 v3BilboardX, D3DXVECTOR3 v3BilboardZ)
{
    for (int bulletCount = 0; bulletCount < BULLET_MAX; bulletCount++)
    {
        if (bullets[bulletCount] == NULL)
            continue;

        if (bullets[bulletCount]->GetFireSprite().GetIsPlaySprite())    // ���� �� �Ҳ� �׸�
            RenderBilboard(bullets[bulletCount]->GetMatrix(), bullets[bulletCount]->GetRadius(), g_pTEXTURE_Array[TEXTURE_FIRE], g_pVB_Array[VB_BULLETFIRE], v3BilboardX, v3BilboardZ, bullets[bulletCount]->GetFireSprite().GetNowTextureCount() * 4, D3DPT_TRIANGLEFAN);
        else                                                            // �����ϱ� ������ �Ѿ� �׸�
            RenderIndices(bullets[bulletCount], g_pTEXTURE_Array[TEXTURE_BULLETCOLOR], g_pVB_Array[VB_BULLET], g_pIB_Array[IB_BULLET], D3DPT_TRIANGLELIST, 12, 20);
    }
}


// ���� �׽�Ʈ (��� ��Ȳ���� �ڿ� �ִ� ���� �׸� �� ������ �������� �Ұ���,  ���� ���� or ������)
void _SetAlphaTest()
{
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);        // ���� ���� ����
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);          // ���� �׽�Ʈ �ѱ�
    g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);           // ���� �׽�Ʈ ����/������ ���ذ�
    g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);      // ���ذ����� ũ�� �׸���
}

// ���� ���� (������ ������ ���� �ڿ� �ִ� ���� �� ����)
void _SetAlphaBlend()
{
    g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);         // ���� �׽�Ʈ ����
    g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);         // ���� ���� �ѱ�
    g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    // �ҽ� ���� ����, ���� �׷��� �׸�
    g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// �ݴ� ���İ� ����, ���� �ִ� �׸�
}

// ���� ����
void _SetLight(D3DLIGHTTYPE lightType, D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DVECTOR position, D3DVECTOR direction, FLOAT range, FLOAT falloff, FLOAT theta, FLOAT phi, DWORD lightIndex)
{
    D3DLIGHT9 d3dLight;
    ZeroMemory(&d3dLight, sizeof(d3dLight));
    d3dLight.Type = lightType;

    d3dLight.Diffuse = diffuse;      // Ȯ�걤
    d3dLight.Ambient = ambient;      // �ֺ���
    d3dLight.Specular = specular;    // �ݻ籤

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

// ���� ����
void _SetMatrial(D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular, D3DCOLORVALUE emissive, FLOAT power)
{
    D3DMATERIAL9 d3dMaterial;
    ZeroMemory(&d3dMaterial, sizeof(d3dMaterial));
    d3dMaterial.Diffuse = diffuse;
    d3dMaterial.Ambient = ambient;
    d3dMaterial.Specular = specular;

    d3dMaterial.Emissive = emissive;  // ��ü�߱�
    //d3dMaterial.Power = power;        // Speculare�� �������� Power

    g_pd3dDevice->SetMaterial(&d3dMaterial);
}

// ����ü ��� ����
void SetFrustumPlane(D3DXMATRIX tempViewTM, D3DXMATRIX tempProjectionTM)
{
    D3DXMATRIX viewProjMatrix;
    D3DXMatrixMultiply(&viewProjMatrix, &tempViewTM, &tempProjectionTM);

    // ����� ������ ax + by + cz + d����
    // �������Ͱ� ���������϶� (a, b, c)�� �״�� ���� ���Ͱ� �ȴ�.

    // ����ü ����� ���� �迭
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

// ����ü �ø�
BOOL IsSphereInFrustumPlane(const D3DXVECTOR3& center, float radius, D3DXPLANE planes[6])
{
    if (!cullingOn)
        return true;

    for (int i = 0; i < 6; ++i)
    {
        float distance = planes[i].a * center.x + planes[i].b * center.y + planes[i].c * center.z + planes[i].d;
        if (distance < -radius)     return false;   // �Ÿ��� -���������� ������ ��� ��
    }
    return true;
}


// UI �׸���
void DrawUI(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    g_pd3dDevice->SetFVF(SCREEN_VERTEX::FVF);

    _SetAlphaBlend();   // ���� ���� (������ ������ ���� �ڿ� �ִ� ���� �� ����)

    switch (sceneState.nowSceneType)
    {
    case SCENE_SCORE:  DrawScoreScene(font);
    case SCENE_TITLE:  DrawTitleScene(font);                                    break;
    case SCENE_GAME:   DrawGameScene(font, pTextMetrics, dateInfo, sceneState); break;
    case SCENE_RESULT: DrawResultScene(font);                                   break;
    }
}

// UI
// Ÿ��Ʋ�� ���� â UI
void DrawScoreScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 16, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f,        HEIGHT_WINDOW / 10.0f, 0, 0, "����");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 2.0f, HEIGHT_WINDOW / 10.0f, 0, 0, "����");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 3.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "ų");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 4.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "�������");
    _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 6.5f, HEIGHT_WINDOW / 10.0f, 0, 0, "����Ͻ�");


    for (int i = 0; i < 10; i++)
    {
        if (!saveData[i].score)
            break;

        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f,        HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", i + 1);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 2.0f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", saveData[i].score);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 3.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d", saveData[i].killCount);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 4.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d�� %d��", saveData[i].aliveTime[0], saveData[i].aliveTime[1]);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 6.5f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d/%d/%d", saveData[i].realTime[0], saveData[i].realTime[1], saveData[i].realTime[2]);
        _drawText(font, FALSE, WIDTH_WINDOW / 20.0f * 8.2f, HEIGHT_WINDOW / 10.0f * (2.0f + i * 0.7f), 0, 0, "%d:%d", saveData[i].realTime[3], saveData[i].realTime[4]);
    }
}

// Ÿ��Ʋ UI
void DrawTitleScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, NULL);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices, sizeof(SCREEN_VERTEX));         // �� ����

    if (isBtnOnMouse[BUTTON_PLAY])  g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 4, sizeof(SCREEN_VERTEX));     // �÷��� ��ư

    if (isBtnOnMouse[BUTTON_SCORE]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 8, sizeof(SCREEN_VERTEX));     // ���� ��ư

    if (isBtnOnMouse[BUTTON_END]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_RED_ONMOUSE]);
    else                            g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_RED]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleSceneVertices + 12, sizeof(SCREEN_VERTEX));    // ���� ��ư

    _drawText(font, TRUE, titleSceneVertices[4].x, titleSceneVertices[4].y, titleSceneVertices[5].x, titleSceneVertices[7].y, "�÷���");
    _drawText(font, TRUE, titleSceneVertices[8].x, titleSceneVertices[8].y, titleSceneVertices[9].x, titleSceneVertices[11].y, "����");
    _drawText(font, TRUE, titleSceneVertices[12].x, titleSceneVertices[12].y, titleSceneVertices[13].x, titleSceneVertices[15].y, "����");
}

// ���Ӿ� UI
void DrawGameScene(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo, SceneState sceneState)
{
    for (int btnNum = 0; btnNum < 5; btnNum++)                  // ��ư �׸��� (����)
    {
        g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_PLAY + btnNum]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices + 4 * (btnNum + 1), sizeof(SCREEN_VERTEX));
    }

    DrawHelpWindow(sceneState, font, pTextMetrics, dateInfo);   // ���� �׸��� (�»��)
    DrawLevelUpUI(sceneState, font, pTextMetrics);              // ������ ���ʽ� ���� ȭ��
    DrawPlayerLvHpExp(font);                      // �÷��̾� ����, HP, ����ġ �׸��� (���ϴ�)
    DrawCrossCenterLine(sceneState);              // ���콺 ���ظ�� ���ڼ� �׸���
    DrawMenuUI(sceneState, font, pTextMetrics);   // �޴� UI
}

// ���â UI
void DrawResultScene(LPD3DXFONT font)
{
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, NULL);
    if (nowGameData[NOWGAME_RANKING] < 10)
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices + 8, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 1.75,  HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "����");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 2.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "����");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 3.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "ų");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 4.75f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "�������");
    _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 6.25f, HEIGHT_WINDOW / 10.0f * 1.5f, 0, 0, "����Ͻ�");

    for (int i = 0; i < 10; i++)
    {
        if (!saveData[i].score)
            break;

        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 1.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", i + 1);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 2.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", saveData[i].score);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 3.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d", saveData[i].killCount);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 4.75f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d ��  %d ��", saveData[i].aliveTime[0], saveData[i].aliveTime[1]);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 6.25f, HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d / %d / %d", saveData[i].realTime[0], saveData[i].realTime[1], saveData[i].realTime[2]);
        _drawText(font, FALSE, WIDTH_WINDOW / 10.0f * 7.5f,  HEIGHT_WINDOW / 10.0f * (2.2f + i * 0.6f), 0, 0, "%d : %d", saveData[i].realTime[3], saveData[i].realTime[4]);
    }

    if (isBtnOnMouse[BUTTON_TONEXT]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BROWN]); // �������� ��ư
    else                             g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BROWN_Light]);

    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, resultSceneVertices + 4, sizeof(SCREEN_VERTEX));
    _drawText(font, TRUE, resultSceneVertices[4].x, resultSceneVertices[4].y, resultSceneVertices[5].x, resultSceneVertices[7].y, "��������");
}


// ���� �׸���
void DrawHelpWindow(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo)
{
    RECT strRect;
    char str[64] = "";

    if (sceneState.openHelp)
    {
        g_pd3dDevice->SetTexture(0, NULL);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices, sizeof(SCREEN_VERTEX));
        DrawHelpTexts(font, pTextMetrics, dateInfo);   // ����
    }
    else
    {
        if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
            textColor = { 1.0f, 1.0f, 1.0f, 1.0f };

        _drawText(font, FALSE, 10, 12, 0, 0, "�Ͻ�: %d�� %d�� %d��   ", dateInfo.month, dateInfo.day, (int)dateInfo.clock);
        _drawText(font, FALSE, 10, 12 + pTextMetrics.tmHeight, 0, 0, "fps: %.2f", 1.0f / timer.GetDeltaTime());
        _drawText(font, FALSE, 10, 12 + pTextMetrics.tmHeight * 3, 0, 0, "[F1] ���� ����");
    }

    if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
        textColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    _drawText(font, FALSE, WIDTH_WINDOW * 0.35f, HEIGHT_WINDOW * 0.02f, 0, 0, "High Score: %d", nowGameData[NOWGAME_BESTSCORE]);
    _drawText(font, FALSE, WIDTH_WINDOW * 0.35f, HEIGHT_WINDOW * 0.02f + pTextMetrics.tmHeight, 0, 0, "Score: %d", nowGameData[NOWGAME_SCORE]);

    if (dateInfo.clock > 20.0f || dateInfo.clock < 4.0f)
        textColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

// ���� ����
void DrawHelpTexts(LPD3DXFONT font, TEXTMETRICA pTextMetrics, DateInfo dateInfo)
{
    RECT strRect;
    int textHeight = pTextMetrics.tmHeight;
    char* helpTexts[11] = { "�̵�: wasd / �����", "ȸ��: ���콺 �¿� ȸ��", "      ��Ŭ������ ȸ�� ����", "����: �����̽� ��", "1.ī�޶� ��ȯ    2.���� on/off", "3.������ on/off  4.�¾� on/off", 
        "TAB.���콺 ���� ��� ����", "ESC.�޴�         Q.����", "���� ��ư(���ʺ��� �������)", "    �ð� ���/����, ���� �ð�, ", "    ���� ��, ���� ��, �޴�" };

    if (font == NULL)
        return;

    for (int i = 0; i < 11; i++)
        _drawText(font, FALSE, 10, 12 + (textHeight + 1) * i, 0, 0, helpTexts[i]);

    _drawText(font, FALSE, 10, 12 + (textHeight + 1) * 11, 0, 0, "�Ͻ�: %d�� %d�� %d��   ", dateInfo.month, dateInfo.day, (int)dateInfo.clock);
    _drawText(font, FALSE, 10, 12 + (textHeight + 1) * 12, 0, 0, "fps: %.2f", 1.0f / timer.GetDeltaTime());
}

// ���ڼ� �׸���
void DrawCrossCenterLine(SceneState sceneState)
{
    if (sceneState.mouseCrossFocusMode)
    {
        g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_CROSSLINE]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameSceneVertices + 24, sizeof(SCREEN_VERTEX));
    }
}

// �÷��̾� ����, HP, ����ġ �׸��� (���ϴ�)
void DrawPlayerLvHpExp(LPD3DXFONT font)
{
    _SetAlphaBlend();

    // �÷��̾� ����
    g_pd3dDevice->SetTexture(0, NULL);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 16, sizeof(SCREEN_VERTEX));
    _drawText(font, FALSE, PLAYERHPMIN, (int)(HEIGHT_WINDOW / 8.0f * 6.25f), 0, 0, " Lv. %d", playerObj.GetLevel());

    // �÷��̾� ü��
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_HPBAR_RED]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_HPBAR_GREEN]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 4, sizeof(SCREEN_VERTEX));

    // �÷��̾� ����ġ
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_EXPBAR_GRAY]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 8, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_EXPBAR_BLUE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, playerHpExpBarVertices + 12, sizeof(SCREEN_VERTEX));

    _SetAlphaTest();
}

// �޴�â �׸���
void DrawMenuUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics)
{
    if (!sceneState.isOpenMenu)
        return;

    if (sceneState.isOpenMenu == 1) // ���ʿ� Ƣ��� �ִ� �÷��̾� ����
    {
        menuVertices[4].color = menuVertices[5].color = menuVertices[6].color = menuVertices[7].color = 0xbffffffff;
        menuVertices[8].color = menuVertices[9].color = menuVertices[10].color = menuVertices[11].color = 0xff909090;
    }
    else // ���ʿ� Ƣ��� �ִ� ����
    {
        menuVertices[4].color = menuVertices[5].color = menuVertices[6].color = menuVertices[7].color = 0xff909090;
        menuVertices[8].color = menuVertices[9].color = menuVertices[10].color = menuVertices[11].color = 0xffffffff;
    }

    _SetAlphaTest();
    // ��� ū �簢�� ���� ��׶���
    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BG]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices, sizeof(SCREEN_VERTEX));
    _SetAlphaBlend();

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_MENU_BTN]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 4, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 8, sizeof(SCREEN_VERTEX));

    _drawText(font, FALSE, (menuVertices[4].x + menuVertices[5].x) * 0.5f - pTextMetrics.tmAveCharWidth * 6, (menuVertices[4].y + menuVertices[7].y) * 0.5f - pTextMetrics.tmHeight * 0.5f, 0, 0, "�÷��̾� ����");
    _drawText(font, FALSE, (menuVertices[8].x + menuVertices[9].x) * 0.5f - pTextMetrics.tmAveCharWidth * 2, (menuVertices[8].y + menuVertices[11].y) * 0.5f - pTextMetrics.tmHeight * 0.5f, 0, 0, "����");


    if (sceneState.isOpenMenu == 1)         // ����
    {
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 4, 0, 0, "���� :  %d", playerObj.GetLevel());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 6, 0, 0, "ü�� :  %d / %d", playerObj.GetHpNow(), playerObj.GetHpMax());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 8, 0, 0, "����ġ :  %d / %d", playerObj.GetNowExp(), playerObj.GetLevelUpExp());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 12, 0, 0, "�̵��ӵ� :  %.2f", playerObj.GetMoveSpeed());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 14, 0, 0, "���ݷ� :  %d", playerObj.GetAttackDamage());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 16, 0, 0, "���� ������ :  %.2f", playerObj.GetAttackDelay());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 18, 0, 0, "�ڿ� ȸ���� :  %d", playerObj.GetHpRecoveryRate());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 20, 0, 0, "�ڿ� ȸ�� ������ :  %.2f", playerObj.GetHpRecoveryDelay());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 22, 0, 0, "����ġ ȹ�� ���� :  %.2f", playerObj.GetExpBonusRate());
        _drawText(font, FALSE, menuVertices[0].x + pTextMetrics.tmAveCharWidth * 10, menuVertices[0].y + pTextMetrics.tmHeight * 25, 0, 0, "�Ѿ� �л� :  %d     �Ѿ� ���� :  %d      �� ū �Ѿ� :  %d", playerObj.GetAttackSpreadLevel(), playerObj.GetAttackBurstLevel(), playerObj.GetBulletSizeLevel());
    }
    else if (sceneState.isOpenMenu == 2)    // ����
    {
        // �����̴�
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 0);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 20);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 40);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 60);
        DrawSliderHorizontal(g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_GRAY], g_pTEXTURE_Array[TEXTURE_SLIDER_HORIZONTAL_BLUE], g_pTEXTURE_Array[TEXTURE_SLIDER_HANDLE], 80);

        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5].x) * 0.4f, menuSliderVertices[5].y, 0, 0, "�þ߰�");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 20].x) * 0.4f, menuSliderVertices[5 + 20].y, 0, 0, "�þ� ����");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 40].x) * 0.4f, menuSliderVertices[5 + 40].y, 0, 0, "���콺 ȸ�� ����");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 60].x) * 0.4f, menuSliderVertices[5 + 60].y, 0, 0, "BGM");
        _drawText(font, FALSE, (menuVertices[0].x + menuSliderVertices[5 + 80].x) * 0.4f, menuSliderVertices[5 + 80].y, 0, 0, "SE");

        // Ÿ��Ʋ�� ��ư
        if (isBtnOnMouse[BUTTON_TOTITLE]) g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE_ONMOUSE]);
        else                              g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_BUTTON_BLUE]);
        g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, menuVertices + 12, sizeof(SCREEN_VERTEX));
        _drawText(font, TRUE, menuVertices[12].x, menuVertices[12].y, menuVertices[13].x, menuVertices[15].y, "Ÿ��Ʋ ȭ������");

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

// ������ ���ʽ� ���� ȭ��
void DrawLevelUpUI(SceneState sceneState, LPD3DXFONT font, TEXTMETRICA pTextMetrics)
{
    if (!sceneState.onLevelUpScreen)
        return;

    _SetAlphaTest();

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_LVUP_BG_BROWN]);  // ���� �κ�
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices, sizeof(SCREEN_VERTEX));

    g_pd3dDevice->SetTexture(0, g_pTEXTURE_Array[TEXTURE_LVUP_BG_WHITE]);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 4, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 8, sizeof(SCREEN_VERTEX));
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, levelUpScreenVertices + 12, sizeof(SCREEN_VERTEX));

    //_drawText(font, TRUE, levelUpScreenVertices[16].x, levelUpScreenVertices[16].y, levelUpScreenVertices[18].x, levelUpScreenVertices[18].y, "Level Up Bonus Card");


    for (int lvUpCard = 0; lvUpCard < 3; lvUpCard++)    // ������ ���ʽ� ī�� 3��
    {
        char lvUpCardTexts[4][32] = { "", "", "", "" };
        char lvUpCardEffectNum[32] = "";

        switch (playerObj.GetLevelUpBonusNum()[lvUpCard])
        {
        case HP_MAX_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "�ִ� ü�� ����", "�÷��̾���", "�ִ� ü����", "20 �����Ѵ�");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetHpMax(), playerObj.GetHpMax() + 20);
            break;

        case HP_RECOVER_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "ü�� ȸ���� ����", "�÷��̾���", "ȸ�� �ֱⰡ ª������", "ȸ������ 2 �����Ѵ�");
            sprintf_s(lvUpCardEffectNum, "%d -> %d,  %.2f -> %.2f", playerObj.GetHpRecoveryRate(), playerObj.GetHpRecoveryRate() + 2, playerObj.GetHpRecoveryDelay(), playerObj.GetHpRecoveryDelay() * 0.95f);
            break;

        case MOVE_SPEED_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "�̵� �ӵ� ����", "�÷��̾���", "�̵� �ӵ���", "�����Ѵ�");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetMoveSpeed(), playerObj.GetMoveSpeed() + 0.2f);
            break;

        case ATTACK_DAMAGE_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "���ݷ� ����", "�÷��̾���", "���� ��������", "2 �����Ѵ�");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackDamage(), playerObj.GetAttackDamage() + 2);
            break;

        case ATTACK_SPEED_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "���� �ӵ� ����", "�÷��̾���", "���� �����̰�", "ª������");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetAttackDelay(), playerObj.GetAttackDelay() * 0.95f);
            break;

        case GET_EXP_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "ȹ�� ����ġ ����", "�÷��̾���", "ȹ�� ����ġ ������", "1.1�� �����Ѵ�");
            sprintf_s(lvUpCardEffectNum, "%.2f -> %.2f", playerObj.GetExpBonusRate(), playerObj.GetExpBonusRate() + 0.1f);
            break;

        case BULLET_SPREAD_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "�Ѿ� �л�", "�Ѿ��� ������ŭ", "������ �۶߷��� �߻�", " +1");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackSpreadLevel(), playerObj.GetAttackSpreadLevel() + 1);
            if (playerObj.GetAttackSpreadLevel() >= SPREADLEVELMAX) sprintf_s(lvUpCardEffectNum, "%d (Level MAX)", playerObj.GetAttackSpreadLevel());
            break;

        case BULLET_BURST_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "�Ѿ� ����", "�Ѿ��� ������ŭ", "���޾� �߻�", " +1");
            sprintf_s(lvUpCardEffectNum, "%d -> %d", playerObj.GetAttackBurstLevel(), playerObj.GetAttackBurstLevel() + 1);
            if (playerObj.GetAttackBurstLevel() >= BURSTLEVELMAX)  sprintf_s(lvUpCardEffectNum, "%d (Level MAX)", playerObj.GetAttackBurstLevel());
            break;

        case BULLET_SIZE_UP:
            SetLevelUpBonusCardTexts(lvUpCardTexts, "�� ū �Ѿ�", "�Ѿ��� Ŀ����", "�������� �����Ѵ�", "ũ�� +10%, ������ +20%");
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

// ������ ī�� ����
void SetLevelUpBonusCardTexts(char lvUpCardTexts[5][32], char* cardName, char* cardEffect1, char* cardEffect2, char* cardEffect3)
{
    strcat_s(lvUpCardTexts[0], cardName);
    strcat_s(lvUpCardTexts[1], cardEffect1);
    strcat_s(lvUpCardTexts[2], cardEffect2);
    strcat_s(lvUpCardTexts[3], cardEffect3);
}

// �����̴� �׸���
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