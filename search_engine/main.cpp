/*
 * main.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: huy
 */
#include"System.h"
int main(){
	System SYSTEM;
	SYSTEM.get_files_name();
	SYSTEM.load_stop_word();
	SYSTEM.build_trie();
	return 0;
}



