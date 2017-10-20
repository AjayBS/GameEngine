#pragma once
#include<stdio.h>
#include "Windows.h"
#include"GLib.h"
namespace Input {

	
	void SetKeyPressed(bool changeState, unsigned int key);
	bool GetKeyPressed();
	unsigned int GetKeyValue();

	void Read();

	void Update();
	
	void SetStateChange();
	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);
}

