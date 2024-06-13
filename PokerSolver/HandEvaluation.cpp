#include "HandEvaluation.h"


std::string ordered_cards = "AKQJT98765432";

std::map<char, int> *card_rank_map;

bool HandEvaluator::CardRankComparator(std::string card_a, std::string card_b) {

	int card_a_rank = GetCardRank(card_a);
	int card_b_rank = GetCardRank(card_b);

	return card_a_rank > card_b_rank;
}

void HandEvaluator::SortHandByRank(std::pair < std::string, std::string>* hole_cards, std::vector<std::string>* board, std::vector<std::string>* sorted_hand) {

	//Assert size of sorted_hand vector is bigger than size of board + size of hole cards.
	assert(sorted_hand->size() == (2 + board->size()));

	//Insert board cards into vector to be sorted
	for (std::string card : *board) {
		sorted_hand->push_back(card);
	}
	//Insert hole cards into vector to be sorted
	sorted_hand->push_back(hole_cards->first);
	sorted_hand->push_back(hole_cards->second);

	//Sort hand using CardRankComparator
	std::sort(sorted_hand->begin(), sorted_hand->end(), CardRankComparator);
}
	

int HandEvaluator::GetCardRank(std::string card) {

	char card_value = card[0];
	return this->card_rank_map->at(card_value);
}

char HandEvaluator::GetCardSuit(std::string card) {
	return card[1];
}


//Called by FindHighestStraight to check for wheel, input is Set created in FindHighestStraight function
//Edge case for checking for 5-A straight (Colloqially known as the Wheel)
bool HandEvaluator::CheckWheelStraight(std::set<int> *sorted_hand_set) {

	//Assert that the sorted_hand vector has at least 5 cards
	assert(sorted_hand_set->size() >= 5);

	//Check if first card in sorted_hand is A. If not, wheel is not possible.
	int first_card_rank = *(sorted_hand_set->begin());
		
	if (first_card_rank == 14) {

		std::set<int> wheel_ranks = { 2, 3, 4, 5 };

		//Check if sorted_hand_set is superset of wheel_ranks.
		return std::includes(sorted_hand_set->begin(), sorted_hand_set->end(), wheel_ranks.begin(), wheel_ranks.end());
	}
	return false;
}


//Returns rank of the high card of a straight
//Example : Hand of {K, K, Q, J, T, 9, 8} returns 13 Highest Straight = K-9
//Returns 0 if no straight found.
int HandEvaluator::FindHighestStraight(std::vector<std::string>* sorted_hand) {

	//Assert that the sorted_hand vector has at least 5 cards
	assert(sorted_hand->size() >= 5);

	std::set<int> sorted_hand_set;

	//Add sorted_hand card ranks to set
	for (std::string card : *(sorted_hand)) {
		int curr_rank = GetCardRank(card);
		sorted_hand_set.insert(curr_rank);
	}

	size_t num_cards = sorted_hand_set.size();
	int high_end = 0;
	bool straight_found = false;
	if (num_cards >= 5) {

		//Iterator for high end and low end of straight.
		auto high_itr = sorted_hand_set.begin();
		auto low_itr = std::next(sorted_hand_set.begin(), 4);

		int pos = 0;
		for (pos; pos < num_cards - 4; pos++) {

			int high_rank = *high_itr;
			int low_rank = *low_itr;
			if (high_rank - low_rank == 4) {
				high_end = std::max(high_rank, high_end);
				straight_found = true;
				break;
			}
			high_itr = std::next(high_itr);
			low_itr = std::next(high_itr);
		}
	}
	//If straight not found, check for Wheel straight and set return value if found.
	if (!straight_found) {
		if (CheckWheelStraight(&sorted_hand_set)) {
			high_end = 5;
		}
	}
		
	return high_end;
}

