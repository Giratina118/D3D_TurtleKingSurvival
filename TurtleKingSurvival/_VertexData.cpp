#include "_VertexData.h"

DWORD SCREEN_VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
DWORD CUSTOMVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

FLOAT buttonSize = WIDTH_WINDOW / 12.0f;

// 2D UI

// 타이틀씬 정점
SCREEN_VERTEX titleSceneVertices[] =
{
    { WIDTH_WINDOW * 0.6f,  0.0f,                    0.4f, 1.0f,    0x80909090, 0.0f, 0.0f },   // UI 바탕
    { WIDTH_WINDOW,         0.0f,                    0.4f, 1.0f,    0x80909090, 1.0f, 0.0f },
    { WIDTH_WINDOW,         HEIGHT_WINDOW,           0.4f, 1.0f,    0x80909090, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.6f,  HEIGHT_WINDOW,           0.4f, 1.0f,    0x80909090, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // 시작 버튼
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.4375f, 0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // 점수 버튼
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.4375f, 0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.5625f, 0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.5625f, 0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.625f,  0.4f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // 종료 버튼
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.625f,  0.4f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.94f, HEIGHT_WINDOW * 0.75f,   0.4f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.65f, HEIGHT_WINDOW * 0.75f,   0.4f, 1.0f,    0xffffffff, 0.0f, 1.0f },
    

    { 0.0f,                0.0f,                  0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 타이틀 점수화면 바탕
    { WIDTH_WINDOW * 0.5f, 0.0f,                  0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.5f, HEIGHT_WINDOW * 0.95f, 0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { 0.0f,                HEIGHT_WINDOW * 0.95f, 0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },
};

// 결과씬 정점
SCREEN_VERTEX resultSceneVertices[] =
{
    { WIDTH_WINDOW * 0.125f, HEIGHT_WINDOW * 0.1f,  0.4f, 1.0f,     0xb0ffffff, 0.0f, 0.0f },   // UI 바탕
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.1f,  0.4f, 1.0f,     0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.125f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.35f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 타이틀로 버튼
    { WIDTH_WINDOW * 0.65f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.65f,  HEIGHT_WINDOW * 0.9375f, 0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.35f,  HEIGHT_WINDOW * 0.9375f, 0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ff0000, 0.0f, 0.0f },   // 점수 강조
    { WIDTH_WINDOW * 0.85f,  HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ff0000, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.85f,  HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ff0000, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ff0000, 0.0f, 1.0f },
};

// 게임씬 정점
SCREEN_VERTEX gameSceneVertices[] =
{
    { 5.0f,                  10.0f,                  0.5f, 1.0f,    0x90ffffff, 0.0f, 0.0f },   // 좌상단 정보
    { WIDTH_WINDOW * 0.275f, 10.0f,                  0.5f, 1.0f,    0x90ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.275f, HEIGHT_WINDOW * 0.375f, 0.5f, 1.0f,    0x90ffffff, 1.0f, 1.0f },
    { 5.0f,                  HEIGHT_WINDOW * 0.375f, 0.5f, 1.0f,    0x90ffffff, 0.0f, 1.0f },

    // 우상단 버튼
    { WIDTH_WINDOW - buttonSize * 5.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ▷    재생/정지
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 5.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >    다음 시간
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 4.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >>   다음 날
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 3.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // >>>  다음 달
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 2.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 0.0f, 0.0f },   // ▤    메뉴
    { WIDTH_WINDOW - buttonSize * 0.25f, 10.0f,              0.5f, 1.0f,    0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW - buttonSize * 0.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW - buttonSize * 1.25f, 10.0f + buttonSize, 0.5f, 1.0f,    0xffffffff, 0.0f, 1.0f },

    
    { WIDTH_WINDOW * 0.468f, HEIGHT_WINDOW * 0.5f - WIDTH_WINDOW * 0.042f, 0.5f, 1.0f,  0xffffffff, 0.0f, 0.0f },   // 십자 조준점
    { WIDTH_WINDOW * 0.518f, HEIGHT_WINDOW * 0.5f - WIDTH_WINDOW * 0.042f, 0.5f, 1.0f,  0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.518f, HEIGHT_WINDOW * 0.5f + WIDTH_WINDOW * 0.008f, 0.5f, 1.0f,  0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.468f, HEIGHT_WINDOW * 0.5f + WIDTH_WINDOW * 0.008f, 0.5f, 1.0f,  0xffffffff, 0.0f, 1.0f },
};

// 메뉴 UI
SCREEN_VERTEX menuVertices[] =
{
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 0.0f },   // UI 바탕
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 0.0f, 0.0f },   // 현재 능력
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0xb0ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xb0ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0xb0ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // 설정
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.25f,   0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.225f, HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.375f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },


    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.8f,    0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 타이틀로 버튼
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.8f,    0.4f, 1.0f,   0xffffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.675f, HEIGHT_WINDOW * 0.9f,    0.4f, 1.0f,   0xffffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.9f,    0.4f, 1.0f,   0xffffffff, 0.0f, 1.0f },


    // FPS 변경
    { WIDTH_WINDOW * 0.425f, HEIGHT_WINDOW * 0.2f,    0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // 현재
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

    { WIDTH_WINDOW * 0.375f, HEIGHT_WINDOW * 0.215f,  0.4f, 1.0f,   0xffffffff, 0.0f, 0.0f },   // FPS 글자 위치
};

