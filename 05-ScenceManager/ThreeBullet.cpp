#include "ThreeBullet.h"

ThreeBullet::ThreeBullet(float _start_x, float _start_y)
{
	bullet1 = new SophiaBullet(start_x, start_y);
	//bullet2 = new SophiaBullet(_start_x, _start_y);
	//bullet3 = new SophiaBullet(_start_x, _start_y);
	bullet1->SetPosition(_start_x, _start_y);
	bullet1->Set_bullet_dir(1);
	/*bullet2->SetPosition(start_x, start_y + 15);
	bullet3->SetPosition(start_x, start_y - 15);*/
	isMove = true;
	isDone = false;
}

void ThreeBullet::Render()
{
	int ani = 0;
	bullet1->animation_set->at(0)->Render(bullet1->x, bullet1->y);
	/*bullet1->Render();
	bullet2->Render();
	bullet3->Render();*/
}
