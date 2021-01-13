#include "Font.h"


CFont::CFont()
{
	ani_set = CAnimationSets::GetInstance()->Get(8);
}

CFont::~CFont()
{

}

void CFont::Render(string str, int x, int y)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '0':
			ani_set->at(26)->Render(x, y);
			break;
		case '1':
			ani_set->at(27)->Render(x, y);
			break;
		case '2':
			ani_set->at(28)->Render(x, y);
			break;
		case '3':
			ani_set->at(29)->Render(x, y);
			break;
		case '4':
			ani_set->at(30)->Render(x, y);
			break;
		case '5':
			ani_set->at(31)->Render(x, y);
			break;
		case '6':
			ani_set->at(32)->Render(x, y);
			break;
		case '7':
			ani_set->at(33)->Render(x, y);
			break;
		case '8':
			ani_set->at(34)->Render(x, y);
			break;
		case '9':
			ani_set->at(35)->Render(x, y);
			break;
		case 'A':
			ani_set->at(26)->Render(x, y);
			break;
		case 'B':
			ani_set->at(26)->Render(x, y);
			break;
		case 'C':
			ani_set->at(26)->Render(x, y);
			break;
		case 'D':
			ani_set->at(26)->Render(x, y);
			break;
		case 'E':
			ani_set->at(26)->Render(x, y);
			break;
		case 'F':
			ani_set->at(26)->Render(x, y);
			break;
		case 'G':
			ani_set->at(26)->Render(x, y);
			break;
		case 'H':
			ani_set->at(26)->Render(x, y);
			break;
		case 'I':
			ani_set->at(26)->Render(x, y);
			break;
		case 'J':
			ani_set->at(26)->Render(x, y);
			break;
		case 'K':
			ani_set->at(26)->Render(x, y);
			break;
		case 'L':
			ani_set->at(26)->Render(x, y);
			break;
		case 'M':
			ani_set->at(26)->Render(x, y);
			break;
		case 'N':
			ani_set->at(26)->Render(x, y);
			break;
		case 'O':
			ani_set->at(26)->Render(x, y);
			break;
		case 'P':
			ani_set->at(26)->Render(x, y);
			break;
		case 'Q':
			ani_set->at(26)->Render(x, y);
			break;
		case 'R':
			ani_set->at(26)->Render(x, y);
			break;
		case 'S':
			ani_set->at(26)->Render(x, y);
			break;
		case 'T':
			ani_set;
		case 'U':
			ani_set->at(26)->Render(x, y);
			break;
		case 'V':
			ani_set->at(26)->Render(x, y);
			break;
		case 'W':
			ani_set->at(26)->Render(x, y);
			break;
		case 'X':
			ani_set->at(26)->Render(x, y);
			break;
		case 'Y':
			ani_set->at(26)->Render(x, y);
			break;
		case 'Z':
			ani_set->at(26)->Render(x, y);
			break;
		case '-':
			ani_set->at(26)->Render(x, y);
			break;
		default:
			break;
		}

	}
}
