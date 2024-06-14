#pragma once
#include <bitset>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <fstream>
#include <math.h>

const std::map<char, int> CARD_RANKS = { {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2} };
const int CARD_PRIME[13] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
const std::map<char, int> SUIT_VALUE = { {'s', 8}, {'c', 4}, {'d', 2}, {'h', 1} };

const short DISTINCT_STRAIGHT_FLUSHES = 10;
const short DISTINCT_QUADS = 156;
const short DISTINCT_FULL_HOUSES = 156;
const short DISTINCT_FLUSHES = 1277;
const short DISTINCT_STRAIGHTS = 10;
const short DISTINCT_TRIPS = 858;
const short DISTINCT_TWO_PAIRS = 858;
const short DISTINCT_ONE_PAIRS = 2860;
const short DISTINCT_HIGH_CARDS = 1277;

const short START_RANK_STRAIGHT_FLUSH = 1;
const short START_RANK_QUADS = 11;
const short START_RANK_FULL_HOUSE = 167;
const short START_RANK_FLUSHES = 323;
const short START_RANK_STRAIGHTS = 1600;
const short START_RANK_TRIPS = 1610;
const short START_RANK_TWO_PAIRS = 2468;
const short START_RANK_ONE_PAIRS = 3326;
const short START_RANK_HIGH_CARDS = 6186;

const std::bitset<27> STRAIGHT_BIT_MASK = std::bitset<13>().set(31);
const std::bitset<27> FLUSH_BIT_MASK = std::bitset<27>().set(15) <<= 10;

const int STRAIGHT_PRIME_VALS[10] = { 31367009, 14535931, 6678671, 2800733, 1062347, 323323, 85085, 15015, 2310, 8610 };



const int TABLE_SIZE = 7642;

class CardBitMask {

private:

	std::bitset<27> card_bits;

	//Format 
	//13 Rank Bits			- Each rank sets 1 bit to 1, from left 'A' : 1|0000|0000|0000, to right '2' : 0|0000|0000|0001
	//4  Suit Bits			- Each suit sets 1 bit to 1, Spade : 1000, Club: 0100, Diamond: 0010, Heart : 0001
	//4  Rank Bits (Int)	- Integer representation of card rank. A (14) : 1110, K (13) : 1101, ...., 2 (2) : 0010
	//6  Rank Bits (Prime)	- Prime representation of card ranks:
			//Rank:		2		3		4		5		6		7		8		9		T		J		Q		K		A
			//Prime:	2		3		5		7		11		13		17		19		23		29		31		37		41
			//bit:		000001	000011	000101	000111	001011	001101	010001	010011	010111	011101	011111	100101	101001


public:

	CardBitMask(std::bitset<27>);

	CardBitMask(char, char);

	CardBitMask(std::string);

	CreateHandBitMask(std::)

	GetCardRank();

	GetCardSuit();

	GetCardPrime();


};




class HandBitMask {

private:

	std::vector<CardBitMask> all_card_bitmasks;
	short num_bitsets;

public:


	HandBitMask(std::vector<CardBitMask>);

	HandBitMask(std::vector<std::bitset<27>>);

	HandBitMask(std::vector<std::string>);

	~HandBitMask();

	std::bitset<27> GetCombinedBitMask();

	int NumCardsInHand();

	bool AreCardsUnique();

	bool IsHandFlush();

	bool IsHandStraight();

	int GetHandPrimeValue();




	std::bitset<13> GetRankBit();

	std::bitset<4> GetSuit();

	std::bitset<4> GetRankInt();

	std::bitset<6> GetRankPrime();


};


class FastHandEvaluator{

private:

	std::string lookup_file;

	std::map<int, short>* flushes;

	std::map<int, short>* straights;

	std::map<int, short>* paired;

	std::map<int, short>* high_cards;

	bool are_hands_evaluated;

	void EvaluateAllHandRanks(short*);

	void GenerateStraightFlushesAndStraights(std::map<std::bitset<27>, short>*, std::map<std::bitset<27>, short>*);

	void GenerateQuads(std::map<std::bitset<27>, short>*);

	void GenerateFullHouses(std::map<std::bitset<27>, short>*);

	void GenerateFlushes(std::map<std::bitset<27>, short>*);

	void GenerateTrips(std::map<std::bitset<27>, short>*);

	void GenerateTwoPairs(std::map<std::bitset<27>, short>*);

	void GenerateOnePairs(std::map<std::bitset<27>, short>*);

	void GenerateAllHighCards(std::map<std::bitset<27>, short>*, int);

	int GetCardPrime(int);

	bool IsHandStraight(std::vector<int>);

	bool AreRanksUnique(std::vector<int>);
	
public:

	FastHandEvaluator(std::string, bool, bool);

	~FastHandEvaluator();


	int CreateLookupFile(std::string, bool);

	int ReadLookupFile(std::string);


	short EvaluateHandRank(HandBitMask*);

	short EvaluateHandRank(std::vector<std::string>*);

	int EvaluateWinner(std::vector<HandBitMask*>*);

	int EvaluateWinner(std::vector< std::vector<std::string>* >*);


};

