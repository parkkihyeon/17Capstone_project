#include "factoryPattern.h"

ParserFactory::ParserFactory(){} 

Parser* ParserFactory::createParser(char *line, Parser* parser) {
	return FactoryMethod(line, parser) ;
}


SuperParserFactory::SuperParserFactory(){

} 

Parser* SuperParserFactory::FactoryMethod(char *line, Parser* parser) {
	strtok(line, TOKEN) ;
	char *token = new char[MIN];
	memset(token, 0, sizeof(token)) ;

	while(token = strtok(NULL, TOKEN)){
		if(strlen(token) >= MIN_LENGTH){
			string gibo_str(token) ;

			switch(parser->distinctParser(token)) {
			case KOREAN_PARSER : return new KoreanParser() ;
			case CHINESE_PARSER : return new ChineseParser() ;
			case CHINESE_2_PARSER : return new Chinese2Parser() ;
			case REST_TIME : break ;
			case ERROR_PARSER : 
			default : cerr << "SuperParserFactory::FactoryMethod =>  Parser Error " ; return NULL ;
			}	
		}
	}
	cerr << "Out of token " << endl ;
	return NULL ;
}

