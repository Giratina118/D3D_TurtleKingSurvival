#include "_TransformMatrix.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CBullet.h"
#include <math.h>

extern CPlayer playerObj;           // �÷��̾� ������Ʈ
extern CEnemy* enemyObj[ENEMY_MAX]; // �� ������Ʈ
extern Timer timer; // Ÿ�̸�

extern CObject* landformObj[OBJECT_LANDFORM_MAX];   // �������� ������Ʈ
extern LPDIRECT3DVERTEXBUFFER9* g_pVB_Array;

FLOAT tempAngle = 0.0f;

// �̵�
BOOL TranslateObject(CObject* object, int moveDir, float moveSpeed)
{
    D3DXMATRIX nextObjectMatrix; // ���� ��ġ ������ ��
    D3DXMATRIX moveDirection = GetTransformMatrix(object->GetMatrix(), moveDir, moveSpeed); // �̵� ����
    FLOAT gravityMoveDown = 0.0f;

    D3DXVECTOR3 nextMove(0, 0, 0);

    for (int xyz = 0; xyz < 3; ++xyz)
    {
        D3DXVECTOR3 tryMove = nextMove;
        nextObjectMatrix = *object->GetMatrix();

        // x y z�� ������ ���� ����Ͽ� ������ �������δ� �̵� �Ұ�
        if (xyz == 0) tryMove.x += moveDirection._41;
        if (xyz == 1) tryMove.y += moveDirection._42;
        if (xyz == 2) tryMove.z += moveDirection._43;

        nextObjectMatrix._41 += tryMove.x;
        nextObjectMatrix._42 += tryMove.y;
        nextObjectMatrix._43 += tryMove.z;

        CObject nextObj(nextObjectMatrix, object->GetLength(), object->GetRadius(), object->GetIsCollision());

        if (CollisionCheckIndex(object, nextObj, xyz, &gravityMoveDown) != NULL) continue;  // �浹 üũ
        else nextMove = tryMove;
    }

    BOOL returnCollision = FALSE;   // �ٴ�(�Ʒ��� ����)�� ��Ҵ��� üũ
    if (nextMove.y == 0)
    {
        nextMove.y = -gravityMoveDown + 0.01f; // �ٴ� �浹 �� �ٴ� �ٷ� ���� ��ġ�ϵ���
        returnCollision = TRUE;
    }

    // ���� �̵� ����
    D3DXMATRIX transformMatrix;
    D3DXMatrixTranslation(&transformMatrix, nextMove.x, nextMove.y, nextMove.z);
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    return returnCollision;
}

// �̵� ���� ����
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

// �浹 üũ ����
CObject* CollisionCheckIndex(CObject* object, CObject nextObj, int xyz, FLOAT* gravityMoveDown)
{
    CObject* collisionObj = NULL;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_GROUND], GROUND_X * GROUND_Z, xyz, gravityMoveDown);   // �� ���� üũ
    if (collisionObj != NULL) return collisionObj;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_WALL], WALL_COUNT, xyz, gravityMoveDown);              // �� ���� üũ
    if (collisionObj != NULL) return collisionObj;

    collisionObj = CollisionCheck(object, nextObj, landformObj[OBJECT_LANDFORM_TREE], TREE_COUNT, xyz, gravityMoveDown);              // ���� ���� üũ
    if (collisionObj != NULL) return collisionObj;
    
    // ������ �浹üũ, �� ������ �浹X, ���� ���� �� �Ѿ� �浹 X
    if (object->GetObjType() != OBJECT_ENEMY && !(object->GetObjType() == OBJECT_BULLET && static_cast<CBullet*>(object)->GetShooterType() == OBJECT_ENEMY))
    {
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (enemyObj[i] == NULL || object == enemyObj[i]) continue;
            collisionObj = CollisionCheckOne(object, nextObj, enemyObj[i], ENEMY_MAX, xyz, gravityMoveDown); // �� ���� üũ
            if (collisionObj != NULL) return collisionObj;
        }
    }
    
    // �÷��̾���� �浹üũ, ���� �浹, �÷��̾ ���� ���� �Ѿ˰� �浹
    if (object->GetObjType() == OBJECT_ENEMY || (object->GetObjType() == OBJECT_BULLET && static_cast<CBullet*>(object)->GetShooterType() != OBJECT_PLAYER))
    {
        collisionObj = CollisionCheckOne(object, nextObj, &playerObj, 1, xyz, gravityMoveDown); // �Ѿ� ���� üũ
        if (collisionObj != NULL) return collisionObj;
    }

    return NULL;
}

// �浹 üũ (������)
CObject* CollisionCheck(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown)
{
    for (int i = 0; i < iteratorMaxCount; i++)
    {
        if (object->GetIsCollision() && nextObj.IsAABBCollision(otherObj[i]))
        {
            // �ٴڿ� ��� ����(�߷�, y��)
            if (xyz == 1)   *gravityMoveDown = (FLOAT)fabsf(object->GetPos().y - otherObj[i].GetPos().y) - object->GetLength().y / 2.0f - otherObj[i].GetLength().y / 2.0f;
            return &otherObj[i];
        }
    }
    return NULL;
}

