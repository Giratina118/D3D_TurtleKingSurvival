#include "_VertexData.h"

DWORD SCREEN_VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
DWORD CUSTOMVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

FLOAT buttonSize = WIDTH_WINDOW / 12.0f;

// 2D UI

// Ÿ��Ʋ�� ����
SCREEN_VERTEX titleSceneVertices[] =
{
    { WIDTH_WINDOW * 0.6f,  0.0f,                    0.4f, 1.0f,    0x80909090, 0.0f, 0.0f },   // UI ����
    { WIDTH_WINDOW,         0.0f,                    0.4f, 1.0f,    0x80909090, 1.0f, 0.0f },
    { WIDTH_WINDOW,         HEIGHT_WINDOW,           0.4f, 1.0f,    0x80909090, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.6f,  HEIGHT_WINDOW,           0.4f, 1.0f,    0x80909090, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ���� ��ư
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.4375f, 0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ���� ��ư
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.4375f, 0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.5625f, 0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.5625f, 0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.625f,  0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ���� ��ư
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.625f,  0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.75f,   0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.75f,   0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },
    

    { 0.0f,                0.0f,                  0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // Ÿ��Ʋ ����ȭ�� ����
    { WIDTH_WINDOW * 0.5f, 0.0f,                  0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.5f, HEIGHT_WINDOW * 0.95f, 0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { 0.0f,                HEIGHT_WINDOW * 0.95f, 0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },
};

// ����� ����
SCREEN_VERTEX resultSceneVertices[] =
{
    { WIDTH_WINDOW * 0.125f, HEIGHT_WINDOW * 0.1f,  0.4f, 1.0f,     0xb0ffffff, 0.0f, 0.0f },   // UI ����
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.1f,  0.4f, 1.0f,     0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.125f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.35f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // Ÿ��Ʋ�� ��ư
    { WIDTH_WINDOW * 0.65f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.65f,  HEIGHT_WINDOW * 0.9375f, 0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.35f,  HEIGHT_WINDOW * 0.9375f, 0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ff0000, 0.0f, 0.0f },   // ���� ����
    { WIDTH_WINDOW * 0.85f,  HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ff0000, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.85f,  HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ff0000, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ff0000, 0.0f, 1.0f },
};

// ���Ӿ� ����
SCREEN_VERTEX gameSceneVertices[] =
{
    { 5.0f,                  10.0f,                  0.5f, 1.0f,    0x90ffffff, 0.0f, 0.0f },   // �»�� ����
    { WIDTH_WINDOW * 0.275f, 10.0f,                  0.5f, 1.0f,    0x90ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.275f, HEIGHT_WINDOW * 0.375f, 0.5f, 1.0f,    0x90ffffff, 1.0f, 1.0f },
    { 5.0f,                  HEIGHT_WINDOW * 0.375f, 0.5f, 1.0f,    0x90ffffff, 0.0f, 1.0f },

    // ���� ��ư
    { WIDTH_WINDOW - buttonSize * 5.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ��    ���/����
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 5.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >    ���� �ð�
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >>   ���� ��
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >>>  ���� ��
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ��    �޴�
    { WIDTH_WINDOW - buttonSize * 0.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 0.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    
    { WIDTH_WINDOW * 0.468f, HEIGHT_WINDOW * 0.5f - WIDTH_WINDOW * 0.042f, 0.5f, 1.0f,  0xffffffff, 0.0f, 0.0f },   // ���� ������
    { WIDTH_WINDOW * 0.518f, HEIGHT_WINDOW * 0.5f - WIDTH_WINDOW * 0.042f, 0.5f, 1.0f,  0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.518f, HEIGHT_WINDOW * 0.5f + WIDTH_WINDOW * 0.008f, 0.5f, 1.0f,  0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.468f, HEIGHT_WINDOW * 0.5f + WIDTH_WINDOW * 0.008f, 0.5f, 1.0f,  0xffffffff, 0.0f, 1.0f },
};

// �޴� UI
SCREEN_VERTEX menuVertices[] =
{
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 0.0f },   // UI ����
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 0.0f },   // ���� �ɷ�
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // ����
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },


    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.8f,    0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // Ÿ��Ʋ�� ��ư
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.8f,    0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.9f,    0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.9f,    0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },


    // FPS ����
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.2f,    0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // ����
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.2f,    0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.25f,   0.1f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 30
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.25f,   0.1f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.3f,    0.1f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.3f,    0.1f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.3f,    0.1f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 45
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.3f,    0.1f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.35f,   0.1f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.35f,   0.1f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.35f,   0.1f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 60
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.35f,   0.1f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.4f,    0.1f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.4f,    0.1f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.4f,    0.1f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 90
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.4f,    0.1f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.45f,   0.1f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.45f,   0.1f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.45f,   0.1f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 120
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.45f,   0.1f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.5f,    0.1f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.5f,    0.1f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.375f, HEIGHT_WINDOW * 0.215f,  0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // FPS ���� ��ġ
};

