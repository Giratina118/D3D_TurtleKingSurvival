#ifndef __DEFINEDATA_H__
#define __DEFINEDATA_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

// define
#define WIDTH_WINDOW            1280    // 1280 1920
#define HEIGHT_WINDOW           720     // 720  1080
#define FAR_Z			        100.0f  // �þ� �ִ�
#define NEAR_Z			        0.1f    // �þ� �ּ�

// �� ����, ������, �� ����
#define GROUND_X		        10      // �� x�� ����
#define GROUND_Z		        10      // �� z�� ����
#define GROUND_RADIUS	        4       // �� ������

#define CUBE_VERTEX_COUNT       24      // ť�� ���� ��  (��, ��ֹ�)
#define CUBE_TRIANGLE_COUNT     12      // ť�� ���� ��  (��, ��ֹ�)
#define WALL_COUNT              (GROUND_X * 2 + GROUND_Z * 2 + 4)   // �� ��
#define OBSTACLE_COUNT          1       // ���� �ѷ��� ���� �ƴ� ���� ������ ��
#define TREE_COUNT              10      // ����(������) ��
#define BULLET_MAX              512     // ������ �� �ִ� �Ѿ� �ִ� ��
#define ENEMY_MAX               32      // ������ �� �ִ� �� �ִ� ��

#define GRAVITY_ACCELERATION    0.4f       // �߷� ��(���ӵ�)
#define JUMP_POWER              0.2f       // ���� ��
#define PI                      3.141592f  // ���̰�(�¾� �̵��� ���)

// �޴� �����̴�
#define MENU_SLIDER_START       WIDTH_WINDOW / 10.0f * 4.175f
#define MENU_SLIDER_END         WIDTH_WINDOW / 10.0f * 7.825f

// �÷��̾� ������
#define PLAYERHPMAX             WIDTH_WINDOW / 10.0f * 3.5f     // �ִ� hp ǥ���ϴ� ��ġ
#define PLAYERHPMIN             WIDTH_WINDOW / 10.0f * 0.5f     // ���� hp ǥ���ϴ� ��ġ
#define SPREADLEVELMAX          9       // �л� ���׷��̵� �ִ� ����
#define BURSTLEVELMAX           9       // ���� ���׷��̵� �ִ� ����
#define BULLETSIZELEVELMAX      5       // �Ѿ� ũ�� ���׷��̵� �ִ� ����


// enum
// �̵� ����
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

// ȸ�� ����
enum RotationTypeEnum
{
    X_PLUS_ROT,
    X_MINUS_ROT,
    Y_PLUS_ROT,
    Y_MINUS_ROT,
    Z_PLUS_ROT,
    Z_MINUS_ROT
};

// �������� ��Ƴ��� �迭
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

// �ε������� ��Ƴ��� �迭
enum IndexBufferArrayTypeEnum
{
    IB_CUBE,
    IB_ENEMY1,

    IB_BULLET,

    IB_MAX
};

// �ؽ�ó ��Ƴ��� �迭
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

// ������Ʈ(���� ������Ʈ)
enum LandformObjectTypeEnum
{
    OBJECT_LANDFORM_GROUND,
    OBJECT_LANDFORM_WALL,
    OBJECT_LANDFORM_TREE,
    OBJECT_LANDFORM_OBSTACLE,

    OBJECT_LANDFORM_MAX
};


// ����Ű ����
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

// �����̴� ����
enum SliderArrayTypeEnum
{
    SLIDER_FIELDOFVIEW,
    SLIDER_VIEWFAR,
    SLIDER_CAMERAROTATESPEED,
    SLIDER_BGM,
    SLIDER_SE,

    SLIDER_MAX
};

// ���콺 Ŀ�� ��ġ
enum MouseCursorPosTypeEnum
{
    MOUSE_CLICK_XPOS,
    MOUSE_CLICK_YPOS,
    MOUSE_DRAG_XPOS,
    MOUSE_DRAG_YPOS,
};

// ���� ȭ�� ����
enum SceneTypeEnum
{
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT,
    SCENE_SCORE,

    SCENE_MAX
};

// ���� ���� ������
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
// �����̴� ����
struct SliderData
{
    FLOAT clickXPos;
    FLOAT value;
    BOOL  onDragHandle;
};

// �ð� ����
struct DateInfo
{
    FLOAT       clock;          // �ð�
    int         day;            // ��¥
    int         month;          // ��
    D3DXVECTOR3 sunDirection;   // �¾� ����
};

// ȭ�� ����
struct SceneState
{
    int nowSceneType;               // ���� ȭ�� ���� (Ÿ�̵�, ���� ��, ���â)
    int isOpenMenu;                 // �޴� â �������� ����,  0: ����, 1: ����, 2: ����
    BOOL clickSetFPS;               // fps �����ϴ� ĭ ��������
    BOOL openHelp;                  // �»�� ���� ����/�ݱ�
    BOOL onLevelUpScreen;           // ������ â ���ȴ��� ����

    BOOL mouseCrossFocusMode;       // ���콺 ���� ���
    BOOL tempMouseCrossFocusMode;   // ������, �޴� â ���� ���� �� ���

    BOOL rotateFreeze;              // ���콺 ��Ŭ������ ȸ�� ��� ����
    BOOL tempRotateFreeze;          // ������, �޴� â ���� ���� �� ���

    BOOL clickKey[KEY_MAX];         // Ű���� ����Ű   enum ShortcutKeyTypeEnum
};

#endif