//Returns rank of high card of straight flush (Royal flush has rank 14 for A high straight flush)
//Returns 0 if no straight flush exists
//Function is called after checking if straights and flushes are possible. Only need to check if straight exists.
int HandEvaluator::FindHighestStraightFlush(std::vector<std::string>* sorted_hand, int straight_rank, char flush_suit) {

	//Check if straight exists. If it doesn't, return 0 for no straight flush
	if (straight_rank == 0) {
		return 0;
	}

	//Iterate through all cards in sorted_hand that match flush_suit, starting from high end of the identified straight.
	//Count number of consecutive cards until a break is found, which would restart the counter.
	//Terminate early if number of cards left - count < 5 or if consecutive_count = 5.
	int consecutive_count = 0;
	int prev_rank = straight_rank + 1;
	size_t num_cards_left = sorted_hand->size();
	bool ace_of_suit_seen = false; //Used for Wheel Straight Flush Edge Case
	for (std::string card : *sorted_hand) {
			
		//Edge case for Wheel straight flush 5 - A. If A of suit seen, consecutive count = 3 and card rank = 2,return wheel straight flush. 
		if (consecutive_count == 3 && ace_of_suit_seen && GetCardSuit(card) == flush_suit && GetCardRank(card) == 2) {
			return 5; //5 is the high part of wheel straight flush
		}
			
		//Early termination if there are not enough cards left to make straight flush
		if (num_cards_left - consecutive_count < 5) {
			return 0;
		}

		if (GetCardSuit(card) == flush_suit) {
			int card_rank = GetCardRank(card);
			//Stores info for Wheel Straight Flush Edge Case
			if (card_rank == 14) {
				ace_of_suit_seen = true;
			}
			if (card_rank == prev_rank - 1) {
				consecutive_count += 1;
			}
			else {
				consecutive_count = 1;
			}
			prev_rank = card_rank;
		}
		//Early termination when highest straight flush found.
		//Current card_rank + 4 => rank of high end of straight flush.
		if (consecutive_count == 5) {
			int card_rank = GetCardRank(card);
			return card_rank + 4;
		}
		num_cards_left -= 1;
	}
}

	

void HandEvaluator::PairAnalysis(std::vector <std::string>* sorted_hand, PairAnalysisData *pair_data_struct) {

	//Map that has key = card rank, value = card count, sorted in descending order
	std::map<int, int, std::greater<int> > card_count;
	for (std::string card : *sorted_hand) {
		int card_rank = GetCardRank(card);
		//If card rank already seen, update count.
		if (card_count.find(card_rank) != card_count.end()) {
			card_count[card_rank]++;
		}
		//Else add card_rank to map with count 1
		else {
			std::pair<int, int> temp = std::make_pair(card_rank, 1);
			card_count.insert(temp);
		}
	}

	//Iterate through map and add to pair_data_struct
	std::map<int, int>::iterator it;
	for (it = card_count.begin(); it != card_count.end(); it++) {
		int card_rank = (*it).first;
		int count = (*it).second;
			
		switch (count) {
		case 1:
			pair_data_struct->high_cards[pair_data_struct->high_card_count] = card_rank;
			pair_data_struct->high_card_count += 1;
			break;
		case 2:
			pair_data_struct->pair[pair_data_struct->pair_count] = card_rank;
			pair_data_struct->pair_count += 1;
			break;
		case 3:
			pair_data_struct->three_of_kind[pair_data_struct->three_of_kind_count] = card_rank;
			pair_data_struct->three_of_kind_count += 1;
			break;
			
		case 4:
			pair_data_struct->four_of_kind[pair_data_struct->four_of_kind_count] = card_rank;
			pair_data_struct->four_of_kind_count += 1;
			break;
		}
	}
}
	
	 
	



//Quick check if straight possible, saves computation for finding straight flushes and straights.
//For sorted board, if either the 3rd and 4th card, or the 4th and 5th card are consecutive, there exists a possible straight.
bool HandEvaluator::IsStraightPossible(std::vector <std::string>* sorted_hand) {

	bool possible_straight = false;
	int third_card_rank = GetCardRank(*(sorted_hand->begin() + 2));
	int fourth_card_rank = GetCardRank(*(sorted_hand->begin() + 3));
	if (third_card_rank - fourth_card_rank == 1) {
		return true;
	}
	int fifth_card_rank = GetCardRank(*(sorted_hand->begin() + 4));
	if (fourth_card_rank - fifth_card_rank == 1) {
		return true;
	}
	return possible_straight;
}