// 메뉴 슬라이더 정점
SCREEN_VERTEX menuSliderVertices[] =
{
    // 슬라이더 1 (시야각)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 회색(슬라이더 밑 바탕, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 회색/파란색(슬라이더 밑 바탕, 왼쪽 원)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // 회색/파란색(슬라이더 밑 바탕, 오른쪽 원)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 파란색(슬라이더 채워진 영역, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.3f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.35f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.2875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 슬라이더 손잡이
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.2875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // 슬라이더 2 (시야범위)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 회색(슬라이더 밑 바탕, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 회색/파란색(슬라이더 밑 바탕, 왼쪽 원)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // 회색/파란색(슬라이더 밑 바탕, 오른쪽 원)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 파란색(슬라이더 채워진 영역, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.4f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.45f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.3875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 슬라이더 손잡이
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.3875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // 슬라이더 3 (마우스 회전 감도)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 회색(슬라이더 밑 바탕, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 회색/파란색(슬라이더 밑 바탕, 왼쪽 원)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // 회색/파란색(슬라이더 밑 바탕, 오른쪽 원)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 파란색(슬라이더 채워진 영역, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.5f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.55f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.4875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 슬라이더 손잡이
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.4875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },


    // 슬라이더 3 (배경음 볼륨)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 회색(슬라이더 밑 바탕, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 회색/파란색(슬라이더 밑 바탕, 왼쪽 원)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // 회색/파란색(슬라이더 밑 바탕, 오른쪽 원)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 파란색(슬라이더 채워진 영역, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.6f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.65f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.5875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 슬라이더 손잡이
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.5875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    // 슬라이더 3 (마우스 회전 감도)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 회색(슬라이더 밑 바탕, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 회색/파란색(슬라이더 밑 바탕, 왼쪽 원)
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.0f,  1.0f },

    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },  // 회색/파란색(슬라이더 밑 바탕, 오른쪽 원)
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.8f,   HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },

    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.16f, 0.0f },  // 파란색(슬라이더 채워진 영역, 중앙 막대)
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.7f,    0.3f, 1.0f,   0xffffffff, 0.84f, 0.0f },
    { WIDTH_WINDOW * 0.765f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.84f, 1.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.75f,   0.3f, 1.0f,   0xffffffff, 0.16f, 1.0f },

    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.6875f, 0.1f, 1.0f,   0xffffffff, 0.0f,  0.0f },  // 슬라이더 손잡이
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.6875f, 0.1f, 1.0f,   0xffffffff, 1.0f,  0.0f },
    { WIDTH_WINDOW * 0.435f, HEIGHT_WINDOW * 0.7625f, 0.1f, 1.0f,   0xffffffff, 1.0f,  1.0f },
    { WIDTH_WINDOW * 0.4f,   HEIGHT_WINDOW * 0.7625f, 0.1f, 1.0f,   0xffffffff, 0.0f,  1.0f },

};

