/*
 * main.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: huy
 */
#include"System.h"
#include"Library.h"
int main(){
	System SYSTEM;
	//SYSTEM.get_files_name();
	SYSTEM.InputFiles();
	SYSTEM.load_synonym();
	SYSTEM.load_stop_word();
	SYSTEM.build_trie();
	while(1){
	SYSTEM.inputSearch();
	SYSTEM. process_synonyms();
	}
	//system("pause");
	return 0;
}




