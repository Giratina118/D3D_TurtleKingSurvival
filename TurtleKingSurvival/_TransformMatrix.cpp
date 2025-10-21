#include "_TransformMatrix.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include <math.h>

extern CPlayer playerObj;           // 플레이어 오브젝트
extern CEnemy* enemyObj[ENEMY_MAX]; // 적 오브젝트
extern Timer timer; // 타이머

extern CObject* landformObj[OBJECT_LANDFORM_MAX];   // 지형지물 오브젝트
extern LPDIRECT3DVERTEXBUFFER9* g_pVB_Array;

FLOAT tempAngle = 0.0f;

// 이동
BOOL TranslateObject(CObject* object, int moveDir, float moveSpeed)
{
    D3DXMATRIX nextObjectMatrix; // 다음 위치 저장할 곳
    D3DXMATRIX moveDirection = GetTransformMatrix(object->GetMatrix(), moveDir, moveSpeed); // 이동 방향
    FLOAT gravityMoveDown = 0.0f;

    D3DXVECTOR3 nextMove(0, 0, 0);

    for (int xyz = 0; xyz < 3; ++xyz)
    {
        D3DXVECTOR3 tryMove = nextMove;
        nextObjectMatrix = *object->GetMatrix();

        // x y z축 접촉을 따로 계산하여 막히는 방향으로는 이동 불가
        if (xyz == 0) tryMove.x += moveDirection._41;
        if (xyz == 1) tryMove.y += moveDirection._42;
        if (xyz == 2) tryMove.z += moveDirection._43;

        nextObjectMatrix._41 += tryMove.x;
        nextObjectMatrix._42 += tryMove.y;
        nextObjectMatrix._43 += tryMove.z;

        CObject nextObj(nextObjectMatrix, object->GetLength(), object->GetRadius(), object->GetIsCollision());

        if (CollisionCheckIndex(object, nextObj, xyz, &gravityMoveDown) != NULL) continue;  // 충돌 체크
        else nextMove = tryMove;
    }

    BOOL returnCollision = FALSE;   // 바닥(아래쪽 방향)에 닿았는지 체크
    if (nextMove.y == 0)
    {
        nextMove.y = -gravityMoveDown + 0.01f; // 바닥 충돌 시 바닥 바로 위에 위치하도록
        returnCollision = TRUE;
    }

    // 최종 이동 적용
    D3DXMATRIX transformMatrix;
    D3DXMatrixTranslation(&transformMatrix, nextMove.x, nextMove.y, nextMove.z);
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    return returnCollision;
}

// 이동 방향 설정
D3DXMATRIX GetTransformMatrix(D3DXMATRIX* object, int moveDir, float moveSpeed)
{
    D3DXMATRIX transformMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    D3DXVECTOR3 moveDirection;

    switch (moveDir)
    {
    case MOVE_RIGHT:   moveDirection = {  object->_11,  0.0f,         object->_13 }; break;
    case MOVE_LEFT:    moveDirection = { -object->_11,  0.0f,        -object->_13 }; break;
    case MOVE_UP:      moveDirection = {  object->_21,  object->_22,  object->_23 }; break;
    case MOVE_DOWN:    moveDirection = { -object->_21, -object->_22, -object->_23 }; break;
    case MOVE_FRONT:   moveDirection = {  object->_31,  0.0f,         object->_33 }; break;
    case MOVE_BACK:    moveDirection = { -object->_31,  0.0f,        -object->_33 }; break;
    case DOWN_GRAVITY: moveDirection = {  0.0f,        -1.0f,         0.0f };        break;
    case UP_JUMP:      moveDirection = {  0.0f,         1.0f,         0.0f };        break;
    }
    moveDirection *= moveSpeed;
    D3DXMatrixTranslation(&transformMatrix, moveDirection.x, moveDirection.y, moveDirection.z);
    return transformMatrix;
}

