#ifndef __FACTORY__H__
#define __FACTORY__H__

#include "Parser.h"

class ParserFactory {
public :
	ParserFactory() ;
	Parser* createParser(char *line) ;
protected:
	virtual Parser* FactoryMethod(char *line) = 0 ;
};

class SuperParserFactory : public ParserFactory{
private:

public:
	SuperParserFactory() ;
	Parser* FactoryMethod(char *line) ;

};

#endif