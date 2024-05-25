#include "define_piece.hpp"
using namespace std;

struct board{
    piece Board[8][8];
};


board decode_fen(string fen){
    board initial;
    bool r, R, n, N, b, B = 0;
    int p, P = 1;
    int i, j = 0;
    for(int k = 0; k < fen.length(); k++){
        if(fen[k] == '/'){
            i++;
            j = 0;
        }
        else if(fen[k] < 57 && fen[k] > 48){
            int gap = fen[k] - 48;
            for(int r = 0; r < gap; r++){
                initial.Board[i][j + r] = empty();
            }
        }else if(fen[k] == 'r'){
            if(!r){
                initial.Board[i][j] = rook("r1",make_pair(i, j), 0);
                cout << "hi";
                r = !r;
            }else{
                initial.Board[i][j] = rook("r2",make_pair(i, j), 0);
            }
        }else if(fen[k] == 'n'){
            if(!n){
                initial.Board[i][j] = knight("k1",make_pair(i, j), 0);
                n = !n;
            }else{
                initial.Board[i][j] = knight("k2",make_pair(i, j), 0);
            }
        }else if(fen[k] == 'b'){
            if(!b){
                initial.Board[i][j] = bishop("b1",make_pair(i, j), 0);
                b = !b;
            }else{
                initial.Board[i][j] = bishop("b2",make_pair(i, j), 0);
            }
        }else if(fen[k] == 'q'){
            initial.Board[i][j] = queen("qn",make_pair(i, j), 0);
        }else if(fen[k] == 'k'){
            initial.Board[i][j] = queen("kg",make_pair(i, j), 0);
        }else if(fen[k] == 'p'){
            string name = "p" + to_string(p);
            initial.Board[i][j] = pawn(name,make_pair(i, j), 0);
            p++;
        }


        else if(fen[k] == 'R'){
            if(!R){
                initial.Board[i][j] = rook("R1",make_pair(i, j), 1);
                R = !R;
            }else{
                initial.Board[i][j] = rook("R2",make_pair(i, j), 1);
            }
        }else if(fen[k] == 'N'){
            if(!N){
                initial.Board[i][j] = knight("K1",make_pair(i, j), 1);
                N = !N;
            }else{
                initial.Board[i][j] = knight("K2",make_pair(i, j), 1);
            }
        }else if(fen[k] == 'B'){
            if(!B){
                initial.Board[i][j] = bishop("B1",make_pair(i, j), 1);
                B = !B;
            }else{
                initial.Board[i][j] = bishop("B2",make_pair(i, j), 1);
            }
        }else if(fen[k] == 'Q'){
            initial.Board[i][j] = queen("QN",make_pair(i, j), 1);
        }else if(fen[k] == 'K'){
            initial.Board[i][j] = queen("KG",make_pair(i, j), 1);
        }else if(fen[k] == 'P'){
            string name = "P" + to_string(P);
            initial.Board[i][j] = pawn(name,make_pair(i, j), 1);
            P++;
        }

        j++;
    }
    return initial;
}