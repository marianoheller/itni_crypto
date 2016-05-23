#include "byte_utils.h"
#include <cstdlib>


void ByteUtils::convertStringBytesToHex(const std::string& in,std::string& out){
	std::string temp = in;
	std::string::const_iterator it = temp.begin();
	out.clear();
				
	// Remove NULL terminator if exists
	if(temp.at(temp.length()-1)=='\0')
		temp.erase(temp.length()-1);    
	    
    if(temp.size()%2!=0)    
        temp.erase(temp.length()-1);
    
	while(it!=temp.end()){
		char c1 = *it;
		char c2 = *(it+1);
		unsigned char result = (unsigned char)toHexa(c1);
		result  = (result<<4);
		result  += (unsigned char)toHexa(c2);
		out.push_back(result);
		++++it;
	}
}

void ByteUtils::convertHexArrayToString(const std::string& in,std::string& out){
	std::string temp = in;
	std::string::const_iterator it = temp.begin();
	out.clear();
		
	unsigned char mask = 0x0F;
	for(;it!=temp.end();++it){
		unsigned char temp = *it;
		char c1 = ( ( (temp)>>4 )&mask );
		char c2 = ( ( (temp) )&mask );
		c1 = toASCII(c1);
		c2 = toASCII(c2);
		out.push_back(c1);
		out.push_back(c2);
	}
}

void ByteUtils::removeFrontBytes(const std::string& in ,std::string& out,int n){
	out = in.substr(n);
}

void ByteUtils::printBIGNUM(std::ostream& out, BIGNUM *bn){
	int len = BN_num_bytes(bn);
	if (len == 0){
		out << "0x00";
		return;
	}

	unsigned char* tmp = new unsigned char[len];		
	BN_bn2bin(bn, tmp);
	std::string strout;
	convertHexArrayToString(std::string((char*)tmp,len),strout);
	std::cout << "0x" << strout;

	delete[] tmp;
}

char ByteUtils::toHexa(char num){
	if(num<65)
		return (num- 48);
	else if(num<90)
		return (num - 55);
	else
		return (num - 87);
}

char ByteUtils::toASCII(char num){
	// hasta el 9 sumo 0x30 despues 
	// hay que saltar a las letras mayusculas
	if(num<10)
		return (num+ 48);
	else
		return (num+ 55);
}

void ByteUtils::removeBytes(const std::string& in ,std::string& out,char match){
	out = in;
	int pos;
	while ( (pos = out.find(match)) != std::string::npos ){
		out.erase(pos,1);
	}
}

unsigned int ByteUtils::convertStringBytesToUint(const std::string& in){
	return ((unsigned int)atoi(in.c_str()));
}

void ByteUtils::convertLittleToBigEndian(const std::string& littleEndian, std::string& bigEndian){
	std::string temp = littleEndian;
	std::string::const_reverse_iterator it;
	bigEndian.clear();

	for (it = temp.rbegin();it!=temp.rend(); it++){
		bigEndian.push_back(*it);
	}
}
