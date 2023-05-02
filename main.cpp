#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <unordered_map>

class Stack {
  public:
    std::vector<std::string> cards;
    int number;
    int value;
    Stack() {
      cards = {};
      number = 0;
      value = 0;
    }

    void shuffle() {
      long unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
      auto rng = std::default_random_engine {seed};
      std::shuffle(std::begin(cards), std::end(cards), rng);
    }

    void dealCard(int amount, Stack& deck) {
      for (int i = 0; i < amount; i++) {
        cards.push_back(deck.cards[0]);
        number++;
        deck.cards.erase(deck.cards.begin());
        deck.number--;
      }
    }

    void assessValue() {  
      std::unordered_map<char, int> values = {
        {'2',2},
        {'3',3},
        {'4',4},
        {'5',5},
        {'6',6},
        {'7',7},
        {'8',8},
        {'9',9},
        {'0',10},
        {'J',10},
        {'Q',10},
        {'K',10},
        {'A',11}
      };
      for (int i = 0; i < cards.size(); i++) {
        value += values[cards[i][0]];
      }
    }
};

class Deck: public Stack {
  public:
    Deck() {
      cards = {"2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "0h", "Jh", "Qh", "Kh", "Ah",
               "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "0d", "Jd", "Qd", "Kd", "Ad",
               "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "0s", "Js", "Qs", "Ks", "As",
               "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "0h", "Jh", "Qh", "Kh", "Ah"};
      number = cards.size();
    }
};

void printCard(std::string card) {
  std::ifstream f("/home/louisj/Programs/blackjack/cards/" + card + ".txt");
  std::string str;
  if(f) {
    std::ostringstream ss;
    ss << f.rdbuf();
    str = ss.str();
    std::cout << str << '\n';
  }
}

int cycle(Stack hand, Deck deck, Stack dealer, int playermoney) {
  std::cout << "YOU HAVE $" << playermoney << '\n';
  std::cout << "YOUR CARDS ARE: " << '\n';
  for (int i = 0; i < hand.number; i++) {
    printCard(hand.cards[i]);
  }
  std::cout << "HIT? $10 (y/n): ";
  char input;
  std::cin >> input;
  if (input == 'y' || input == 'Y') {
    hand.dealCard(1, deck);
    playermoney -= 10;    
    hand.assessValue();
    if (hand.value > 21) {
      for (int i = 0; i < hand.number; i++) {
        printCard(hand.cards[i]);
      }
      std::cout << "YOU LOSE!\n";
      return 0;
    }
    cycle(hand, deck, dealer, playermoney);
  } 
  else if (input == 'n' || input == 'N') {
    hand.assessValue();
    dealer.assessValue(); 
    std::cout << "YOUR HAND:\n";
    for (int i = 0; i < hand.number; i++) {
      printCard(hand.cards[i]);
    }
    std::cout << "DEALER'S HAND:\n";
    for (int i = 0; i < dealer.number; i++) {
      printCard(dealer.cards[i]);
    }
    if (hand.value > dealer.value || dealer.value > 21) {
      std::cout << "YOU WIN!\n";
    } else if (hand.value < dealer.value || hand.value > 21) {
      std::cout << "YOU LOSE!\n";
    } else {
      std::cout << "TIE\n";
    }
  } else {
    std::cout << "PLEASE ENTER A VALID INPUT" << '\n';
    cycle(hand, deck, dealer, playermoney);
  }
  return 0;
}

int main() {
  Stack hand = Stack();
  Stack dealer = Stack();
  Deck deck = Deck();
  int playermoney = 100;
  deck.shuffle();
  hand.dealCard(2, deck);
  dealer.dealCard(2, deck);
  cycle(hand, deck, dealer, playermoney);
  hand.assessValue();
  return 0;
}
