#include "stdafx.h"
#include "game2048.h"




HRESULT game2048::init(void)
{
	IMAGEMANAGER->addImage("��", "map.bmp", 500, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ȼ���", "pixelmap.bmp", 500, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "2.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "4.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "8.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("16", "16.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("32", "32.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("64", "64.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("128", "128.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("256", "256.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("512", "512.bmp", 107, 107, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1024", "1024.bmp", 107, 107, true, RGB(255, 0, 255));

	state = STOP;
	block* temp = new block;
	temp->init(0, 0, 2);
	_vBlock.push_back(temp);

	block* temp2 = new block;
	temp2->init(0, 1, 2);
	_vBlock.push_back(temp2);

	block* temp3 = new block;
	temp3->init(0, 2, 2);
	_vBlock.push_back(temp3);

	block* temp4 = new block;
	temp4->init(0, 3, 4);
	_vBlock.push_back(temp4);

	
	addBlock();
	time = 0;
	timeM = 10;


	return S_OK;
}

void game2048::release(void)
{
}

void game2048::update(void)
{
	
	keyBord();

	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->update();
	}

	blockMove();
	blockMerge();

	/*if (state == STOP)
	{
		time++;
		if (time == 1&& timeM>5)
		{
			addBlock();
		
		}
		timeM = 0;
	}
	else
	{
		timeM++;
		time = 0;
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		addBlock();
	}

	
	

}

void game2048::render(void)
{
	IMAGEMANAGER->render("��", getMemDC());
	if (KEYMANAGER->isToggleKey('A'))
	{
		IMAGEMANAGER->render("�ȼ���", getMemDC());
	}
	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->render();
	}
}

void game2048::addBlock()
{
	
	while (_vBlock.size()!=16)
	{
		int posX = RND->getInt(4);
		int posY = RND->getInt(4);
		int rnd = RND->getInt(10);
		if (_vBlock.empty())
		{
			if (rnd == 9)
			{
				block* temp = new block;
				temp->init(posX, posY, 4);
				_vBlock.push_back(temp);
				return;
			}
			else
			{
				block* temp = new block;
				temp->init(posX, posY, 2);
				_vBlock.push_back(temp);
				return;
			}
			return;
		}
		else
		{
			
			if (findBlock(posX,posY)==NULL)
			{
				if (rnd == 9)
				{
					block* temp = new block;
					temp->init(posX, posY,4);
					_vBlock.push_back(temp);
					return;
				}
				else
				{
					block* temp = new block;
					temp->init(posX, posY,2);
					_vBlock.push_back(temp);
					return;
				}
				
			}
		}
		
	}
	return;
	
}

void game2048::keyBord()
{
	if (!getIsMove())
	{
		state = STOP;
		for (int i = 0; i < _vBlock.size(); i++)
		{
			_vBlock[i]->setIsMerge(false);
			
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			for (int i = 0; i < _vBlock.size(); i++)
			{
				_vBlock[i]->setSpeedX(-10);
			}

			

			
			state = LEFT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			for (int i = 0; i < _vBlock.size(); i++)
			{
				
				
				_vBlock[i]->setSpeedX(10);
				
			
			}
			
			state = RIGHT;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{

			for (int i = 0; i < _vBlock.size(); i++)
			{
			
				_vBlock[i]->setSpeedY(-10);
				
				
			}
			
			state = UP;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			for (int i = 0; i < _vBlock.size(); i++)
			{
				
					_vBlock[i]->setSpeedY(10);
				
			}
			
			state = DOWN;
		}
	}

}

block * game2048::findBlock(int x, int y)
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (x == _vBlock[i]->getPosX() && y == _vBlock[i]->getPosY())
		{
			return _vBlock[i];
		}
	}
	
	return NULL;
}


void game2048::blockMove()
{
	
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (state == LEFT)
		{
			if (_vBlock[i]->getPosX() > 0)
			{
				block* search = findBlock(_vBlock[i]->getPosX() - 1, _vBlock[i]->getPosY());
				if (search != NULL)
				{
					if (!blockMoving(search->getPosX(), search->getPosY()) && ((search->getValue() != _vBlock[i]->getValue()) ||search->getIsMerge()))
					{
						COLORREF rgb = GetPixel(IMAGEMANAGER->findImage("�ȼ���")->getMemDC(), _vBlock[i]->getRC().left, _vBlock[i]->getY());
						int r = GetRValue(rgb);
						int g = GetGValue(rgb);
						int b = GetBValue(rgb);

						if (r == 0 && g == 0 && b == 255)
						{
							_vBlock[i]->setX(70 + _vBlock[i]->getPosX() * 120);
							_vBlock[i]->stopBlock();
						}
					}
				}
			}
		}
		else if (state == RIGHT)
		{
			if (_vBlock[i]->getPosX() < 3)
			{
				block* search = findBlock(_vBlock[i]->getPosX() + 1, _vBlock[i]->getPosY());
				if (search != NULL)
				{
					if (!blockMoving(search->getPosX(), search->getPosY()) && ((search->getValue() != _vBlock[i]->getValue()) || search->getIsMerge()))
					{
						COLORREF rgb = GetPixel(IMAGEMANAGER->findImage("�ȼ���")->getMemDC(), _vBlock[i]->getRC().right, _vBlock[i]->getY());
						int r = GetRValue(rgb);
						int g = GetGValue(rgb);
						int b = GetBValue(rgb);

						if (r == 0 && g == 0 && b == 255)
						{
							_vBlock[i]->setX(70 + _vBlock[i]->getPosX() * 120);
							_vBlock[i]->stopBlock();
						}
					}
				}
			}
		}
		else if (state == UP)
		{
			if (_vBlock[i]->getPosY() > 0)
			{
				block* search = findBlock(_vBlock[i]->getPosX(), _vBlock[i]->getPosY() - 1 );
				if (search != NULL)
				{
					if (!blockMoving(search->getPosX(), search->getPosY()) && ((search->getValue() != _vBlock[i]->getValue()) || search->getIsMerge()))
					{
						COLORREF rgb = GetPixel(IMAGEMANAGER->findImage("�ȼ���")->getMemDC(), _vBlock[i]->getX(), _vBlock[i]->getRC().top);
						int r = GetRValue(rgb);
						int g = GetGValue(rgb);
						int b = GetBValue(rgb);

						if (r == 0 && g == 0 && b == 255)
						{
							_vBlock[i]->setY(70 + _vBlock[i]->getPosY() * 119);
							_vBlock[i]->stopBlock();
						}
					}
				}
			}
		}
		else if (state == DOWN)
		{
			if (_vBlock[i]->getPosY() < 3)
			{
				block* search = findBlock(_vBlock[i]->getPosX(), _vBlock[i]->getPosY() + 1);
				if (search != NULL)
				{
					if (!blockMoving(search->getPosX(), search->getPosY()) && ((search->getValue() != _vBlock[i]->getValue()) || search->getIsMerge()))
					{
						COLORREF rgb = GetPixel(IMAGEMANAGER->findImage("�ȼ���")->getMemDC(), _vBlock[i]->getX(), _vBlock[i]->getRC().bottom);
						int r = GetRValue(rgb);
						int g = GetGValue(rgb);
						int b = GetBValue(rgb);

						if (r == 0 && g == 0 && b == 255)
						{
							_vBlock[i]->setY(70 + _vBlock[i]->getPosY() * 119);
							_vBlock[i]->stopBlock();
						}
					}
				}
			}
		}
	}
	
}

void game2048::blockMerge()
{
	for (int n = 0; n <16; n++)
	{
		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i != j)
				{
					if (_vBlock[i]->getPosX() == _vBlock[j]->getPosX() && _vBlock[i]->getPosY() == _vBlock[j]->getPosY())
					{
						if (_vBlock[i]->getIsMove() == false && _vBlock[j]->getIsMove() == false)
						{
							_vBlock[i]->addValue(_vBlock[j]->getValue());
							_vBlock[i]->stopBlock();
							_vBlock[i]->setIsMerge(true);
							_vBlock.erase(_vBlock.begin() + j);
						}
						
					}
				}
			}
		}
	}
}

bool game2048::getIsMove()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i]->getIsMove())
		{
			return true;
		}
	}
	return false;
}

bool game2048::blockMoving(int x, int y)
{
	if (state == LEFT)
	{
		if (x == 0)
		{
			return false;
		}
		block* find=findBlock(x - 1, y);
		if (find == NULL)
		{
			return true;
		}
		else if (findBlock(x, y)->getIsMerge())
		{
			return false;
		}
		else
		{
			if (find->getValue() != findBlock(x, y)->getValue() && !blockMoving(find->getPosX(), find->getPosY()))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	}

	if (state == RIGHT)
	{
		if (x == 3)
		{
			return false;
		}
		block* find = findBlock(x + 1, y);
		if (find == NULL)
		{
			return true;
		}
		else if (findBlock(x, y)->getIsMerge())
		{
			return false;
		}
		else
		{
			if (find->getValue() != findBlock(x, y)->getValue()&& !blockMoving(find->getPosX(),find->getPosY()))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	}

	if (state == UP)
	{
		if (y == 0)
		{
			return false;
		}
		block* find = findBlock(x , y-1);
		if (find == NULL)
		{
			return true;
		}
		else if (findBlock(x, y)->getIsMerge())
		{
			return false;
		}
		else
		{
			if (find->getValue() != findBlock(x, y)->getValue() && !blockMoving(find->getPosX(), find->getPosY()))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	}

	if (state == DOWN)
	{
		if (y == 3)
		{
			return false;
		}
		else
		{
			block* find = findBlock(x, y + 1);
			if (find == NULL)
			{
				return true;
			}
			else if (findBlock(x, y)->getIsMerge())
			{
				return false;
			}
			else
			{
				if (find->getValue() != findBlock(x, y)->getValue() && !blockMoving(find->getPosX(), find->getPosY()))
				{

					return false;
				}
				else
				{

					return true;
				}
			}
		}
		

	}

	return false;
}