// �޴� �����̴� ����
SCREEN_VERTEX menuSliderVertices[] =
{
    // �����̴� 1 (�þ߰�)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // ȸ��(�����̴� �� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ���� ��)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ������ ��)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // �Ķ���(�����̴� ä���� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.2875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // �����̴� ������
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.2875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // �����̴� 2 (�þ߹���)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // ȸ��(�����̴� �� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ���� ��)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ������ ��)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // �Ķ���(�����̴� ä���� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // �����̴� ������
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // �����̴� 3 (���콺 ȸ�� ����)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // ȸ��(�����̴� �� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ���� ��)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ������ ��)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // �Ķ���(�����̴� ä���� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // �����̴� ������
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },


    // �����̴� 3 (����� ����)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // ȸ��(�����̴� �� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ���� ��)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ������ ��)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // �Ķ���(�����̴� ä���� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // �����̴� ������
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // �����̴� 3 (���콺 ȸ�� ����)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // ȸ��(�����̴� �� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ���� ��)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // ȸ��/�Ķ���(�����̴� �� ����, ������ ��)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // �Ķ���(�����̴� ä���� ����, �߾� ����)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // �����̴� ������
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.7625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

};

// �÷��̾� ü�¹�, ����ġ��
SCREEN_VERTEX playerHpExpBarVertices[] =
{
    // ü�� ������
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.8125f, 0.8f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // �ִ� ü�� ������ (����)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.8125f, 0.8f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    { PLAYERHPMIN, HEIGHT_WINDOW * 0.8125f, 0.7f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // ���� ü�� ������ (�ʷ�)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.8125f, 0.7f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    // ����ġ ������
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // ����ġ ���� (ȸ��)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.9375f, 0.8f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.9375f, 0.8f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // ���� ����ġ ������ (�Ķ�)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.9375f, 0.7f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.9375f, 0.7f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    // ü�� ������ �� ���� ǥ��
    { PLAYERHPMIN,         HEIGHT_WINDOW * 0.7625f, 0.6f, 1.0f,     0x906181df, 0.0f, 0.0f },
    { PLAYERHPMAX * 0.35f, HEIGHT_WINDOW * 0.7625f, 0.6f, 1.0f,     0x906181df, 1.0f, 0.0f },
    { PLAYERHPMAX * 0.4f,  HEIGHT_WINDOW * 0.8125f, 0.6f, 1.0f,     0x906181df, 1.0f, 1.0f },
    { PLAYERHPMIN,         HEIGHT_WINDOW * 0.8125f, 0.6f, 1.0f,     0x906181df, 0.0f, 1.0f },
};