//Returns char of possible flush. 
//Returns null char '\0' if no flush possible
char HandEvaluator::IsFlushPossible(std::vector <std::string>* sorted_hand) {

	int spade_count = 0;
	int club_count = 0;
	int heart_count = 0;
	int diamond_count = 0;

	int highest_count = 0;
	char highest_count_char = '\0';
		
	int pos = 0;
	for (std::string card : *sorted_hand) {
		//If 4th position reached with a max of suit count of 1 for every suit, flushes are not possible (there are only 3 more cards)
		//Terminate function and early and return null character
		if (pos >= 4 && highest_count <= 1) {
			return '\0';
		}
		char suit = GetCardSuit(card);
		switch (suit) {
		case 's':
			spade_count++;
			if (spade_count > highest_count) {
				highest_count = spade_count;
				highest_count_char = 's';
			}
			break;
		case 'c':
			club_count++;
			if (club_count > highest_count) {
				highest_count = club_count;
				highest_count_char = 'c';
			}
			break;
		case 'h':
			heart_count++;
			if (heart_count > highest_count) {
				highest_count = heart_count;
				highest_count_char = 'h';
			}
			break;
		case 'd':
			diamond_count++;
			if (diamond_count > highest_count) {
				highest_count = diamond_count;
				highest_count_char = 'd';
			}
			break;
		}
		if (highest_count >= 5) {
			return highest_count_char;
		}
		pos++;
	}
	return highest_count_char;
}


//Constructor for HandEvaluator Class
HandEvaluator::HandEvaluator() {

	//Initialize card rank map
		
	card_rank_map = new std::map<char, int>;
	//Fill Card Rank map

	int rank = 14;
	int i;
		
	for (i = 0; i < 13; i++) {
		char card = ordered_cards[i];
		std::pair<char, int> card_rank_pair = std::make_pair(card, rank);
		card_rank_map->insert(card_rank_pair);
		rank -= 1;
	}
	
}

HandEvaluator::~HandEvaluator() {
	delete(card_rank_map);
}



//Returns pointer to HandStrength struct of format: {hand class, hand class strength}
//Hand class refers to the rank of hand class from straight flush (9) to high card (1).
HandStrength* HandEvaluator::EvaluateHandStrength(std::pair < std::string, std::string> *hole_cards, std::vector<std::string> *board) {

	//Initialize Structs.
	HandStrength* hand_strength_struct = new HandStrength;
	PairAnalysisData* pair_analysis_struct = new PairAnalysisData;
	hand_strength_struct->pair_data = pair_analysis_struct;
		
	int num_board_cards = (int)board->size();
	//Create new sorted vector that combines hole cards and board cards.
	std::vector<std::string>* all_cards = new std::vector<std::string>(num_board_cards + 2);
		
	SortHandByRank(hole_cards, board, all_cards);

	EvaluateHandStrength(all_cards, hand_strength_struct);

	return hand_strength_struct;
}


