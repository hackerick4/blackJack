#include<iostream>
#include<stdio.h>
#include<time.h>
#include<vector>
#include <cstdlib>
using namespace std;
#ifndef Card_CLASS
#define Card_CLASS
enum Suit{
    club, diamond, heart, spade
};
class Card{
    public:
        Card(Suit s, int n){
            suit = s;   
            number = n;
        }
        void operator= (const Card & other){
            suit = other.suit;
            number = other.number;
        }
        Suit get_suit();
        int get_number();
        void print_card();
    private:
        Suit suit;
        int number;
};
Suit Card::get_suit(){
    return suit;
}
int Card::get_number(){
    if(number < 10){
        return number+1;
    }else{
        return 10;
    }
}
void Card::print_card(){
    cout <<  get_suit() << " " << get_number() << endl;
}
class DeckOfCard{
    public:
        DeckOfCard(int n);
        DeckOfCard();
        int get_num_of_decks();
        void shuffle();
        void make_up();
        void print();
        Card get_next();
        void set_num_of_decks(int n);
        void set_shuffle_percent(double percent_of_cards_to_shuffle);
        void add_running_count(int count);
        int get_running_count();
        double get_true_count();
    private:
        int card_index;
        int num_of_decks;
        double pocts;
        vector<Card> cards;
        void swap_card(Card &card1, Card &card2);
        void create_deck_of_cards(int n);
        void modify_count(int num);
        int running_count;
        double true_count;
};
DeckOfCard::DeckOfCard(){
    create_deck_of_cards(1);
}
DeckOfCard::DeckOfCard(int n){
    create_deck_of_cards(n);
}
void DeckOfCard::set_shuffle_percent(double percent_of_cards_to_shuffle){
    pocts = percent_of_cards_to_shuffle;
}
void DeckOfCard::create_deck_of_cards(int n){
    running_count = 0;
    num_of_decks = n;
    card_index = 0;
    cards.clear();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 52; j++){
            Card card((Suit)(j/13), (int)(j%13));
            cards.push_back(card);
        }
    }
}
void DeckOfCard::set_num_of_decks(int n){
    create_deck_of_cards(n);
}
int DeckOfCard::get_num_of_decks(){
    return num_of_decks;
}
void DeckOfCard::shuffle(){
    srand(time(NULL));
    for(int i = 52*num_of_decks-1; i >= 0; i--){
        int r = rand()%(i+1);
        swap_card(cards[i], cards[r]);
    }
    running_count = 0;
}
void DeckOfCard::make_up(){
    swap_card(cards[0], cards[44]);//6
    swap_card(cards[1], cards[46]);//8
}

void DeckOfCard::swap_card(Card &card1, Card &card2){
    Card tmp = card1;
    card1 = card2;
    card2 = tmp;
    return;
}
Card DeckOfCard::get_next(){
    Card nextCard = cards[card_index];
    card_index++;
    if(num_of_decks*52 - card_index < (int)(num_of_decks*52*pocts)){
        shuffle();
        card_index = 0;
    }
    modify_count(nextCard.get_number());
    return nextCard;
}
void DeckOfCard::modify_count(int num){
    if(num <= 6 && num >=  2){
        add_running_count(1);
    }else if(num == 1 || num == 10){
        add_running_count(-1);
    }
    return;
}
void DeckOfCard::print(){
    for(int i = 0; i < num_of_decks*52; i++){
        cout << (int)cards[i].get_suit() << " " << (int)cards[i].get_number() << endl;
    }
    return;
}
void DeckOfCard::add_running_count(int count){
    running_count += count;
}
int DeckOfCard::get_running_count(){
    return running_count;
}
double DeckOfCard::get_true_count(){
    return (double)running_count*52/(52*num_of_decks - card_index);
}

/*
int main(){
    DeckOfCard doc;
    doc.set_num_of_decks(8);
    doc.print();
    doc.shuffle();
    doc.make_up();
    doc.print();
    doc.get_next().printCard();
    return 0;
}*/
#endif
