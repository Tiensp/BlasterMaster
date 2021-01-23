#include "Enemy.h"

#include "Grid.h"
#include "Game.h"
#include "PlayScence.h"
Enemy::Enemy()
{


}

Enemy::~Enemy()
{
}
void Enemy::Render()
{

}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	if (this->hp <= 0)
	{
		isDeath = true;
		if (this->typeItem >= 0 && this->typeItem <= 4)
		{
			Item = new CItem(typeItem);
			Item->SetPosition(this->x, this->y);
			CPlayScene* plScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			/*plScene->GetListItem().push_back(Item);*/
			plScene->GetGrid()->AddObject(Item);
		}
	}
}




