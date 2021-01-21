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
		/*Item->SetPosition(this->x, this->y);
		Item->Render();
		isDeath = true;*/

		CItem* item = new CItem(typeItem);
		item->SetPosition(this->x, this->y);
		CPlayScene* plScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		plScene->GetGrid()->AddObject(item);
		isDeath = true;



	}





}




