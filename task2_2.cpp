#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <algorithm>

using std::vector;

struct Player {
    int feature;
    int index;
};

bool ComparePlayerByFeature(const Player & FirstPlayer, const Player & SecondPlayer) {
    if (FirstPlayer.feature < SecondPlayer.feature) {
         return true;
    }
    if (FirstPlayer.feature >= SecondPlayer.feature) {
         return false;
    }
}

bool ComparePlayerByIndex(const Player & FirstPlayer, const Player & SecondPlayer) {
    if (FirstPlayer.index < SecondPlayer.index) {
         return true;
    }
    if (FirstPlayer.index >= SecondPlayer.index) {
         return false;
    }
}


void Input (vector <Player>* Players) {
    int Length;
    scanf("%d", &Length);
    Players->resize(Length);
    for (int i = 0; i < Length; ++i) {
         scanf("%lld", &(Players->at(i)).feature);
         (Players->at(i)).index = i;
    }
}


void QuickSort(vector<Player>::iterator First, vector<Player>::iterator Last, 
               bool (*ComparePlayer) (const Player &, const Player &)) {
    if ((First == Last) || (First + 1 == Last)) { 
         return;
    }
    Player Pivot = *(First + rand() % (Last - First));
    vector<Player>::iterator PointerLessPivot = First;
    vector<Player>::iterator PointerMorePivot = Last;
    while (PointerLessPivot < PointerMorePivot) {
        if (PointerMorePivot != Last) { 
            ++PointerLessPivot;
        }
        --PointerMorePivot;
         while ((*ComparePlayer)(Pivot, *PointerMorePivot)) {
             --PointerMorePivot;
         }
         while ((*ComparePlayer)(*PointerLessPivot, Pivot)) {
             ++PointerLessPivot;
         }
         if (PointerLessPivot < PointerMorePivot) {
              std::swap(*PointerLessPivot, *PointerMorePivot);
         }
    }
    QuickSort(First, PointerMorePivot + 1, (*ComparePlayer));
    QuickSort(PointerMorePivot + 1, Last, (*ComparePlayer));
}

long long FindBestTeamEffectivness(const vector <Player>& Players, vector <Player>* Team) {
    vector <Player> SortedPlayers = Players;
    QuickSort(SortedPlayers.begin(), SortedPlayers.end(), ComparePlayerByFeature);
    if (SortedPlayers.size() == 1) {
         Team->resize(1);
         Team->at(0).feature = SortedPlayers[0].index;
         Team->at(0).index = 0;
         return SortedPlayers[0].feature;
    }
    long long BestTeam = 0;
    long long SumEffectiveness = 0;
    int WorstPlayer = 0;
    int FirstPlayer;
    int LastPlayer;
    int PlayerIndex = 0;
    while (PlayerIndex < SortedPlayers.size()) {
         long long BestPlayer = static_cast<long long>(SortedPlayers[WorstPlayer].feature) + 
                                static_cast<long long>(SortedPlayers[WorstPlayer + 1].feature);
         if (SortedPlayers[PlayerIndex].feature <= BestPlayer) {
              SumEffectiveness += SortedPlayers[PlayerIndex].feature;
              if (PlayerIndex + 1 == SortedPlayers.size()) {
                   if (SumEffectiveness > BestTeam) {
                        BestTeam = SumEffectiveness;
                        FirstPlayer = WorstPlayer;
                        LastPlayer = PlayerIndex;
                   }
                   Team->clear();
                   for (int i = FirstPlayer; i <= LastPlayer; ++i) {
                       Team->push_back(SortedPlayers[i]);
                   }
                   QuickSort(Team->begin(), Team->end(), ComparePlayerByIndex);
                   return BestTeam;
              }
              ++PlayerIndex;
         }
         else {
              if (SumEffectiveness > BestTeam) {
                   BestTeam = SumEffectiveness;
                   FirstPlayer = WorstPlayer;
                   LastPlayer = PlayerIndex - 1;
              }
              SumEffectiveness -= SortedPlayers[WorstPlayer].feature;
              ++WorstPlayer;
         }
    }
}

void Output(const long long MaximalEffectivness, vector <Player> & Team) {
    printf("%lld\n", MaximalEffectivness);
    for (int i = 0; i < Team.size(); ++i) {
         printf("%d ", Team[i].index + 1);
    }
    printf("\n");
}


int main() {
    vector <Player> Players;
    Input(&Players);
    vector <Player> Team;
    long long MaximalEffectivness = FindBestTeamEffectivness(Players, &Team);
    Output(MaximalEffectivness, Team);
    return 0;
}
