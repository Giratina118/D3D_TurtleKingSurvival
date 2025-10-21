#ifndef __DEFINEDATA_H__
#define __DEFINEDATA_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

// define
#define WIDTH_WINDOW            1280    // 1280 1920
#define HEIGHT_WINDOW           720     // 720  1080
#define FAR_Z			        100.0f  // 시야 최대
#define NEAR_Z			        0.1f    // 시야 최소

// 땅 개수, 반지름, 벽 개수
#define GROUND_X		        10      // 땅 x축 길이
#define GROUND_Z		        10      // 땅 z축 길이
#define GROUND_RADIUS	        4       // 땅 반지름

#define CUBE_VERTEX_COUNT       24      // 큐브 정점 수  (벽, 장애물)
#define CUBE_TRIANGLE_COUNT     12      // 큐브 도형 수  (벽, 장애물)
#define WALL_COUNT              (GROUND_X * 2 + GROUND_Z * 2 + 4)   // 벽 수
#define OBSTACLE_COUNT          1       // 맵을 둘러싼 벽이 아닌 따로 떨어진 블럭
#define TREE_COUNT              10      // 나무(빌보드) 수
#define BULLET_MAX              512     // 생성할 수 있는 총알 최대 수
#define ENEMY_MAX               32      // 생성할 수 있는 적 최대 수

#define GRAVITY_ACCELERATION    0.4f       // 중력 힘(가속도)
#define JUMP_POWER              0.2f       // 점프 힘
#define PI                      3.141592f  // 파이값(태양 이동에 사용)

// 메뉴 슬라이더
#define MENU_SLIDER_START       WIDTH_WINDOW / 10.0f * 4.175f
#define MENU_SLIDER_END         WIDTH_WINDOW / 10.0f * 7.825f

// 플레이어 정보들
#define PLAYERHPMAX             WIDTH_WINDOW / 10.0f * 3.5f     // 최대 hp 표시하는 위치
#define PLAYERHPMIN             WIDTH_WINDOW / 10.0f * 0.5f     // 현재 hp 표시하는 위치
#define SPREADLEVELMAX          9       // 분사 업그레이드 최대 레벨
#define BURSTLEVELMAX           9       // 연사 업그레이드 최대 레벨
#define BULLETSIZELEVELMAX      5       // 총알 크기 업그레이드 최대 레벨


// enum
// 이동 방향
enum TransformDirectionTypeEnum
{
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_FRONT,
    MOVE_BACK,
    DOWN_GRAVITY,
    UP_JUMP
};

// 회전 방향
enum RotationTypeEnum
{
    X_PLUS_ROT,
    X_MINUS_ROT,
    Y_PLUS_ROT,
    Y_MINUS_ROT,
    Z_PLUS_ROT,
    Z_MINUS_ROT
};

// 정점버퍼 모아놓은 배열
enum VertexBufferArrayTypeEnum
{
    VB_CUBE,
    VB_GRASS,
    VB_BILBOARD,
    VB_SKYBOX,
    VB_ENEMY1,
    VB_ENEMYHPBAR,

    VB_BULLETFIRE,
    VB_BULLET,

    VB_MAX
};

// 인덱스버퍼 모아놓은 배열
enum IndexBufferArrayTypeEnum
{
    IB_CUBE,
    IB_ENEMY1,

    IB_BULLET,

    IB_MAX
};

// 텍스처 모아놓은 배열
enum TextureArrayTypeEnum
{
    TEXTURE_TREE,
    TEXTURE_GRASS,
    TEXTURE_WALL,

    TEXTURE_SKYBOX_RIGHT,
    TEXTURE_SKYBOX_LEFT,
    TEXTURE_SKYBOX_TOP,
    TEXTURE_SKYBOX_BOTTOM,
    TEXTURE_SKYBOX_FRONT,
    TEXTURE_SKYBOX_BACK,

    TEXTURE_BUTTON_PLAY,
    TEXTURE_BUTTON_RIGHTCHEVRON1,
    TEXTURE_BUTTON_RIGHTCHEVRON2,
    TEXTURE_BUTTON_RIGHTCHEVRON3,
    TEXTURE_BUTTON_MENU,

    TEXTURE_BUTTON_BLUE,
    TEXTURE_BUTTON_RED,

