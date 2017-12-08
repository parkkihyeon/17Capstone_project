#include "factoryPattern.h"

ParserFactory::ParserFactory(){} 

Parser* ParserFactory::createParser(char *line) {
	return FactoryMethod(line) ;
}


SuperParserFactory::SuperParserFactory(){

} 

Parser* SuperParserFactory::FactoryMethod(char *line) {
	strtok(line, TOKEN) ;
	char *token = new char[MIN];

	while(token = strtok(NULL, TOKEN)){
		if(strlen(token) >= MIN_LENGTH){
			string gibo_str(token) ;
			if(Korean_to_English(gibo_str.substr(2,2)) != NOT_METHOD){
				return new KoreanParser ;
			}
			else {
				if(Convert_Chinese_to_English(gibo_str.substr(2,4)) != NOT_METHOD )
					return new Chinese2 ;
				else
					return new Chinese ;
			}
		}

	}
	free(token) ;
}

