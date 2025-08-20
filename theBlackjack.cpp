#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

struct Card {
    string rank;
    string suit;
    int value;
};

void deal(vector<Card>& hand, vector<Card>& deck) {
    Card card = deck.back();
    deck.pop_back();
    hand.push_back(card);
}

int calculateHandTotal(vector<Card>& hand) {
    int aceTotal = 0;
    int total = 0;
    for (const Card& card : hand) {
        if (card.rank == "J" || card.rank == "Q" || card.rank == "K") { total += 10; }
        else if (card.rank == "A") {
            total += 1;
            aceTotal++;
        }
        else {
            total += stoi(card.rank);
        }
    }
    if (aceTotal > 0 && total + 10 <= 21) {
        total += 10;
    }
    return total;
};

void printPlayerHand(vector<Card>& playerHand) {
    int total = calculateHandTotal(playerHand);
    cout << "Your hand: ";
    for (const Card& card : playerHand) {
        cout << "[" << card.rank << " of " << card.suit << "] ";
    }
    cout << "Total: " << total << endl;
}

void printDealerHand(vector<Card>& dealerHand) {
    int total = calculateHandTotal(dealerHand);
    cout << "Dealer's hand: ";
    for (const Card& card : dealerHand) {
        cout << "[" << card.rank << " of " << card.suit << "] ";
    }
    cout << "Total: " << total << endl;
}


int main() {
    bool playAgain = true;
    while (playAgain == true) {
        vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
        vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        vector<Card> deck;
        vector<Card> playerHand;
        vector<Card> dealerHand;

        for (string suit : suits) {
            for (string rank : ranks) {
                int value;
                if (rank == "J" || rank == "Q" || rank == "K") { value = 10; }
                else if (rank == "A") { value = 1; }
                else { value = stoi(rank); }

                Card card{ rank, suit, value };
                deck.push_back(card);
            }
        }

        shuffle(deck.begin(), deck.end(), mt19937(random_device{}()));

        deal(playerHand, deck);
        deal(dealerHand, deck);
        deal(playerHand, deck);
        deal(dealerHand, deck);

        string choice;
        bool turnOver = false;
        while (!turnOver && calculateHandTotal(playerHand) < 21) {
            clearScreen();
            
            printPlayerHand(playerHand);
            cout << "Dealer's hand: " << "[" << dealerHand[0].rank << " of " << dealerHand[0].suit << "] [???] Total: ???" << endl;
            cout << "Do you want to [H]it or [S]tand?" << endl;
            cin >> choice;
            if (choice == "H" || choice == "h") {
                clearScreen();
                deal(playerHand, deck);
                printPlayerHand(playerHand);
                cout << "Dealer's hand: " << "[" << dealerHand[0].rank << " of " << dealerHand[0].suit << "] [???] Total: ???" << endl;
            }
            else if (choice == "S" || choice == "s") {
                clearScreen();
                turnOver = true;
            }
            else { cout << "Invalid choice. Please try again" << endl; }
        }

        if (calculateHandTotal(playerHand) > 21) {
            clearScreen();
            cout << "You busted! Dealer wins!" << endl;
            printPlayerHand(playerHand);
            printDealerHand(dealerHand);
        }
        else {
            while (calculateHandTotal(dealerHand) < 17) {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                deal(dealerHand, deck);
            }
            if (calculateHandTotal(dealerHand) > 21) {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                cout << "Dealer busted! You win!" << endl;
            }
            else if (calculateHandTotal(playerHand) == 21 && calculateHandTotal(dealerHand) != 21) {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                cout << "BLACKJACK!!! YOU WIN!!!" << endl;
            }
            else if (calculateHandTotal(playerHand) > calculateHandTotal(dealerHand)) {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                cout << "You win!" << endl;
            }
            else if (calculateHandTotal(playerHand) < calculateHandTotal(dealerHand)) {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                cout << "Dealer wins!" << endl;
            }
            else {
                clearScreen();
                printPlayerHand(playerHand);
                printDealerHand(dealerHand);
                cout << "Push! You tie!" << endl;
            }
        }
        string replay;
        cout << "Would you like to play again? Y/N?" << endl;
        cin >> replay;
        if (replay != "Y" && replay != "y") {
            playAgain = false;
        }
    }
    cout << "Thanks for playing!" << endl;
}
