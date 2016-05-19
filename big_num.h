#ifndef __BIG_NUM_H__
#define __BIG_NUM_H__

#include <openssl/bn.h>
#include <string>
#include <iostream>
#include "byte_utils.h"

class Bignum {
private:
	BIGNUM* bn;

public:
	Bignum(){
		bn  = BN_new();
	}

	Bignum(BIGNUM* bn){
		this->bn  = BN_dup(bn);
	}

	~Bignum(){
		if(bn)
			BN_free(bn);
	}

	BIGNUM* duplicate()const{
		return BN_dup(bn);
	}

	operator BIGNUM*()const {
		return bn;
	}

	void setWord(unsigned long word){
		BN_set_word(bn,word);
	}

	bool operator==(const Bignum& bn2)const{
		return !BN_cmp(bn,bn2.bn);
	}

	// No se puede sobrecargar de nuevo el ==
	// dado que ya se sobrecargo el de casteo
	bool compareBN(const BIGNUM* bn2)const{
		return !BN_cmp(bn,bn2);
	}

	const void toString(std::string& bnStr);

	void print(std::ostream& out);
};



#endif //__BIG_NUM_H__