// 충돌 체크 묶음
CObject* CollisionCheckIndex(CObject* object, CObject nextObj, int xyz, FLOAT* gravityMoveDown)
{
    CObject* collisionObj = NULL;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_GROUND], GROUND_X * GROUND_Z, xyz, gravityMoveDown);   // 땅 접촉 체크
    if (collisionObj != NULL) return collisionObj;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_WALL], WALL_COUNT, xyz, gravityMoveDown);              // 벽 접촉 체크
    if (collisionObj != NULL) return collisionObj;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_TREE], TREE_COUNT, xyz, gravityMoveDown);              // 나무 접촉 체크
    if (collisionObj != NULL) return collisionObj;
    
    // 적과의 충돌체크, 적 끼리는 충돌X, 적과 적이 쏜 총알 충돌 X
    if (object->GetObjType() != OBJECT_ENEMY && !(object->GetObjType() == OBJECT_BULLET && static_cast<CBullet*>(object)->GetShooterType() == OBJECT_ENEMY))
    {
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (enemyObj[i] == NULL || object == enemyObj[i]) continue;
            collisionObj = CollisionCheckOne(object, nextObj, enemyObj[i], ENEMY_MAX, xyz, gravityMoveDown); // 적 접촉 체크
            if (collisionObj != NULL) return collisionObj;
        }
    }
    
    // 플레이어와의 충돌체크, 적과 충돌, 플레이어가 쏘지 않은 총알과 충돌
    if (object->GetObjType() == OBJECT_ENEMY || (object->GetObjType() == OBJECT_BULLET && static_cast<CBullet*>(object)->GetShooterType() != OBJECT_PLAYER))
    {
        collisionObj = CollisionCheckOne(object, nextObj, &playerObj, 1, xyz, gravityMoveDown); // 총알 접촉 체크
        if (collisionObj != NULL) return collisionObj;
    }

    return NULL;
}

// 충돌 체크 (여러개)
CObject* CollisionCheck(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown)
{
    for (int i = 0; i < iteratorMaxCount; i++)
    {
        if (object->GetIsCollision() && nextObj.IsAABBCollision(otherObj[i]))
        {
            // 바닥에 닿는 접촉(중력, y축)
            if (xyz == 1)   *gravityMoveDown = (FLOAT)fabsf(object->GetPos().y - otherObj[i].GetPos().y) - object->GetLength().y / 2.0f - otherObj[i].GetLength().y / 2.0f;
            return &otherObj[i];
        }
    }
    return NULL;
}

// 충돌 체크 (단일)
CObject* CollisionCheckOne(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown)
{
    if (otherObj != NULL && object->GetIsCollision() && nextObj.IsAABBCollision(*otherObj))
    {
        // 바닥에 닿는 접촉(중력, y축)
        if (xyz == 1)   *gravityMoveDown = (FLOAT)fabsf(object->GetPos().y - otherObj->GetPos().y) - object->GetLength().y / 2.0f - otherObj->GetLength().y / 2.0f;
        return otherObj;
    }
    return NULL;
}

// 회전
void RotationObject(D3DXMATRIX* object, int xyz, float rotSpeed, BOOL isPlayer)
{
    FLOAT xTemp = object->_41, yTemp = object->_42, zTemp = object->_43;
    FLOAT playerViewAngleLimit = 0.4f;

    D3DXMATRIX transformMatrix(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);

    D3DXMatrixTranslation(&transformMatrix, -xTemp, -yTemp, -zTemp); // 원점으로 이동
    D3DXMatrixMultiply(object, object, &transformMatrix);

    D3DXVECTOR3 pV(0.0f, 0.0f, 0.0f);

    switch (xyz) // 회전 방향
    {
    case X_PLUS_ROT:  pV = {  object->_11,  object->_12,  object->_13 }; break;
    case X_MINUS_ROT: pV = { -object->_11, -object->_12, -object->_13 }; break;
    case Y_PLUS_ROT:  pV = {  object->_21,  object->_22,  object->_23 }; break;
    case Y_MINUS_ROT: pV = { -object->_21, -object->_22, -object->_23 }; break;
    case Z_PLUS_ROT:  pV = {  object->_31,  object->_32,  object->_33 }; break;
    case Z_MINUS_ROT: pV = { -object->_31, -object->_32, -object->_33 }; break;
    }

    D3DXMatrixRotationAxis(&transformMatrix, &pV, D3DXToRadian(rotSpeed)); // 회전
    D3DXMatrixMultiply(object, object, &transformMatrix);

    D3DXMatrixTranslation(&transformMatrix, xTemp, yTemp, zTemp); // 원래 오브젝트 위치로 이동
    D3DXMatrixMultiply(object, object, &transformMatrix);
}

