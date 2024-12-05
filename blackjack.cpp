#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int deal_card() {
    vector<int> cards = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
    return cards[rand() % cards.size()];
}

void adjust_for_ace(vector<int>& hand) {
    int score = 0, ace_count = 0;
    for (int card : hand) {
        score += card;
        if (card == 11) ace_count++;
    }
    while (score > 21 && ace_count > 0) {
        for (int& card : hand) {
            if (card == 11) {
                card = 1;
                score -= 10;
                ace_count--;
                break;
            }
        }
    }
}

int calculate_score(vector<int>& hand) {
    adjust_for_ace(hand);
    int score = 0;
    for (int card : hand) score += card;
    return score;
}

void print_hand(const string& name, const vector<int>& hand) {
    cout << name << "의 카드: ";
    for (int card : hand) cout << card << " ";
    cout << endl;
}

bool player_turn(vector<int>& hand) {
    char choice;
    while (true) {
        cout << "카드를 더 받으시겠습니까? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            hand.push_back(deal_card());
            adjust_for_ace(hand);
            print_hand("사용자", hand);
            if (calculate_score(hand) > 21) {
                cout << "사용자가 버스트! 딜러가 승리했습니다." << endl;
                return false;
            }
        }
        else if (choice == 'n') {
            return true;
        }
        else {
            cout << "잘못된 입력입니다. y 또는 n을 입력해주세요." << endl;
        }
    }
}

bool ask_play_again() {
    char play_again;
    while (true) {
        cout << "다시 플레이하시겠습니까? (y/n): ";
        cin >> play_again;
        if (play_again == 'y' || play_again == 'n') return play_again == 'y';
        cout << "잘못된 입력입니다. y 또는 n을 입력해주세요." << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    do {
        cout << "\n블랙잭 게임을 시작합니다!\n" << endl;

        vector<int> user_hand = { deal_card(), deal_card() };
        vector<int> dealer_hand = { deal_card(), deal_card() };

        print_hand("사용자", user_hand);
        print_hand("딜러", dealer_hand);

        if (player_turn(user_hand)) {
            while (calculate_score(dealer_hand) < 17) dealer_hand.push_back(deal_card());
            print_hand("딜러", dealer_hand);

            int user_score = calculate_score(user_hand);
            int dealer_score = calculate_score(dealer_hand);

            cout << "사용자의 점수: " << user_score << endl;
            cout << "딜러의 점수: " << dealer_score << endl;

            if (dealer_score > 21 || user_score > dealer_score) {
                cout << "사용자가 승리했습니다!" << endl;
            }
            else if (user_score < dealer_score) {
                cout << "딜러가 승리했습니다!" << endl;
            }
            else {
                cout << "무승부입니다!" << endl;
            }
        }
    } while (ask_play_again());

    return 0;
}
