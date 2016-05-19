#ifndef __BYTE_UTILS_H__
#define __BYTE_UTILS_H__

#include <string>
#include <iostream>
#include <openssl/bn.h>

class ByteUtils {
public:
	static void convertLittleToBigEndian(const std::string& littleEndian, std::string& bigEndian);

	static void convertStringBytesToHex(const std::string& in,std::string& out);

	static void convertHexArrayToString(const std::string& in,std::string& out);

	static void removeFrontBytes(const std::string& in ,std::string& out,int n);
	
	static void removeBytes(const std::string& in ,std::string& out,char match);

	static unsigned int convertStringBytesToUint(const std::string& in);

	static void printBIGNUM(std::ostream& out, BIGNUM *bn);

private:
	static char toHexa(char num);
	static char toASCII(char num);
};

#endif // __BYTE_UTILS_H__