//Updates hand_strength_data with data regarding hand strength including:
//	- Card Rank representation of player's best 5 card hand, using any combination of 0-2 hole cards and 3-5 community cards.
//	- Hand Class (1 - 9) from High Card to Straight Flush 
//	- Pointer to PairAnalysisData which stores information of the pairs a hand has (4 of a kind, 3 of a kind, pairs and high cards)
// 
//Evaluates stronger class of hands before weaker ones to avoid unnecessary computation
void HandEvaluator::EvaluateHandStrength(std::vector<std::string>* sorted_hand, HandStrength* hand_strength_data) {

	//Check if straight is possible
	bool straight_possible = IsStraightPossible(sorted_hand);
	int straight_rank = -1; //Start as -1 as Checking for straight flush may update it.
	//Iniitalize flush suit as placeholder 'N', this will be used to identify if flush is evaluated later.
	char flush_suit = 'N';

	//If straight possible, check for straight flush.
	//Must get suit for flush
	if (straight_possible) {

		flush_suit = IsFlushPossible(sorted_hand);
		//If flush exists, find possible straight.
		if (flush_suit != '\0') {
			straight_rank = FindHighestStraight(sorted_hand);
			int straight_flush_rank = FindHighestStraightFlush(sorted_hand, straight_rank, flush_suit);
			if (straight_flush_rank > 0) {

				hand_strength_data->hand_class = 9;
				//Edge case for 5 high straight flush which includes A (rank 14)
				if (straight_flush_rank == 5) {
					int r = 5;
					for (int i = 0; i < 4; i++) {
						hand_strength_data->hand[i] = r;
						r--;
					}
					hand_strength_data->hand[4] = 14;
				}
				else {
					int r = straight_flush_rank;
					for (int i = 0; i < 5; i++) {
						hand_strength_data->hand[i] = r;
						r--;
					}
				}
				//Straight Flush found, return early
				return;
			}
		}
	}

	//Do pair Analysis to check for next 2 classes: 8: four of a kind, 7: full house
	PairAnalysis(sorted_hand, hand_strength_data->pair_data);

	//Create temp pointer for easier access
	PairAnalysisData* data_ptr = hand_strength_data->pair_data;

	//Hand is 4 of a kind, store as [Kicker, x, x, x, x] x = rank for 4 of a kind
	if (data_ptr->four_of_kind_count == 1) {
		//Find kicker in pair_data
		int kickers[3] = { data_ptr->three_of_kind[0], data_ptr->pair[0], data_ptr->high_cards[0] };
		int highest_kicker = *std::max_element(kickers, kickers + 3);
			

		//Update hand_strength_data
		hand_strength_data->hand_class = 8;
		hand_strength_data->hand[0] = highest_kicker;
		for (int i = 1; i < 5; i++) {
			hand_strength_data->hand[i] = data_ptr->four_of_kind[0];
		}
		//Four of a kind found, return early.
		return;
	}

	//Check if full house exists: 
	//	- three of a kind count = 1 and pair_count >= 1
	//	- three of a kind count = 2

	if (data_ptr->three_of_kind_count == 2 || (data_ptr->three_of_kind_count == 1 && data_ptr->pair_count >= 1)) {
		//Full house exists. Find best combination.
		int three_card_rank = data_ptr->three_of_kind[0];
			
		int potential_two_card_rank = 0;
		if (data_ptr->three_of_kind_count == 2) {
			int other_three_card_rank = data_ptr->three_of_kind[2];;
			potential_two_card_rank = other_three_card_rank;
		}
			

		//Find best 2 card portion of full house.
		int two_card_rank = std::max(data_ptr->pair[0], potential_two_card_rank);

		//Update hand_strength data
		hand_strength_data->hand_class = 7;
		for (int j = 0; j < 3; j++) {
			hand_strength_data->hand[j] = three_card_rank;
		}
		for (int k = 3; k < 5; k++) {
			hand_strength_data->hand[k] = two_card_rank;
		}

		//Full house found, end early
		return;
	}

	//Check if flush was evaluated earlier, if not, find flush suit if it exists and update_hand_strength.
	if (flush_suit == 'N') {
		flush_suit = IsFlushPossible(sorted_hand);
	}
	//Flush found => Update Hand strength
	if (flush_suit != '\0') {
		int cards_added_cnt = 0;
		for (std::string card : *sorted_hand) {
			if (cards_added_cnt == 5) {
				break;
			}
			char suit = GetCardSuit(card);
			if (suit == flush_suit) {
				hand_strength_data->hand[cards_added_cnt] = GetCardRank(card);
				cards_added_cnt++;
			}
		}
		hand_strength_data->hand_class = 6;
		return;
	}

	//Check if straight was evaluated earlier, if not, find potential straight and update hand_strength
	if (straight_rank == -1) {
		straight_rank = FindHighestStraight(sorted_hand);
	}
	if (straight_rank > 0) {
		//Straight found, update hand_strength_data
		hand_strength_data->hand_class = 5;
		int card_rank = straight_rank;
		//Edge case for Wheel Straight
		if (card_rank == 5) {
			int r = 5;
			for (int i = 0; i < 4; i++) {
				hand_strength_data->hand[i] = r;
				r--;
			}
			hand_strength_data->hand[4] = 14;
		}
		else {
			for (int i = 0; i < 5; i++) {
				hand_strength_data->hand[i] = card_rank;
				card_rank -= 1;
			}
		}
		return;
	}

	//If 2 pair exists, find best 2 pair using first 2 values of pair array and kicker. 
	if (data_ptr->pair_count >= 2) {

		int high_pair_rank = data_ptr->pair[0];
		int low_pair_rank = data_ptr->pair[1];
		int kicker = data_ptr->high_cards[0];
		if (data_ptr->pair_count == 3) {
			kicker = std::max(kicker, data_ptr->pair[2]);
		}
			

		//Update hand strength data
		hand_strength_data->hand_class = 3;
		hand_strength_data->hand[0] = high_pair_rank;
		hand_strength_data->hand[1] = high_pair_rank;
		hand_strength_data->hand[2] = low_pair_rank;
		hand_strength_data->hand[3] = low_pair_rank;
		hand_strength_data->hand[4] = kicker;
		return;
	}

	//1 pair
	if (data_ptr->pair_count == 1) {
			
		hand_strength_data->hand_class = 2;
		hand_strength_data->hand[0] = data_ptr->pair[0];
		hand_strength_data->hand[1] = data_ptr->pair[0];
		for (int i = 0; i < 3; i++) {
			hand_strength_data->hand[i + 2] = data_ptr->high_cards[i];
		}
		return;
	}

	//Hand is only high card, update hand strength 

	hand_strength_data->hand_class = 1;
	for (int i = 0; i < 5; i++) {
		hand_strength_data->hand[i] = data_ptr->high_cards[i];
	}
	return;
		
}



