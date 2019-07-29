/*
 * main.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: huy
 */
#include"System.h"
int main(){
	System SYSTEM;
	//SYSTEM.get_files_name();
	SYSTEM.InputFiles();
	SYSTEM.load_stop_word();
	SYSTEM.build_trie();
	SYSTEM.inputSearch();
	SYSTEM.process_intitle(SYSTEM.getSearch());
	system("pause");
	return 0;
}