    TEXTURE_SLIDER_HANDLE,
    TEXTURE_SLIDER_HORIZONTAL_BLUE,
    TEXTURE_SLIDER_HORIZONTAL_GRAY,

    TEXTURE_HPBAR_GREEN,
    TEXTURE_HPBAR_RED,
    TEXTURE_EXPBAR_BLUE,
    TEXTURE_EXPBAR_GRAY,

    TEXTURE_FIRE,
    TEXTURE_CROSSLINE,
    TEXTURE_ENEMY_TURTLE,
    TEXTURE_BULLETCOLOR,
    TEXTURE_OUTLINERECT,
    TEXTURE_MENU_BG,
    TEXTURE_MENU_BTN,
    TEXTURE_LVUP_BG_BROWN,
    TEXTURE_LVUP_BG_WHITE,

    TEXTURE_BUTTON_BROWN,
    TEXTURE_BUTTON_BROWN_Light,
    TEXTURE_BUTTON_BLUE_ONMOUSE,
    TEXTURE_BUTTON_RED_ONMOUSE,

    TEXTURE_MAX
};

// 오브젝트(지형 오브젝트)
enum LandformObjectTypeEnum
{
    OBJECT_LANDFORM_GROUND,
    OBJECT_LANDFORM_WALL,
    OBJECT_LANDFORM_TREE,
    OBJECT_LANDFORM_OBSTACLE,

    OBJECT_LANDFORM_MAX
};


// 단축키 종류
enum ShortcutKeyTypeEnum
{
    KEY_TOPVIEWCAMERA,
    KEY_POINTLIGHT,
    KEY_SPOTLIGHT,
    KEY_DIRECTIONALLIGHT,
    KEY_TIMESTOP,
    KEY_TONEXTTIME,

    KEY_MAX
};

// 슬라이더 종류
enum SliderArrayTypeEnum
{
    SLIDER_FIELDOFVIEW,
    SLIDER_VIEWFAR,
    SLIDER_CAMERAROTATESPEED,
    SLIDER_BGM,
    SLIDER_SE,

    SLIDER_MAX
};

// 마우스 커서 위치
enum MouseCursorPosTypeEnum
{
    MOUSE_CLICK_XPOS,
    MOUSE_CLICK_YPOS,
    MOUSE_DRAG_XPOS,
    MOUSE_DRAG_YPOS,
};

// 게임 화면 상태
enum SceneTypeEnum
{
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_SCORE,

    SCENE_MAX
};

// 현재 게임 데이터
enum NowGameDataEnum
{
    NOWGAME_RANKING,
    NOWGAME_BESTSCORE,
    NOWGAME_SCORE,
    NOWGAME_KILLCOUNT,
    NOWGAME_NOWENEMYCOUNT,

    NOWGAME_MAX,
};

enum ButtonName
{
    BUTTON_PLAY,
    BUTTON_SCORE,
    BUTTON_END,
    BUTTON_TOTITLE,
    BUTTON_TONEXT,

    BUTTON_MAX,
};

// struct
// 슬라이더 정보
struct SliderData
{
    FLOAT clickXPos;
    FLOAT value;
    BOOL  onDragHandle;
};

// 시간 정보
struct DateInfo
{
    FLOAT       clock;          // 시각
    int         day;            // 날짜
    int         month;          // 달
    D3DXVECTOR3 sunDirection;   // 태양 각도
};

// 화면 정보
struct SceneState
{
    int nowSceneType;               // 현재 화면 상태 (타이들, 게임 중, 결과창)
    int isOpenMenu;                 // 메뉴 창 열었는지 여부,  0: 닫힘, 1: 정보, 2: 설정
    BOOL clickSetFPS;               // fps 조절하는 칸 눌렀는지
    BOOL openHelp;                  // 좌상단 도움말 열기/닫기
    BOOL onLevelUpScreen;           // 레벨업 창 열렸는지 여부

    BOOL mouseCrossFocusMode;       // 마우스 십자 모드
    BOOL tempMouseCrossFocusMode;   // 레벨업, 메뉴 창 열고 닫을 때 사용

    BOOL rotateFreeze;              // 마우스 우클릭으로 회전 잠금 여부
    BOOL tempRotateFreeze;          // 레벨업, 메뉴 창 열고 닫을 때 사용

    BOOL clickKey[KEY_MAX];         // 키보드 단축키   enum ShortcutKeyTypeEnum
};

#endif