//Returns 1 if IP player has stronger hand, -1 if OOP player has stronger hand, 0 for equal hand strength
int HandEvaluator::StrongerHand(std::pair < std::string, std::string> *hole_cards_IP, std::pair < std::string, std::string> *hole_cards_OOP, std::vector<std::string> *board) {

	//Initialize Structs.
	HandStrength* hand_strength_IP = new HandStrength;
	PairAnalysisData* pair_analysis_IP = new PairAnalysisData;
	hand_strength_IP->pair_data = pair_analysis_IP;

	HandStrength* hand_strength_OOP = new HandStrength;
	PairAnalysisData* pair_analysis_OOP = new PairAnalysisData;
	hand_strength_OOP->pair_data = pair_analysis_OOP;


	int num_board_cards = (int)board->size();
	//Create new sorted vector that combines hole cards and board cards.
	std::vector<std::string>* all_cards_IP = new std::vector<std::string>(num_board_cards + 2);
	std::vector<std::string>* all_cards_OOP = new std::vector<std::string>(num_board_cards + 2);

	SortHandByRank(hole_cards_IP, board, all_cards_IP);
	SortHandByRank(hole_cards_OOP, board, all_cards_OOP);

	//Evaluate each player's Hand Strength with EvaluateHandStrength()
	EvaluateHandStrength(all_cards_IP, hand_strength_IP);
	EvaluateHandStrength(all_cards_OOP, hand_strength_OOP);


	//Compare the hand strength of each player to determine the winner.


	int winner;
	//If hand class is different, the higher ranked class is the winner.
	int hand_class_diff = hand_strength_IP->hand_class - hand_strength_OOP->hand_class;
	if (hand_class_diff != 0) {
		if (hand_class_diff > 0) {
			winner = 1;
		}
		else {
			winner = -1;
		}
	}
	//If hand class is the same, the strength of the class is compared.
	else {

		int first_card_IP = hand_strength_IP->hand[0];
		int first_card_OOP = hand_strength_OOP->hand[0];
		int first_card_diff = 0;

		if (first_card_IP > first_card_OOP) {
			first_card_diff = 1;
		}
		else if (first_card_IP < first_card_OOP) {
			first_card_diff = -1;
		}
			
		int hand_class = hand_strength_IP->hand_class;
		switch (hand_class) {
		//Straight Flush compare rank of first card of each persons hand.
		case 9:
		//4 of a kind, compare each players kicker as there must be 4 of a kind within the community cards (high card)
		case 8:
		//Straight: Compare rank of first card of each persons hand
		case 5:
			winner = first_card_diff;
			break;

		//Full house, compare the three of a kind portion first using first card, if equal, compare the 2 of a kind portion using 4th card.
		case 7:
			if (first_card_diff != 0) {
				winner = first_card_diff;
			}
			else {
				int fourth_card_IP = hand_strength_IP->hand[3];
				int fourth_card_OOP = hand_strength_OOP->hand[3];
				winner = 0;
				if (fourth_card_IP > fourth_card_OOP) {
					winner = 1;
				}
				if (fourth_card_IP < fourth_card_OOP) {
					winner = -1;
				}
			}
			break;
		//Flush, iterate through 2 boards until 1 of ranks doesn't match, winner is determined by higher rank.
		//If all cards same, both players have same flush
		case 6:
			winner = 0;
			for (int i = 0; i < 5; i++) {
					
				int rank_one = hand_strength_IP->hand[i];
				int rank_two = hand_strength_OOP->hand[i];
				if (rank_one != rank_two) {
					if (rank_one > rank_two) {
						winner = 1;
					}
					else{
						winner = -1;
					}
					break;
				}
			}
			break;

			

		//Three of a kind - Same as full house, 5th card compared if 1st card and 4th card are the same.
		case 4:
			if (first_card_diff != 0) {
				winner = first_card_diff;
			}
			else {
				int fourth_card_IP = hand_strength_IP->hand[3];
				int fourth_card_OOP = hand_strength_OOP->hand[3];
					
				//First Kicker is same => compare second kicker.
				if (fourth_card_IP == fourth_card_OOP) {
					int fifth_card_IP = hand_strength_IP->hand[4];
					int fifth_card_OOP = hand_strength_OOP->hand[4];
					winner = 0;
					if (fifth_card_IP > fifth_card_OOP) {
						winner = 1;
					}
					else if (fifth_card_IP < fifth_card_OOP) {
						winner = -1;
					}
				}

				//First kicker is higher for IP
				else if (fourth_card_IP > fourth_card_OOP) {
					winner = 1;
				}

				//First kicker is higher for OOP
				else (fourth_card_IP < fourth_card_OOP) {
					winner = -1;						
				}
			}
			break;

		//2 pair Compare first pair using 1st card, if same => compare 2nd pair using 3rd card, if same compare kicker using 5th card
		case 3:
			if (first_card_diff != 0) {
				winner = first_card_diff;
			}
			else {
				int third_card_IP = hand_strength_IP->hand[2];
				int third_card_OOP = hand_strength_OOP->hand[2];
				if (third_card_IP > third_card_OOP) {
					winner = 1;
				}
				else if (third_card_IP < third_card_OOP) {
					winner = -1;
				}
				//2nd pair is same, check kicker
				else {
					int fifth_card_IP = hand_strength_IP->hand[4];
					int fifth_card_OOP = hand_strength_OOP->hand[4];
					winner = 0;
					if (fifth_card_IP > fifth_card_OOP) {
						winner = 1;
					}
					else if (fifth_card_IP < fifth_card_OOP) {
						winner = -1;
					}
				}
			}break;

		//1 pair: Compare first pair using first card, if same, iterate through hand until different rank seen.
		case 2:
			if (first_card_diff != 0) {
				winner = first_card_diff;
			}
			else {
				winner = 0;
				for (int i = 2; i < 5; i++) {
					int rank_IP = hand_strength_IP->hand[i];
					int rank_OOP = hand_strength_OOP->hand[i];
					if (rank_IP > rank_OOP) {
						winner = 1;
						break;
					}
					if (rank_IP < rank_OOP) {
						winner = -1;
					}
				}
			}break;

		//High Card: iterate through hand until different rank seen.
		case 1:
			winner = 0;
			for (int i = 0; i < 5; i++) {
				int rank_IP = hand_strength_IP->hand[i];
				int rank_OOP = hand_strength_OOP->hand[i];
				if (rank_IP > rank_OOP) {
					winner = 1;
					break;
				}
				if (rank_IP < rank_OOP) {
					winner = -1;
				}
			}
			break;
		}
			
	}

	//Free data structures before returning result of winner.
	delete(hand_strength_IP);
	delete(pair_analysis_IP);

	delete(hand_strength_OOP);
	delete(pair_analysis_OOP);

	delete(all_cards_IP);
	delete(all_cards_OOP);

	return winner;
}
	