// �浹 üũ (����)
CObject* CollisionCheckOne(CObject* object, CObject nextObj, CObject* otherObj, int iteratorMaxCount, int xyz, FLOAT* gravityMoveDown)
{
    if (otherObj != NULL && object->GetIsCollision() && nextObj.IsAABBCollision(*otherObj))
    {
        // �ٴڿ� ��� ����(�߷�, y��)
        if (xyz == 1)   *gravityMoveDown = (FLOAT)fabsf(object->GetPos().y - otherObj->GetPos().y) - object->GetLength().y / 2.0f - otherObj->GetLength().y / 2.0f;
        return otherObj;
    }
    return NULL;
}

// ȸ��
void RotationObject(D3DXMATRIX* object, int xyz, float rotSpeed, BOOL isPlayer)
{
    FLOAT xTemp = object->_41, yTemp = object->_42, zTemp = object->_43;
    FLOAT playerViewAngleLimit = 0.4f;

    D3DXMATRIX transformMatrix(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);

    D3DXMatrixTranslation(&transformMatrix, -xTemp, -yTemp, -zTemp); // �������� �̵�
    D3DXMatrixMultiply(object, object, &transformMatrix);

    D3DXVECTOR3 pV(0.0f, 0.0f, 0.0f);

    switch (xyz) // ȸ�� ����
    {
    case X_PLUS_ROT:  pV = {  object->_11,  object->_12,  object->_13 }; break;
    case X_MINUS_ROT: pV = { -object->_11, -object->_12, -object->_13 }; break;
    case Y_PLUS_ROT:  pV = {  object->_21,  object->_22,  object->_23 }; break;
    case Y_MINUS_ROT: pV = { -object->_21, -object->_22, -object->_23 }; break;
    case Z_PLUS_ROT:  pV = {  object->_31,  object->_32,  object->_33 }; break;
    case Z_MINUS_ROT: pV = { -object->_31, -object->_32, -object->_33 }; break;
    }

    D3DXMatrixRotationAxis(&transformMatrix, &pV, D3DXToRadian(rotSpeed)); // ȸ��
    D3DXMatrixMultiply(object, object, &transformMatrix);

    D3DXMatrixTranslation(&transformMatrix, xTemp, yTemp, zTemp); // ���� ������Ʈ ��ġ�� �̵�
    D3DXMatrixMultiply(object, object, &transformMatrix);
}

// ȸ�� (Ư�� Ÿ�� ��������)
void RotationLookAt(CObject* object, D3DXVECTOR3 targetPos)
{
    D3DXVECTOR3 v3LookAtPlayer = targetPos - object->GetPos();
    v3LookAtPlayer.y = 0.0f;
    D3DXVECTOR3 v3Front = { object->GetMatrix()->_31, 0.0f, object->GetMatrix()->_33 };
    D3DXVec3Normalize(&v3LookAtPlayer, &v3LookAtPlayer);
    D3DXVec3Normalize(&v3Front, &v3Front);

    float dot = D3DXVec3Dot(&v3Front, &v3LookAtPlayer); // ���� �̿��ؼ� ���� �ٶ󺸴� ���� Ÿ���� ���̰� ���ϱ�
    if (dot > 1.0f)  dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    float rotateAngle = acosf(dot);

    D3DXVECTOR3 v3Cross;
    D3DXVec3Cross(&v3Cross, &v3Front, &v3LookAtPlayer);

    if (v3Cross.y < 0.0f)   rotateAngle = -rotateAngle;

    FLOAT xTemp = object->GetPos().x, yTemp = object->GetPos().y, zTemp = object->GetPos().z;

    D3DXMATRIX transformMatrix(1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);

    D3DXMatrixTranslation(&transformMatrix, -xTemp, -yTemp, -zTemp);                // �������� �̵�
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    D3DXVECTOR3 pV(0.0f, 1.0f, 0.0f);
    D3DXMatrixRotationAxis(&transformMatrix, &pV, rotateAngle);                     // ���̰� ��ŭ �÷��̾� �������� ȸ��
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);

    D3DXMatrixTranslation(&transformMatrix, xTemp, yTemp, zTemp);                   // ���� ������Ʈ ��ġ�� �̵�
    D3DXMatrixMultiply(object->GetMatrix(), object->GetMatrix(), &transformMatrix);
}

// ����
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

// �߷�
void _Gravity(CPlayer* playerObj, CEnemy** enemyObj)
{
    if (TranslateObject(playerObj, DOWN_GRAVITY, playerObj->GetFallingSpeed())) // �÷��̾� �߷� ���
    {
        playerObj->SetFallingSpeed(GRAVITY_ACCELERATION * timer.GetDeltaTime() * 10);
        playerObj->SetIsJumping(FALSE);
    }
    else
        playerObj->SetFallingSpeed(playerObj->GetFallingSpeed() + GRAVITY_ACCELERATION * timer.GetDeltaTime());
        
    for (int i = 0; i < ENEMY_MAX; i++) // �� �߷� ���
    {
        if (enemyObj[i] == NULL)
            continue;

        if (TranslateObject(enemyObj[i], DOWN_GRAVITY, enemyObj[i]->GetFallingSpeed())) // �ٴڿ� ��Ҵ��� �� ��Ҵ��� ���ο� ���� �ٸ��� �����ϵ���
            enemyObj[i]->SetFallingSpeed(GRAVITY_ACCELERATION * timer.GetDeltaTime() * 10);
        else
            enemyObj[i]->SetFallingSpeed(enemyObj[i]->GetFallingSpeed() + GRAVITY_ACCELERATION * timer.GetDeltaTime());

        TranslateObject(enemyObj[i], DOWN_GRAVITY, enemyObj[i]->GetFallingSpeed());
    }
}