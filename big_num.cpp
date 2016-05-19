#include "big_num.h"
#include "byte_utils.h"

const void Bignum::toString(std::string& bnStr){
	int len = BN_num_bytes(this->bn);
	unsigned char* temp = new unsigned char[len];
	BN_bn2bin(this->bn,temp);

	bnStr = std::string((char*)temp, len);
	delete[] temp;
}

void Bignum::print(std::ostream& out){
	std::string bnStr;
	toString(bnStr);

	if (bnStr.size() == 0){
		out << "0x00";
		return;
	}
	std::string strout;
	ByteUtils::convertHexArrayToString(bnStr,strout);
	std::cout << "0x" << strout;
}
	