// ������ â
SCREEN_VERTEX levelUpScreenVertices[] =
{
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // UI ����
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // ù ��° ����
    { WIDTH_WINDOW * 0.37f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.37f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.38f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // �� ��° ����
    { WIDTH_WINDOW * 0.595f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.595f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.38f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.605f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // �� ��° ����
    { WIDTH_WINDOW * 0.825f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.825f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.605f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.33f,  HEIGHT_WINDOW * 0.175f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // Ÿ��Ʋ
    { WIDTH_WINDOW * 0.645f, HEIGHT_WINDOW * 0.175f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.645f, HEIGHT_WINDOW * 0.3f,    0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.33f,  HEIGHT_WINDOW * 0.3f,    0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },
};


// ������ü ����
D3DXVECTOR3 cubePoint[] =
{
    { -GROUND_RADIUS,  GROUND_RADIUS, -GROUND_RADIUS }, // �ո� �»�
    {  GROUND_RADIUS,  GROUND_RADIUS, -GROUND_RADIUS }, // �ո� ���
    {  GROUND_RADIUS, -GROUND_RADIUS, -GROUND_RADIUS }, // �ո� ����
    { -GROUND_RADIUS, -GROUND_RADIUS, -GROUND_RADIUS }, // �ո� ����

    { -GROUND_RADIUS,  GROUND_RADIUS,  GROUND_RADIUS }, // �޸� �»�
    {  GROUND_RADIUS,  GROUND_RADIUS,  GROUND_RADIUS }, // �޸� ���
    {  GROUND_RADIUS, -GROUND_RADIUS,  GROUND_RADIUS }, // �޸� ����
    { -GROUND_RADIUS, -GROUND_RADIUS,  GROUND_RADIUS }  // �޸� ����
};

// ������ü ��������
D3DXVECTOR3 cubeNormal[] =
{
    {  1.0f,  0.0f,  0.0f },    // x+
    { -1.0f,  0.0f,  0.0f },    // x-
    {  0.0f,  1.0f,  0.0f },    // y+
    {  0.0f, -1.0f,  0.0f },    // y-
    {  0.0f,  0.0f,  1.0f },    // z+
    {  0.0f,  0.0f, -1.0f }     // z-
};

// ������ü ����
CUSTOMVERTEX cubeVertices[] =
{
    // ������ü
    { cubePoint[0], cubeNormal[5], 0.0f, 0.0f },    // �ո�
    { cubePoint[1], cubeNormal[5], 1.0f, 0.0f },
    { cubePoint[2], cubeNormal[5], 1.0f, 1.0f },
    { cubePoint[3], cubeNormal[5], 0.0f, 1.0f },

    { cubePoint[5], cubeNormal[4], 0.0f, 0.0f },    // �޸�
    { cubePoint[4], cubeNormal[4], 1.0f, 0.0f },
    { cubePoint[7], cubeNormal[4], 1.0f, 1.0f },
    { cubePoint[6], cubeNormal[4], 0.0f, 1.0f },

    { cubePoint[4], cubeNormal[2], 0.0f, 0.0f },    // ����
    { cubePoint[5], cubeNormal[2], 1.0f, 0.0f },
    { cubePoint[1], cubeNormal[2], 1.0f, 1.0f },
    { cubePoint[0], cubeNormal[2], 0.0f, 1.0f },

    { cubePoint[3], cubeNormal[3], 0.0f, 0.0f },    // �Ʒ���
    { cubePoint[2], cubeNormal[3], 1.0f, 0.0f },
    { cubePoint[6], cubeNormal[3], 1.0f, 1.0f },
    { cubePoint[7], cubeNormal[3], 0.0f, 1.0f },

    { cubePoint[1], cubeNormal[0], 0.0f, 0.0f },    // ������
    { cubePoint[5], cubeNormal[0], 1.0f, 0.0f },
    { cubePoint[6], cubeNormal[0], 1.0f, 1.0f },
    { cubePoint[2], cubeNormal[0], 0.0f, 1.0f },

    { cubePoint[4], cubeNormal[1], 0.0f, 0.0f },    // �޸�
    { cubePoint[0], cubeNormal[1], 1.0f, 0.0f },
    { cubePoint[3], cubeNormal[1], 1.0f, 1.0f },
    { cubePoint[7], cubeNormal[1], 0.0f, 1.0f },
};

// ������ü �ε���
CUSTOMINDEX_LIST cubeIndices[] =
{
    { 0, 1, 2 },    { 0, 2, 3 },
    { 4, 5, 6 },    { 4, 6, 7 },
    { 8, 9, 10 },   { 8, 10, 11 },
    { 12, 13, 14 }, { 12, 14, 15 },
    { 16, 17, 18 }, { 16, 18, 19 },
    { 20, 21, 22 }, { 20, 22, 23 }
};


// �ܵ� ����
CUSTOMVERTEX groundVertices[] =
{
    { { -GROUND_RADIUS, 0.0f,  GROUND_RADIUS }, cubeNormal[2], 0.0f, 0.0f },    // ����
    { {  GROUND_RADIUS, 0.0f,  GROUND_RADIUS }, cubeNormal[2], 1.0f, 0.0f },
    { {  GROUND_RADIUS, 0.0f, -GROUND_RADIUS }, cubeNormal[2], 1.0f, 1.0f },
    { { -GROUND_RADIUS, 0.0f, -GROUND_RADIUS }, cubeNormal[2], 0.0f, 1.0f }
};

// ������
CUSTOMVERTEX bliboardVertices[] =
{
    // ����
    { { -3.0f,  4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.0f },
    { {  3.0f,  4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.0f },
    { {  3.0f, -4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 1.0f },
    { { -3.0f, -4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 1.0f },

    // ����
    { { -5.0f,  2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   0.0f, 0.0f },
    { {  5.0f,  2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   1.0f, 0.0f },
    { {  5.0f, -2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   1.0f, 1.0f },
    { { -5.0f, -2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   0.0f, 1.0f },
};

// �� ü�¹� (������)
CUSTOMVERTEX enemyHpBarVertices[] =
{
    // �ִ� ü�� ������ (����)
    { { -0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },
    { {  0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    // ���� ü�� ������ (�ʷ�)
    { { -0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },
    { {  0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },
};

// ��������Ʈ ����
CUSTOMVERTEX spriteVertices[] =
{
    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.0f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.0f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.25f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.25f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.0f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.0f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.25f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.25f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.0f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.0f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.25f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.25f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.0f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.0f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.25f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.25f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.0f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.0f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.25f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.25f },


    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.25f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.25f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.5f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.5f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.25f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.25f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.5f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.5f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.25f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.25f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.5f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.5f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.25f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.25f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.5f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.5f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.25f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.25f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.5f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.5f  },


    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.5f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.5f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.75f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.75f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.5f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.5f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.75f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.75f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.5f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.5f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.75f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.75f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.5f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.5f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.75f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.75f },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.5f  },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.5f  },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.75f },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.75f },


    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.75f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.75f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 1.0f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 1.0f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 0.75f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.75f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 1.0f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.2f, 1.0f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 0.75f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.75f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 1.0f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.4f, 1.0f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 0.75f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.75f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 1.0f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.6f, 1.0f  },

    { { -0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 0.75f },
    { {  0.5f,  0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.75f },
    { {  0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 1.0f  },
    { { -0.5f, -0.5f, 1.0f },   { 0.0f, 1.0f, 1.0f },   0.8f, 1.0f  },
};


// ��ī�̹ڽ� ����
CUSTOMVERTEX skyBoxVertices[] =
{
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // ������(x+)
    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // ������(x-)
    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // ����(y+)
    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // �Ʒ���(y-)
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // �ո�(z+)
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // �޸�(z-)
    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },
};


FLOAT pixel_128 = 1.0f / 128.0f;
FLOAT pixel_64 = 1.0f / 64.0f;

// ��1 ����
CUSTOMVERTEX enemy1Vertices[] =
{
    // ����
    { { 0.5f, 0.25f, -0.75f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 6.0f,  pixel_64 * 63.0f },  // ������(x+)
    { { 0.5f, 0.25f, 0.5f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 6.0f,  pixel_64 * 43.0f },
    { { 0.5f, -0.6f, 0.5f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 12.0f, pixel_64 * 43.0f },
    { { 0.5f, -0.6f, -0.75f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 12.0f, pixel_64 * 63.0f },

    { { -0.5f, 0.25f, 0.5f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 37.0f, pixel_64 * 43.0f },  // ������(x-)
    { { -0.5f, 0.25f, -0.75f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 37.0f, pixel_64 * 63.0f },
    { { -0.5f, -0.6f, -0.75f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 63.0f },
    { { -0.5f, -0.6f, 0.5f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 43.0f },

    { { -0.5f, 0.25f, 0.5f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 37.0f, pixel_64 * 43.0f },  // ����(y+)
    { { 0.5f, 0.25f, 0.5f },    { 0.0f, 1.0f, 0.0f },   pixel_128 * 56.0f, pixel_64 * 43.0f },
    { { 0.5f, 0.25f, -0.75f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 56.0f, pixel_64 * 63.0f },
    { { -0.5f, 0.25f, -0.75f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 37.0f, pixel_64 * 63.0f },

    { { 0.5f, -0.6f, 0.5f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 30.0f, pixel_64 * 4.0f  },  // �Ʒ���(y-)
    { { -0.5f, -0.6f, 0.5f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 47.0f, pixel_64 * 4.0f  },
    { { -0.5f, -0.6f, -0.75f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 47.0f, pixel_64 * 22.0f },
    { { 0.5f, -0.6f, -0.75f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 30.0f, pixel_64 * 22.0f },

    { { 0.5f, 0.25f, 0.5f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 12.0f, pixel_64 * 37.0f },  // �ո�(z+)
    { { -0.5f, 0.25f, 0.5f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 37.0f },
    { { -0.5f, -0.6f, 0.5f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 44.0f },
    { { 0.5f, -0.6f, 0.5f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 12.0f, pixel_64 * 44.0f },

    { { -0.5f, 0.25f, -0.75f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 37.0f },  // �޸�(z-)
    { { 0.5f, 0.25f, -0.75f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 50.0f, pixel_64 * 37.0f },
    { { 0.5f, -0.6f, -0.75f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 50.0f, pixel_64 * 44.0f },
    { { -0.5f, -0.6f, -0.75f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 44.0f },
    

    // ��
    { { 0.35f, 0.15f, 0.5f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 2.0f,  pixel_64 * 6.0f  },  // ������(x+)
    { { 0.35f, 0.15f, 1.0f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },
    { { 0.35f, -0.35f, 1.0f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 11.0f },
    { { 0.35f, -0.35f, 0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 2.0f,  pixel_64 * 11.0f },

    { { -0.35f, 0.15f, 1.0f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 6.0f  },  // ������(x-)
    { { -0.35f, 0.15f, 0.5f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 6.0f  },
    { { -0.35f, -0.35f, 0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 11.0f },
    { { -0.35f, -0.35f, 1.0f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 11.0f },

    { { -0.35f, 0.15f, 1.0f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 0.0f  },  // ����(y+)
    { { 0.35f, 0.15f, 1.0f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 14.0f, pixel_64 * 0.0f  },
    { { 0.35f, 0.15f, 0.5f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 14.0f, pixel_64 * 6.0f  },
    { { -0.35f, 0.15f, 0.5f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },

    { { 0.35f, -0.35f, 1.0f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 0.0f  },  // �Ʒ���(y-)
    { { -0.35f, -0.35f, 1.0f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 0.0f  },
    { { -0.35f, -0.35f, 0.5f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 6.0f  },
    { { 0.35f, -0.35f, 0.5f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 6.0f  },

    { { 0.35f, 0.15f, 1.0f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },  // �ո�(z+)
    { { -0.35f, 0.15f, 1.0f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 14.0f, pixel_64 * 6.0f  },
    { { -0.35f, -0.35f, 1.0f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 14.0f, pixel_64 * 11.0f },
    { { 0.35f, -0.35f, 1.0f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 8.0f,  pixel_64 * 11.0f },


    // ����
    { { 0.25f, 0.75f, -0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 16.0f },  // ������(x+)
    { { 0.25f, 0.75f, 0.9f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },
    { { 0.25f, 0.25f, 0.9f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.25f, -0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 8.0f  },

    { { -0.25f, 0.75f, 0.9f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 8.0f  },  // ������(x-)
    { { -0.25f, 0.75f, -0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.25f, -0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },
    { { -0.25f, 0.25f, 0.9f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 16.0f },

    { { -0.25f, 0.75f, 0.9f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },  // ����(y+)
    { { 0.25f, 0.75f, 0.9f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.75f, -0.5f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.75f, -0.5f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 16.0f },

    { { 0.25f, 0.25f, 0.9f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 16.0f },  // �Ʒ���(y-)
    { { -0.25f, 0.25f, 0.9f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.25f, -0.5f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.25f, -0.5f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },

    { { 0.25f, 0.75f, 0.9f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },  // �ո�(z+)
    { { -0.25f, 0.75f, 0.9f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 77.0f, pixel_64 * 16.0f },
    { { -0.25f, 0.25f, 0.9f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 77.0f, pixel_64 * 24.0f },
    { { 0.25f, 0.25f, 0.9f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 69.0f, pixel_64 * 24.0f },

    { { -0.25f, 0.75f, -0.5f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 83.0f, pixel_64 * 16.0f },  // �޸�(z-)
    { { 0.25f, 0.75f, -0.5f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },
    { { 0.25f, 0.25f, -0.5f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 91.0f, pixel_64 * 24.0f },
    { { -0.25f, 0.25f, -0.5f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 83.0f, pixel_64 * 24.0f },


    // �ٸ� (���� �չ�)
    { { -0.4f, -0.25f, 0.1f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // ������(x+)
    { { -0.4f, -0.25f, 0.4f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, 0.4f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, 0.1f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, 0.4f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // ������(x-)
    { { -0.7f, -0.25f, 0.1f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, 0.1f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, 0.4f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, 0.4f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // ����(y+)
    { { -0.4f, -0.25f, 0.4f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { -0.4f, -0.25f, 0.1f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { -0.7f, -0.25f, 0.1f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { -0.4f, -1.0f, 0.4f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // �Ʒ���(y-)
    { { -0.7f, -1.0f, 0.4f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { -0.7f, -1.0f, 0.1f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { -0.4f, -1.0f, 0.1f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { -0.4f, -0.25f, 0.4f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // �ո�(z+)
    { { -0.7f, -0.25f, 0.4f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { -0.7f, -0.25f, 0.1f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // �޸�(z-)
    { { -0.4f, -0.25f, 0.1f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    // �ٸ� (������ �չ�)
    { { 0.7f, -0.25f, 0.1f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // ������(x+)
    { { 0.7f, -0.25f, 0.4f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, 0.4f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, 0.1f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, 0.4f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // ������(x-)
    { { 0.4f, -0.25f, 0.1f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, 0.1f },    { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, 0.4f },    { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, 0.4f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // ����(y+)
    { { 0.7f, -0.25f, 0.4f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { 0.7f, -0.25f, 0.1f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { 0.4f, -0.25f, 0.1f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { 0.7f, -1.0f, 0.4f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // �Ʒ���(y-)
    { { 0.4f, -1.0f, 0.4f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { 0.4f, -1.0f, 0.1f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { 0.7f, -1.0f, 0.1f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { 0.7f, -0.25f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // �ո�(z+)
    { { 0.4f, -0.25f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, 0.4f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, 0.4f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { 0.4f, -0.25f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // �޸�(z-)
    { { 0.7f, -0.25f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, 0.1f },    { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, 0.1f },    { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    // �ٸ� (���� �޹�)
    { { -0.4f, -0.25f, -0.65f }, { 1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // ������(x+)
    { { -0.4f, -0.25f, -0.35f }, { 1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, -0.35f },  { 1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, -0.65f },  { 1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, -0.35f }, { -1.0f, 0.0f, 0.0f }, pixel_128 * 44.0f, pixel_64 * 25.0f },  // ������(x-)
    { { -0.7f, -0.25f, -0.65f }, { -1.0f, 0.0f, 0.0f }, pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, -0.65f },  { -1.0f, 0.0f, 0.0f }, pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, -0.35f },  { -1.0f, 0.0f, 0.0f }, pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 10.0f, pixel_64 * 23.0f },  // ����(y+)
    { { -0.4f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { -0.4f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { -0.7f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { -0.4f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 52.0f, pixel_64 * 29.0f },  // �Ʒ���(y-)
    { { -0.7f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { -0.7f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { -0.4f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { -0.4f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // �ո�(z+)
    { { -0.7f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { -0.7f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f }, pixel_128 * 31.0f, pixel_64 * 36.0f },  // �޸�(z-)
    { { -0.4f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f }, pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f }, pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f }, pixel_128 * 44.0f, pixel_64 * 36.0f },

    // �ٸ� (������ �޹�)
    { { 0.7f, -0.25f, -0.65f }, { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // ������(x+)
    { { 0.7f, -0.25f, -0.35f }, { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, -0.35f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, -0.65f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, -0.35f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // ������(x-)
    { { 0.4f, -0.25f, -0.65f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, -0.65f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, -0.35f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // ����(y+)
    { { 0.7f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { 0.7f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { 0.4f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { 0.7f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // �Ʒ���(y-)
    { { 0.4f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { 0.4f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { 0.7f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { 0.7f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // �ո�(z+)
    { { 0.4f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { 0.4f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // �޸�(z-)
    { { 0.7f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },
};

// ��1 �ε���
CUSTOMINDEX_LIST enemy1Indices[] =
{
    { 0, 1, 2 },    { 0, 2, 3 },            // ����
    { 4, 5, 6 },    { 4, 6, 7 },
    { 8, 9, 10 },   { 8, 10, 11 },
    { 12, 13, 14 }, { 12, 14, 15 },
    { 16, 17, 18 }, { 16, 18, 19 },
    { 20, 21, 22 }, { 20, 22, 23 },

    { 24, 25, 26 }, { 24, 26, 27 },         // ��
    { 28, 29, 30 }, { 28, 30, 31 },
    { 32, 33, 34 }, { 32, 34, 35 },
    { 36, 37, 38 }, { 36, 38, 39 },
    { 40, 41, 42 }, { 40, 42, 43 },

    { 44, 45, 46 }, { 44, 46, 47 },         // ����
    { 48, 49, 50 }, { 48, 50, 51 },
    { 52, 53, 54 }, { 52, 54, 55 },
    { 56, 57, 58 }, { 56, 58, 59 },
    { 60, 61, 62 }, { 60, 62, 63 },
    { 64, 65, 66 }, { 64, 66, 67 },

    // �ٸ�
    { 68, 69, 70 }, { 68, 70, 71 },         // �ٸ� (���� �չ�)
    { 72, 73, 74 }, { 72, 74, 75 },
    { 76, 77, 78 }, { 76, 78, 79 },
    { 80, 81, 82 }, { 80, 82, 83 },
    { 84, 85, 86 }, { 84, 86, 87 },
    { 88, 89, 90 }, { 88, 90, 91 },

    { 92, 93, 94 },    { 92, 94, 95 },      // �ٸ� (������ �չ�)
    { 96, 97, 98 },    { 96, 98, 99 },
    { 100, 101, 102 }, { 100, 102, 103 },
    { 104, 105, 106 }, { 104, 106, 107 },
    { 108, 109, 110 }, { 108, 110, 111 },
    { 112, 113, 114 }, { 112, 114, 115 },

    { 116, 117, 118 }, { 116, 118, 119 },   // �ٸ� (���� �޹�)
    { 120, 121, 122 }, { 120, 122, 123 },
    { 124, 125, 126 }, { 124, 126, 127 },
    { 128, 129, 130 }, { 128, 130, 131 },
    { 132, 133, 134 }, { 132, 134, 135 },
    { 136, 137, 138 }, { 136, 138, 139 },

    { 140, 141, 142 }, { 140, 142, 143 },   // �ٸ� (������ �޹�)
    { 144, 145, 146 }, { 144, 146, 147 },
    { 148, 149, 150 }, { 148, 150, 151 },
    { 152, 153, 154 }, { 152, 154, 155 },
    { 156, 157, 158 }, { 156, 158, 159 },
    { 160, 161, 162 }, { 160, 162, 163 },
};

// �Ѿ� ����
CUSTOMVERTEX bulletVertices[] =
{
    // (0, ��1, ����), (��1, ����, 0), (����, 0, ��1), �� = 1.618
    { {  0.1f, 0.1618f, 0.0f },  { 0.0f, 1.0f, 0.0f },  0.0f,  0.0f  },
    { { -0.1f, 0.1618f, 0.0f },  { 0.0f, 1.0f, 0.0f },  0.05f, 0.05f },

    { { 0.0f, 0.1f,  0.1618f },  { 0.0f, 1.0f, 0.0f },  0.1f,  0.1f  },
    { { 0.0f, 0.1f, -0.1618f },  { 0.0f, 1.0f, 0.0f },  0.15f, 0.15f },

    { {  0.1618f, 0.0f,  0.1f }, { 0.0f, 1.0f, 0.0f },  0.2f,  0.2f  },
    { {  0.1618f, 0.0f, -0.1f }, { 0.0f, 1.0f, 0.0f },  0.25f, 0.25f },
    { { -0.1618f, 0.0f,  0.1f }, { 0.0f, 1.0f, 0.0f },  0.3f,  0.3f  },
    { { -0.1618f, 0.0f, -0.1f }, { 0.0f, 1.0f, 0.0f },  0.35f, 0.35f },

    { { 0.0f, -0.1f,  0.1618f }, { 0.0f, 1.0f, 0.0f },  0.4f,  0.4f  },
    { { 0.0f, -0.1f, -0.1618f }, { 0.0f, 1.0f, 0.0f },  0.45f, 0.45f },

    { {  0.1f, -0.1618f, 0.0f }, { 0.0f, 1.0f, 0.0f },  0.5f,  0.5f  },
    { { -0.1f, -0.1618f, 0.0f }, { 0.0f, 1.0f, 0.0f },  0.55f, 0.55f },
};

// �Ѿ� �ε���
CUSTOMINDEX_LIST bulletIndices[] =
{
    {2, 0, 1}, {2, 1, 6}, {2, 6, 8}, {2, 8, 4}, {2, 4, 0},
    {1, 0, 3}, {0, 5, 3}, {0, 4, 5}, {4, 10, 5}, {4, 8, 10},
    {8, 11, 10}, {8, 6, 11}, {6, 7, 11}, {6, 1, 7}, {1, 3, 7},
    {9, 7, 3}, {9, 3, 5}, {9, 5, 10}, {9, 10, 11}, {9, 11, 7},
};