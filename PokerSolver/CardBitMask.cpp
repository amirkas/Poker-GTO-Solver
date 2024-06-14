#include "FastHandEvaluator.h"


CardBitMask::CardBitMask(std::bitset<27> card_bitset) {

	this->card_bits = card;
}

//Convert String representation to Bit representation
CardBitMask::CardBitMask(std::string card) {

	char rank_char = card[0];
	char suit_char = card[1];

	CardBitMask(rank_char, suit_char);
}

//Convert Char representation to Bit Representation
CardBitMask::CardBitMask(char card_rank, char card_suit) {

	int rank = CARD_RANKS.at(card_rank);
	int suit_val = SUIT_VALUE.at(card_suit);
	int rank_prime = CARD_PRIME[rank - 2];

	std::bitset<27> rank_bits_prime = std::bitset<27>().set(rank_prime);

	std::bitset<27> rank_bits_int = std::bitset<27>().set(rank);
	rank_bits_int <<= 6;

	std::bitset<27> suit_bits = std::bitset<27>().set(suit_val);
	suit_bits <<= 10;



	//Start of with bitset that has 1 set at 1st bit.
	this->card_bits = std::bitset<27>().set(1);

	//To Get Rank Bits, left shift the bit set by 14 + (rank - 2), alternatively 12 + rank
	this->card_bits <<= (12 + (rank));

	//Bitwise and with created bitsets for rank int, rank prime, and suit val.
	this->card_bits |= rank_bits_prime;
	this->card_bits |= rank_bits_int;
	this->card_bits |= suit_bits;
}









std::bitset<6> CardBitMask::GetCardPrime() {

	std::bitset<27> temp = this->card_bits;
	std::bitset<6> rank_prime_bits(temp.to_ullong());
	return rank_prime_bits;
}