// 플레이어 체력바, 경험치바
SCREEN_VERTEX playerHpExpBarVertices[] =
{
    // 체력 게이지
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.8125f, 0.8f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // 최대 체력 게이지 (빨강)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.8125f, 0.8f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    { PLAYERHPMIN, HEIGHT_WINDOW * 0.8125f, 0.7f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // 현재 체력 게이지 (초록)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.8125f, 0.7f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    // 경험치 게이지
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // 경험치 바탕 (회색)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.8f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.9375f, 0.8f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.9375f, 0.8f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    { PLAYERHPMIN, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 0.0f, 0.0f },   // 현재 경험치 게이지 (파랑)
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.875f,  0.7f, 1.0f,     0x60ffffff, 1.0f, 0.0f },
    { PLAYERHPMAX, HEIGHT_WINDOW * 0.9375f, 0.7f, 1.0f,     0x60ffffff, 1.0f, 1.0f },
    { PLAYERHPMIN, HEIGHT_WINDOW * 0.9375f, 0.7f, 1.0f,     0x60ffffff, 0.0f, 1.0f },

    // 체력 게이지 위 레벨 표시
    { PLAYERHPMIN,         HEIGHT_WINDOW * 0.7625f, 0.6f, 1.0f,     0x906181df, 0.0f, 0.0f },
    { PLAYERHPMAX * 0.35f, HEIGHT_WINDOW * 0.7625f, 0.6f, 1.0f,     0x906181df, 1.0f, 0.0f },
    { PLAYERHPMAX * 0.4f,  HEIGHT_WINDOW * 0.8125f, 0.6f, 1.0f,     0x906181df, 1.0f, 1.0f },
    { PLAYERHPMIN,         HEIGHT_WINDOW * 0.8125f, 0.6f, 1.0f,     0x906181df, 0.0f, 1.0f },
};

