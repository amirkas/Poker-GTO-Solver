#include "FastHandEvaluator.h"



HandBitMask::~HandBitMask() {




}


int HandBitMask::NumCardsInHand() {

	return this->num_bitsets;
}

bool HandBitMask::AreCardsUnique() {

	

}

bool HandBitMask::IsHandFlush() {

	int num_cards = this->NumCardsInHand();
	if (num_cards == 5) {
		std::bitset<27> temp = this->hand_bits;
		temp &= FLUSH_BIT_MASK;
		return temp.count() == 1;
	}
	return false;
}



std::bitset<13> HandBitMask::GetRankBit() {

	std::bitset<27> temp = this->hand_bits >> 14;
	std::bitset<13> rank_bits(temp.to_ullong());
	return rank_bits;

}

std::bitset<4> HandBitMask::GetSuit() {

	std::bitset<27> temp = this->hand_bits >> 10;
	std::bitset<4> suit_bits(temp.to_ullong());
	return suit_bits;
}

std::bitset<4> HandBitMask::GetRankInt() {

	std::bitset<27> temp = this->hand_bits >> 6;
	std::bitset<4> rank_int_bits(temp.to_ullong());
	return rank_int_bits;
}

std::bitset<6> HandBitMask::GetRankPrime() {

	std::bitset<27> temp = this->hand_bits;
	std::bitset<6> rank_prime_bits(temp.to_ullong());
	return rank_prime_bits;
}


