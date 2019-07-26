/*
 * system.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: huy
 */

#include"system.h"

trie* system::get_trie(){
	return root;
}

void system::load_stop_word(){

}

void system::build_trie(){
	//for every file
	//vector<word>
	//root.add_word(word,file)
}

void system::process_AND(){
	//vector<word> from query
	//initize vector<file> with first word
	//from second word optimize vector<file>
	//go through each file to rank up
}

void system::process_OR(){
	//vector<word> from query
	//get all file thats have one of word
	//go through each file to rank up
}

void system::process_minus(){
	//get first and second word from query
	//get all files thats have first word
	//remove files thats have second word
	//go through each files to rank up
}

void system::process_intitle(){
	//get vector<word> from query
	//get all files thats have all word like AND query
	//go through each file to check and rank up
}

void system::process_plus(){
	//process like AND
}

void system::process_type(){
	//from list of file, return file that same type as query
}

void system::process_a_price(){

}
void system::process_hashtag(){

}
void system::process_exact_match(){

}
void system::process_unknown_word(){

}
void system::process_range_number(){

}
void system::process_synonyms(){

}
void system::history(){

}
