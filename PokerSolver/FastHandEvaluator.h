#pragma once
#include <bitset>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <fstream>
#include <math.h>

#include "HandEvaluationConstants.h"

//Forward Declaration for CardBitMask and HandBitMask classes.
class CardBitMask;
class HandBitMask;

class FastHandEvaluator{

private:
	
	//Instance Variables
	std::string lookup_file;

	struct LookupData {
		std::map<int, short>* flushes;
		std::map<int, short>* paired;
		std::map<int, short>* unique_ranks;

	};
	LookupData *lookup_struct;
	bool are_hands_evaluated;

	/* Private Function Definitions */

	/*Functions that generate lookup table for hand ranks*/
	void EvaluateAllHandRanks(short*);
	static void GenerateStraightFlushesAndStraights(std::map<int, short>*, std::map<int, short>*);
	static void GenerateQuads(std::map<int, short>*);
	static void GenerateFullHouses(std::map<int, short>*);
	static void GenerateFlushes(std::map<int, short>*);
	static void GenerateTrips(std::map<int, short>*);
	static void GenerateTwoPairs(std::map<int, short>*);
	static void GenerateOnePairs(std::map<int, short>*);
	static void GenerateAllHighCards(std::map<int, short>*, int);

	/*Helper functions for lookup table generation and retrieval*/
	static int GetCardPrime(int);
	static bool IsHandStraight(std::vector<int>);
	static bool AreRanksUnique(std::vector<int>);
	
public:
	/* Constructor*/
	FastHandEvaluator(std::string, bool, bool);

	/* Deconstructor*/
	~FastHandEvaluator();

	/*File Creators/Accessors */
	int CreateLookupFile(std::string, bool);
	int ReadLookupFile(std::string);

	/*Hand Evaluators that format hands for table lookup*/
	short EvaluateHandRank(HandBitMask*);
	short EvaluateHandRank(std::vector<std::string>*);
	int EvaluateWinner(std::vector<HandBitMask*>*);
	int EvaluateWinner(std::vector< std::vector<std::string>* >*);


};

