#pragma once
#include "gameNode.h"
#include"block.h"

enum STATE
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class game2048 :
	public gameNode
{
	typedef vector<block*> vBlock;
	typedef vector<block*>::iterator ivBlock;

private:

	vBlock _vBlock;

	int state;
	int prevState;
	bool finishMerge;
	int time;
	int timeM;
public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void addBlock();
	void keyBord();
	block* findBlock(int x,int y);

	void blockMove();
	void blockMerge();
	bool getIsMove();
	bool blockMoving(int x,int y);

	game2048() {};
	~game2048() {};
};

