#ifndef __FACTORY__H__
#define __FACTORY__H__

#include "Parser.h"

class ParserFactory {
public :
	ParserFactory() ;
	Parser* createParser(char *line, Parser* parser) ;
protected:
	virtual Parser* FactoryMethod(char *line, Parser* parser) = 0 ;
};

class SuperParserFactory : public ParserFactory{
public:
	SuperParserFactory() ;
	Parser* FactoryMethod(char *line, Parser* parser) ;

};

#endif