// 회전 (특정 타깃 방향으로)
void RotationLookAt(CObject* object, D3DXVECTOR3 targetPos)
{
    D3DXVECTOR3 v3LookAtPlayer = targetPos - object->GetPos();
    v3LookAtPlayer.y = 0.0f;
    D3DXVECTOR3 v3Front = { object->GetMatrix()->_31, 0.0f, object->GetMatrix()->_33 };
    D3DXVec3Normalize(&v3LookAtPlayer, &v3LookAtPlayer);
    D3DXVec3Normalize(&v3Front, &v3Front);

    float dot = D3DXVec3Dot(&v3Front, &v3LookAtPlayer); // 내적 이용해서 현재 바라보는 곳과 타깃의 사이각 구하기
    if (dot > 1.0f)  dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float rotateAngle = acosf(dot);

    D3DXVECTOR3 v3Cross;
    D3DXVec3Cross(&v3Cross, &v3Front, &v3LookAtPlayer);

    if (v3Cross.y < 0.0f)   rotateAngle = -rotateAngle;

    FLOAT xTemp = object->GetPos().x, yTemp = object->GetPos().y, zTemp = object->GetPos().z;

    D3DXMATRIX transformMatrix(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);

    D3DXMatrixTranslation(&transformMatrix, -xTemp, -yTemp, -zTemp);                // 원점으로 이동
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    D3DXVECTOR3 pV(0.0f, 1.0f, 0.0f);
    D3DXMatrixRotationAxis(&transformMatrix, &pV, rotateAngle);                     // 사이각 만큼 플레이어 방향으로 회전
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    D3DXMatrixTranslation(&transformMatrix, xTemp, yTemp, zTemp);                   // 원래 오브젝트 위치로 이동
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);
}

// 점프
void _JumpProcess(CObject* object)
{
    if (object->GetObjType() == OBJECT_PLAYER)
    {
        if (static_cast<CPlayer*>(object)->GetIsJumping())  return;
        static_cast<CPlayer*>(object)->SetIsJumping(TRUE);
    }

    object->SetFallingSpeed(-JUMP_POWER);
    TranslateObject(object, DOWN_GRAVITY, object->GetFallingSpeed());
}

// 중력
void _Gravity(CPlayer* playerObj, CEnemy** enemyObj)
{
    if (TranslateObject(playerObj, DOWN_GRAVITY, playerObj->GetFallingSpeed())) // 플레이어 중력 계산
    {
        playerObj->SetFallingSpeed(GRAVITY_ACCELERATION * timer.GetDeltaTime() * 10);
        playerObj->SetIsJumping(FALSE);
    }
    else
        playerObj->SetFallingSpeed(playerObj->GetFallingSpeed() + GRAVITY_ACCELERATION * timer.GetDeltaTime());
        
    for (int i = 0; i < ENEMY_MAX; i++) // 적 중력 계산
    {
        if (enemyObj[i] == NULL)
            continue;

        if (TranslateObject(enemyObj[i], DOWN_GRAVITY, enemyObj[i]->GetFallingSpeed())) // 바닥에 닿았는지 안 닿았는지 여부에 따라 다르게 동작하도록
            enemyObj[i]->SetFallingSpeed(GRAVITY_ACCELERATION * timer.GetDeltaTime() * 10);
        else
            enemyObj[i]->SetFallingSpeed(enemyObj[i]->GetFallingSpeed() + GRAVITY_ACCELERATION * timer.GetDeltaTime());

        TranslateObject(enemyObj[i], DOWN_GRAVITY, enemyObj[i]->GetFallingSpeed());
    }
}