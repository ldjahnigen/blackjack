#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

class Stack {
  public:
    std::vector<std::string> cards;
    int number;
    Stack() {
      cards = {};
      number = 0;
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

};

class Deck: public Stack {
  public:
    Deck() {
      cards = {"1h", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "Jh", "Qh", "Kh", "Ah",
              "1d", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "10d", "Jd", "Qd", "Kd", "Ad",
              "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "Js", "Qs", "Ks", "As",
              "1h", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "Jh", "Qh", "Kh", "Ah"};
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

int main() {
  Stack hand = Stack();
  Deck deck = Deck();

  deck.shuffle();
  hand.dealCard(2, deck);
  for (int i = 0; i < hand.number; i++) {
    printCard(hand.cards[i]);
  }

  return 0;
}