// 레벨업 창
SCREEN_VERTEX levelUpScreenVertices[] =
{
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // UI 바탕
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.125f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.875f, HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.1f,   HEIGHT_WINDOW * 0.875f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // 첫 번째 선택
    { WIDTH_WINDOW * 0.37f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.37f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.15f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.38f,  HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // 두 번째 선택
    { WIDTH_WINDOW * 0.595f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.595f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.38f,  HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.605f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // 세 번째 선택
    { WIDTH_WINDOW * 0.825f, HEIGHT_WINDOW * 0.3125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.825f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.605f, HEIGHT_WINDOW * 0.8125f, 0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },

    { WIDTH_WINDOW * 0.33f,  HEIGHT_WINDOW * 0.175f,  0.4f, 1.0f,   0x60ffffff, 0.0f, 0.0f },   // 타이틀
    { WIDTH_WINDOW * 0.645f, HEIGHT_WINDOW * 0.175f,  0.4f, 1.0f,   0x60ffffff, 1.0f, 0.0f },
    { WIDTH_WINDOW * 0.645f, HEIGHT_WINDOW * 0.3f,    0.4f, 1.0f,   0x60ffffff, 1.0f, 1.0f },
    { WIDTH_WINDOW * 0.33f,  HEIGHT_WINDOW * 0.3f,    0.4f, 1.0f,   0x60ffffff, 0.0f, 1.0f },
};


// 정육면체 정점
D3DXVECTOR3 cubePoint[] =
{
    { -GROUND_RADIUS,  GROUND_RADIUS, -GROUND_RADIUS }, // 앞면 좌상
    {  GROUND_RADIUS,  GROUND_RADIUS, -GROUND_RADIUS }, // 앞면 우상
    {  GROUND_RADIUS, -GROUND_RADIUS, -GROUND_RADIUS }, // 앞면 우하
    { -GROUND_RADIUS, -GROUND_RADIUS, -GROUND_RADIUS }, // 앞면 좌하

    { -GROUND_RADIUS,  GROUND_RADIUS,  GROUND_RADIUS }, // 뒷면 좌상
    {  GROUND_RADIUS,  GROUND_RADIUS,  GROUND_RADIUS }, // 뒷면 우상
    {  GROUND_RADIUS, -GROUND_RADIUS,  GROUND_RADIUS }, // 뒷면 우하
    { -GROUND_RADIUS, -GROUND_RADIUS,  GROUND_RADIUS }  // 뒷면 좌하
};

// 정육면체 법선벡터
D3DXVECTOR3 cubeNormal[] =
{
    {  1.0f,  0.0f,  0.0f },    // x+
    { -1.0f,  0.0f,  0.0f },    // x-
    {  0.0f,  1.0f,  0.0f },    // y+
    {  0.0f, -1.0f,  0.0f },    // y-
    {  0.0f,  0.0f,  1.0f },    // z+
    {  0.0f,  0.0f, -1.0f }     // z-
};

// 정육면체 정점
CUSTOMVERTEX cubeVertices[] =
{
    // 정육면체
    { cubePoint[0], cubeNormal[5], 0.0f, 0.0f },    // 앞면
    { cubePoint[1], cubeNormal[5], 1.0f, 0.0f },
    { cubePoint[2], cubeNormal[5], 1.0f, 1.0f },
    { cubePoint[3], cubeNormal[5], 0.0f, 1.0f },

    { cubePoint[5], cubeNormal[4], 0.0f, 0.0f },    // 뒷면
    { cubePoint[4], cubeNormal[4], 1.0f, 0.0f },
    { cubePoint[7], cubeNormal[4], 1.0f, 1.0f },
    { cubePoint[6], cubeNormal[4], 0.0f, 1.0f },

    { cubePoint[4], cubeNormal[2], 0.0f, 0.0f },    // 윗면
    { cubePoint[5], cubeNormal[2], 1.0f, 0.0f },
    { cubePoint[1], cubeNormal[2], 1.0f, 1.0f },
    { cubePoint[0], cubeNormal[2], 0.0f, 1.0f },

    { cubePoint[3], cubeNormal[3], 0.0f, 0.0f },    // 아랫면
    { cubePoint[2], cubeNormal[3], 1.0f, 0.0f },
    { cubePoint[6], cubeNormal[3], 1.0f, 1.0f },
    { cubePoint[7], cubeNormal[3], 0.0f, 1.0f },

    { cubePoint[1], cubeNormal[0], 0.0f, 0.0f },    // 오른면
    { cubePoint[5], cubeNormal[0], 1.0f, 0.0f },
    { cubePoint[6], cubeNormal[0], 1.0f, 1.0f },
    { cubePoint[2], cubeNormal[0], 0.0f, 1.0f },

    { cubePoint[4], cubeNormal[1], 0.0f, 0.0f },    // 왼면
    { cubePoint[0], cubeNormal[1], 1.0f, 0.0f },
    { cubePoint[3], cubeNormal[1], 1.0f, 1.0f },
    { cubePoint[7], cubeNormal[1], 0.0f, 1.0f },
};

// 정육면체 인덱스
CUSTOMINDEX_LIST cubeIndices[] =
{
    { 0, 1, 2 },    { 0, 2, 3 },
    { 4, 5, 6 },    { 4, 6, 7 },
    { 8, 9, 10 },   { 8, 10, 11 },
    { 12, 13, 14 }, { 12, 14, 15 },
    { 16, 17, 18 }, { 16, 18, 19 },
    { 20, 21, 22 }, { 20, 22, 23 }
};


// 잔디 정점
CUSTOMVERTEX groundVertices[] =
{
    { { -GROUND_RADIUS, 0.0f,  GROUND_RADIUS }, cubeNormal[2], 0.0f, 0.0f },    // 윗면
    { {  GROUND_RADIUS, 0.0f,  GROUND_RADIUS }, cubeNormal[2], 1.0f, 0.0f },
    { {  GROUND_RADIUS, 0.0f, -GROUND_RADIUS }, cubeNormal[2], 1.0f, 1.0f },
    { { -GROUND_RADIUS, 0.0f, -GROUND_RADIUS }, cubeNormal[2], 0.0f, 1.0f }
};

// 빌보드
CUSTOMVERTEX bliboardVertices[] =
{
    // 나무
    { { -3.0f,  4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 0.0f },
    { {  3.0f,  4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 0.0f },
    { {  3.0f, -4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   1.0f, 1.0f },
    { { -3.0f, -4.0f, 0.0f },   { 0.0f, 1.0f, 1.0f },   0.0f, 1.0f },

    // 구름
    { { -5.0f,  2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   0.0f, 0.0f },
    { {  5.0f,  2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   1.0f, 0.0f },
    { {  5.0f, -2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   1.0f, 1.0f },
    { { -5.0f, -2.5f, 0.0f },   { 0.0f, 1.0f, 0.2f },   0.0f, 1.0f },
};

// 적 체력바 (빌보드)
CUSTOMVERTEX enemyHpBarVertices[] =
{
    // 최대 체력 게이지 (빨강)
    { { -0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },
    { {  0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    // 현재 체력 게이지 (초록)
    { { -0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },
    { {  0.5f,  0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -0.5f, -0.1f, 0.0f },   { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },
};

// 스프라이트 정점
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


// 스카이박스 정점
CUSTOMVERTEX skyBoxVertices[] =
{
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 우측면(x+)
    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 좌측면(x-)
    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 윗면(y+)
    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 아랫면(y-)
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { { -1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 앞면(z+)
    { {  1.0f,  1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { {  1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { { -1.0f, -1.0f,  1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },

    { {  1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 0.0f },   // 뒷면(z-)
    { { -1.0f,  1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 0.0f },
    { { -1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   1.0f, 1.0f },
    { {  1.0f, -1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },   0.0f, 1.0f },
};


FLOAT pixel_128 = 1.0f / 128.0f;
FLOAT pixel_64 = 1.0f / 64.0f;

// 적1 정점
CUSTOMVERTEX enemy1Vertices[] =
{
    // 몸통
    { { 0.5f, 0.25f, -0.75f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 6.0f,  pixel_64 * 63.0f },  // 우측면(x+)
    { { 0.5f, 0.25f, 0.5f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 6.0f,  pixel_64 * 43.0f },
    { { 0.5f, -0.6f, 0.5f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 12.0f, pixel_64 * 43.0f },
    { { 0.5f, -0.6f, -0.75f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 12.0f, pixel_64 * 63.0f },

    { { -0.5f, 0.25f, 0.5f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 37.0f, pixel_64 * 43.0f },  // 좌측면(x-)
    { { -0.5f, 0.25f, -0.75f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 37.0f, pixel_64 * 63.0f },
    { { -0.5f, -0.6f, -0.75f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 63.0f },
    { { -0.5f, -0.6f, 0.5f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 43.0f },

    { { -0.5f, 0.25f, 0.5f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 37.0f, pixel_64 * 43.0f },  // 윗면(y+)
    { { 0.5f, 0.25f, 0.5f },    { 0.0f, 1.0f, 0.0f },   pixel_128 * 56.0f, pixel_64 * 43.0f },
    { { 0.5f, 0.25f, -0.75f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 56.0f, pixel_64 * 63.0f },
    { { -0.5f, 0.25f, -0.75f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 37.0f, pixel_64 * 63.0f },

    { { 0.5f, -0.6f, 0.5f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 30.0f, pixel_64 * 4.0f  },  // 아랫면(y-)
    { { -0.5f, -0.6f, 0.5f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 47.0f, pixel_64 * 4.0f  },
    { { -0.5f, -0.6f, -0.75f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 47.0f, pixel_64 * 22.0f },
    { { 0.5f, -0.6f, -0.75f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 30.0f, pixel_64 * 22.0f },

    { { 0.5f, 0.25f, 0.5f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 12.0f, pixel_64 * 37.0f },  // 앞면(z+)
    { { -0.5f, 0.25f, 0.5f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 37.0f },
    { { -0.5f, -0.6f, 0.5f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 44.0f },
    { { 0.5f, -0.6f, 0.5f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 12.0f, pixel_64 * 44.0f },

    { { -0.5f, 0.25f, -0.75f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 37.0f },  // 뒷면(z-)
    { { 0.5f, 0.25f, -0.75f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 50.0f, pixel_64 * 37.0f },
    { { 0.5f, -0.6f, -0.75f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 50.0f, pixel_64 * 44.0f },
    { { -0.5f, -0.6f, -0.75f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 44.0f },
    

    // 얼굴
    { { 0.35f, 0.15f, 0.5f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 2.0f,  pixel_64 * 6.0f  },  // 우측면(x+)
    { { 0.35f, 0.15f, 1.0f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },
    { { 0.35f, -0.35f, 1.0f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 11.0f },
    { { 0.35f, -0.35f, 0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 2.0f,  pixel_64 * 11.0f },

    { { -0.35f, 0.15f, 1.0f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 6.0f  },  // 좌측면(x-)
    { { -0.35f, 0.15f, 0.5f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 6.0f  },
    { { -0.35f, -0.35f, 0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 11.0f },
    { { -0.35f, -0.35f, 1.0f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 11.0f },

    { { -0.35f, 0.15f, 1.0f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 0.0f  },  // 윗면(y+)
    { { 0.35f, 0.15f, 1.0f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 14.0f, pixel_64 * 0.0f  },
    { { 0.35f, 0.15f, 0.5f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 14.0f, pixel_64 * 6.0f  },
    { { -0.35f, 0.15f, 0.5f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },

    { { 0.35f, -0.35f, 1.0f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 0.0f  },  // 아랫면(y-)
    { { -0.35f, -0.35f, 1.0f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 0.0f  },
    { { -0.35f, -0.35f, 0.5f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 20.0f, pixel_64 * 6.0f  },
    { { 0.35f, -0.35f, 0.5f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 14.0f, pixel_64 * 6.0f  },

    { { 0.35f, 0.15f, 1.0f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 8.0f,  pixel_64 * 6.0f  },  // 앞면(z+)
    { { -0.35f, 0.15f, 1.0f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 14.0f, pixel_64 * 6.0f  },
    { { -0.35f, -0.35f, 1.0f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 14.0f, pixel_64 * 11.0f },
    { { 0.35f, -0.35f, 1.0f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 8.0f,  pixel_64 * 11.0f },


    // 대포
    { { 0.25f, 0.75f, -0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 16.0f },  // 우측면(x+)
    { { 0.25f, 0.75f, 0.9f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },
    { { 0.25f, 0.25f, 0.9f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.25f, -0.5f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 8.0f  },

    { { -0.25f, 0.75f, 0.9f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 8.0f  },  // 좌측면(x-)
    { { -0.25f, 0.75f, -0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.25f, -0.5f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },
    { { -0.25f, 0.25f, 0.9f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 16.0f },

    { { -0.25f, 0.75f, 0.9f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },  // 윗면(y+)
    { { 0.25f, 0.75f, 0.9f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.75f, -0.5f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.75f, -0.5f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 91.0f, pixel_64 * 16.0f },

    { { 0.25f, 0.25f, 0.9f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 16.0f },  // 아랫면(y-)
    { { -0.25f, 0.25f, 0.9f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 69.0f, pixel_64 * 8.0f  },
    { { -0.25f, 0.25f, -0.5f }, { 0.0f, -1.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 8.0f  },
    { { 0.25f, 0.25f, -0.5f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },

    { { 0.25f, 0.75f, 0.9f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 69.0f, pixel_64 * 16.0f },  // 앞면(z+)
    { { -0.25f, 0.75f, 0.9f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 77.0f, pixel_64 * 16.0f },
    { { -0.25f, 0.25f, 0.9f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 77.0f, pixel_64 * 24.0f },
    { { 0.25f, 0.25f, 0.9f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 69.0f, pixel_64 * 24.0f },

    { { -0.25f, 0.75f, -0.5f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 83.0f, pixel_64 * 16.0f },  // 뒷면(z-)
    { { 0.25f, 0.75f, -0.5f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 91.0f, pixel_64 * 16.0f },
    { { 0.25f, 0.25f, -0.5f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 91.0f, pixel_64 * 24.0f },
    { { -0.25f, 0.25f, -0.5f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 83.0f, pixel_64 * 24.0f },


    // 다리 (왼쪽 앞발)
    { { -0.4f, -0.25f, 0.1f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // 우측면(x+)
    { { -0.4f, -0.25f, 0.4f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, 0.4f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, 0.1f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, 0.4f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // 좌측면(x-)
    { { -0.7f, -0.25f, 0.1f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, 0.1f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, 0.4f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, 0.4f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // 윗면(y+)
    { { -0.4f, -0.25f, 0.4f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { -0.4f, -0.25f, 0.1f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { -0.7f, -0.25f, 0.1f },  { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { -0.4f, -1.0f, 0.4f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // 아랫면(y-)
    { { -0.7f, -1.0f, 0.4f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { -0.7f, -1.0f, 0.1f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { -0.4f, -1.0f, 0.1f },   { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { -0.4f, -0.25f, 0.4f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // 앞면(z+)
    { { -0.7f, -0.25f, 0.4f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { -0.7f, -0.25f, 0.1f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // 뒷면(z-)
    { { -0.4f, -0.25f, 0.1f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    // 다리 (오른쪽 앞발)
    { { 0.7f, -0.25f, 0.1f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // 우측면(x+)
    { { 0.7f, -0.25f, 0.4f },   { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, 0.4f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, 0.1f },    { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, 0.4f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // 좌측면(x-)
    { { 0.4f, -0.25f, 0.1f },   { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, 0.1f },    { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, 0.4f },    { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, 0.4f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // 윗면(y+)
    { { 0.7f, -0.25f, 0.4f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { 0.7f, -0.25f, 0.1f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { 0.4f, -0.25f, 0.1f },   { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { 0.7f, -1.0f, 0.4f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // 아랫면(y-)
    { { 0.4f, -1.0f, 0.4f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { 0.4f, -1.0f, 0.1f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { 0.7f, -1.0f, 0.1f },    { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { 0.7f, -0.25f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // 앞면(z+)
    { { 0.4f, -0.25f, 0.4f },   { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, 0.4f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, 0.4f },    { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { 0.4f, -0.25f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // 뒷면(z-)
    { { 0.7f, -0.25f, 0.1f },   { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, 0.1f },    { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, 0.1f },    { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    // 다리 (왼쪽 뒷발)
    { { -0.4f, -0.25f, -0.65f }, { 1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // 우측면(x+)
    { { -0.4f, -0.25f, -0.35f }, { 1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, -0.35f },  { 1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.4f, -1.0f, -0.65f },  { 1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, -0.35f }, { -1.0f, 0.0f, 0.0f }, pixel_128 * 44.0f, pixel_64 * 25.0f },  // 좌측면(x-)
    { { -0.7f, -0.25f, -0.65f }, { -1.0f, 0.0f, 0.0f }, pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, -0.65f },  { -1.0f, 0.0f, 0.0f }, pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { -0.7f, -1.0f, -0.35f },  { -1.0f, 0.0f, 0.0f }, pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { -0.7f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 10.0f, pixel_64 * 23.0f },  // 윗면(y+)
    { { -0.4f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { -0.4f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { -0.7f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },  pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { -0.4f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 52.0f, pixel_64 * 29.0f },  // 아랫면(y-)
    { { -0.7f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { -0.7f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { -0.4f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f }, pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { -0.4f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // 앞면(z+)
    { { -0.7f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { -0.7f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f }, pixel_128 * 31.0f, pixel_64 * 36.0f },  // 뒷면(z-)
    { { -0.4f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f }, pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { -0.4f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f }, pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { -0.7f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f }, pixel_128 * 44.0f, pixel_64 * 36.0f },

    // 다리 (오른쪽 뒷발)
    { { 0.7f, -0.25f, -0.65f }, { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 36.0f },  // 우측면(x+)
    { { 0.7f, -0.25f, -0.35f }, { 1.0f, 0.0f, 0.0f },   pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, -0.35f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.7f, -1.0f, -0.65f },  { 1.0f, 0.0f, 0.0f },   pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, -0.35f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 36.0f },  // 좌측면(x-)
    { { 0.4f, -0.25f, -0.65f }, { -1.0f, 0.0f, 0.0f },  pixel_128 * 31.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, -0.65f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 31.0f },
    { { 0.4f, -1.0f, -0.35f },  { -1.0f, 0.0f, 0.0f },  pixel_128 * 44.0f, pixel_64 * 36.0f },

    { { 0.4f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 23.0f },  // 윗면(y+)
    { { 0.7f, -0.25f, -0.35f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 23.0f },
    { { 0.7f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 15.0f, pixel_64 * 28.0f },
    { { 0.4f, -0.25f, -0.65f }, { 0.0f, 1.0f, 0.0f },   pixel_128 * 10.0f, pixel_64 * 28.0f },

    { { 0.7f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 29.0f },  // 아랫면(y-)
    { { 0.4f, -1.0f, -0.35f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 29.0f },
    { { 0.4f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 57.0f, pixel_64 * 34.0f },
    { { 0.7f, -1.0f, -0.65f },  { 0.0f, -1.0f, 0.0f },  pixel_128 * 52.0f, pixel_64 * 34.0f },

    { { 0.7f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 25.0f },  // 앞면(z+)
    { { 0.4f, -0.25f, -0.35f }, { 0.0f, 0.0f, 1.0f },   pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, -0.35f },  { 0.0f, 0.0f, 1.0f },   pixel_128 * 31.0f, pixel_64 * 25.0f },

    { { 0.4f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 25.0f },  // 뒷면(z-)
    { { 0.7f, -0.25f, -0.65f }, { 0.0f, 0.0f, -1.0f },  pixel_128 * 44.0f, pixel_64 * 30.0f },
    { { 0.7f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 30.0f },
    { { 0.4f, -1.0f, -0.65f },  { 0.0f, 0.0f, -1.0f },  pixel_128 * 31.0f, pixel_64 * 25.0f },
};

// 적1 인덱스
CUSTOMINDEX_LIST enemy1Indices[] =
{
    { 0, 1, 2 },    { 0, 2, 3 },            // 몸통
    { 4, 5, 6 },    { 4, 6, 7 },
    { 8, 9, 10 },   { 8, 10, 11 },
    { 12, 13, 14 }, { 12, 14, 15 },
    { 16, 17, 18 }, { 16, 18, 19 },
    { 20, 21, 22 }, { 20, 22, 23 },

    { 24, 25, 26 }, { 24, 26, 27 },         // 얼굴
    { 28, 29, 30 }, { 28, 30, 31 },
    { 32, 33, 34 }, { 32, 34, 35 },
    { 36, 37, 38 }, { 36, 38, 39 },
    { 40, 41, 42 }, { 40, 42, 43 },

    { 44, 45, 46 }, { 44, 46, 47 },         // 대포
    { 48, 49, 50 }, { 48, 50, 51 },
    { 52, 53, 54 }, { 52, 54, 55 },
    { 56, 57, 58 }, { 56, 58, 59 },
    { 60, 61, 62 }, { 60, 62, 63 },
    { 64, 65, 66 }, { 64, 66, 67 },

    // 다리
    { 68, 69, 70 }, { 68, 70, 71 },         // 다리 (왼쪽 앞발)
    { 72, 73, 74 }, { 72, 74, 75 },
    { 76, 77, 78 }, { 76, 78, 79 },
    { 80, 81, 82 }, { 80, 82, 83 },
    { 84, 85, 86 }, { 84, 86, 87 },
    { 88, 89, 90 }, { 88, 90, 91 },

    { 92, 93, 94 },    { 92, 94, 95 },      // 다리 (오른쪽 앞발)
    { 96, 97, 98 },    { 96, 98, 99 },
    { 100, 101, 102 }, { 100, 102, 103 },
    { 104, 105, 106 }, { 104, 106, 107 },
    { 108, 109, 110 }, { 108, 110, 111 },
    { 112, 113, 114 }, { 112, 114, 115 },

    { 116, 117, 118 }, { 116, 118, 119 },   // 다리 (왼쪽 뒷발)
    { 120, 121, 122 }, { 120, 122, 123 },
    { 124, 125, 126 }, { 124, 126, 127 },
    { 128, 129, 130 }, { 128, 130, 131 },
    { 132, 133, 134 }, { 132, 134, 135 },
    { 136, 137, 138 }, { 136, 138, 139 },

    { 140, 141, 142 }, { 140, 142, 143 },   // 다리 (오른쪽 뒷발)
    { 144, 145, 146 }, { 144, 146, 147 },
    { 148, 149, 150 }, { 148, 150, 151 },
    { 152, 153, 154 }, { 152, 154, 155 },
    { 156, 157, 158 }, { 156, 158, 159 },
    { 160, 161, 162 }, { 160, 162, 163 },
};

// 총알 정점
CUSTOMVERTEX bulletVertices[] =
{
    // (0, ±1, ±φ), (±1, ±φ, 0), (±φ, 0, ±1), φ = 1.618
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

// 총알 인덱스
CUSTOMINDEX_LIST bulletIndices[] =
{
    {2, 0, 1}, {2, 1, 6}, {2, 6, 8}, {2, 8, 4}, {2, 4, 0},
    {1, 0, 3}, {0, 5, 3}, {0, 4, 5}, {4, 10, 5}, {4, 8, 10},
    {8, 11, 10}, {8, 6, 11}, {6, 7, 11}, {6, 1, 7}, {1, 3, 7},
    {9, 7, 3}, {9, 3, 5}, {9, 5, 10}, {9, 10, 11}, {9, 11, 7},
};