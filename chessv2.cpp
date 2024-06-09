#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct piece
{
    bool is_moved;
    bool colour;
    string name = "  ";
    int value;
    pair<int, int> position;
    char type;
};

struct chance
{
    piece *to_move;
    pair<int, int> final;
    pair<int, int> initial;
};

int ascii_thsld = 95;

class game
{
    char arena[8][8][2];
    vector<piece> white;
    vector<piece> black;
    bool game_over = false;

public:
    piece pawn(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 1;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'p';
        return A;
    }

    piece rook(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 5;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'r';
        return A;
    }
    piece knight(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 3;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'n';
        return A;
    }
    piece bishop(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 3;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'b';
        return A;
    }
    piece queen(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 9;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'q';
        return A;
    }
    piece king(string name, pair<int, int> position, bool colour)
    {
        piece A;
        A.is_moved = false;
        A.value = 100;
        A.name = name;
        A.position = position;
        A.colour = colour;
        A.type = 'k';
        return A;
    }

    void reset_vectors()
    {

        white.clear();
        black.clear();

        black.push_back(rook("r1", make_pair(7, 7), 0));
        black.push_back(knight("k1", make_pair(7, 6), 0));
        black.push_back(bishop("b1", make_pair(7, 5), 0));
        black.push_back(queen("qn", make_pair(7, 4), 0));
        black.push_back(king("kg", make_pair(7, 3), 0));
        black.push_back(bishop("b2", make_pair(7, 2), 0));
        black.push_back(knight("k2", make_pair(7, 1), 0));
        black.push_back(rook("r2", make_pair(7, 0), 0));
        black.push_back(pawn("p1", make_pair(6, 7), 0));
        black.push_back(pawn("p2", make_pair(6, 6), 0));
        black.push_back(pawn("p3", make_pair(6, 5), 0));
        black.push_back(pawn("p4", make_pair(6, 4), 0));
        black.push_back(pawn("p5", make_pair(6, 3), 0));
        black.push_back(pawn("p6", make_pair(6, 2), 0));
        black.push_back(pawn("p7", make_pair(6, 1), 0));
        black.push_back(pawn("p8", make_pair(6, 0), 0));

        white.push_back(rook("R1", make_pair(0, 7), 1));
        white.push_back(knight("K1", make_pair(0, 6), 1));
        white.push_back(bishop("B1", make_pair(0, 5), 1));
        white.push_back(queen("QN", make_pair(0, 4), 1));
        white.push_back(king("KG", make_pair(0, 3), 1));
        white.push_back(bishop("B2", make_pair(0, 2), 1));
        white.push_back(knight("K2", make_pair(0, 1), 1));
        white.push_back(rook("R2", make_pair(0, 0), 1));
        white.push_back(pawn("P1", make_pair(1, 7), 1));
        white.push_back(pawn("P2", make_pair(1, 6), 1));
        white.push_back(pawn("P3", make_pair(1, 5), 1));
        white.push_back(pawn("P4", make_pair(1, 4), 1));
        white.push_back(pawn("P5", make_pair(1, 3), 1));
        white.push_back(pawn("P6", make_pair(1, 2), 1));
        white.push_back(pawn("P7", make_pair(1, 1), 1));
        white.push_back(pawn("P8", make_pair(1, 0), 1));
    }

    void reset_arena()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((i + j) % 2 == 0)
                {
                    arena[i][j][0] = ' ';
                    arena[i][j][1] = ' ';
                }
                else
                {
                    arena[i][j][0] = ':';
                    arena[i][j][1] = ':';
                }
            }
        }
    }

    void put_pieces_from_vectors()
    {
        for (auto Piece : white)
        {
            if (Piece.position.first >= 0 && Piece.position.second >= 0)
            {
                arena[Piece.position.first][Piece.position.second][0] = Piece.name[0];
                arena[Piece.position.first][Piece.position.second][1] = Piece.name[1];
            }
        }

        for (auto Piece : black)
        {
            if (Piece.position.first >= 0 && Piece.position.second >= 0)
            {
                arena[Piece.position.first][Piece.position.second][0] = Piece.name[0];
                arena[Piece.position.first][Piece.position.second][1] = Piece.name[1];
            }
        }
    }

    void print_arena(bool chance)
    {
        if (!chance)
        {
            cout << "      H    G    F    E    D    C    B    A   " << endl;
            cout << "   +----+----+----+----+----+----+----+----+" << endl;
            for (int i = 0; i < 8; i++)
            {
                cout << " " << i + 1 << " | ";
                for (int j = 0; j < 8; j++)
                {
                    cout << arena[i][j][0];
                    cout << arena[i][j][1];
                    cout << " | ";
                }
                cout << i + 1 << endl;
                cout << "   +----+----+----+----+----+----+----+----+" << endl;
            }
            cout << "      H    G    F    E    D    C    B    A   " << endl;
        }
        else
        {
            cout << "      A    B    C    D    E    F    G    H" << endl;
            cout << "   +----+----+----+----+----+----+----+----+" << endl;
            for (int i = 7; i >= 0; i--)
            {
                cout << " " << i + 1 << " | ";
                for (int j = 7; j >= 0; j--)
                {
                    cout << arena[i][j][0];
                    cout << arena[i][j][1];
                    cout << " | ";
                }
                cout << i + 1 << endl;
                cout << "   +----+----+----+----+----+----+----+----+" << endl;
            }
            cout << "      A    B    C    D    E    F    G    H" << endl;
        }
    }

    void print_board_vector(bool chance)
    {
        reset_arena();
        put_pieces_from_vectors();
        print_arena(chance);
    }

    piece *get_piece_at_position(pair<int, int> subject)
    {
        for (auto &i : black)
        {
            if (i.position == subject)
            {
                return &(i);
            }
        }

        for (auto &i : white)
        {
            if (i.position == subject)
            {
                return &(i);
            }
        }
        return nullptr;
    }

    vector<piece *> find_threats(pair<int, int> subject, bool colour)
    {
        vector<piece *> threats;
        bool enemy = !colour;
        threats.clear();
        // along vertical
        for (int i = subject.first + 1; i < 8; i++)
        {
            if (get_piece_at_position(make_pair(i, subject.second)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(i, subject.second));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'r' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(i, subject.second)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        for (int i = subject.first - 1; i >= 0; i--)
        {
            if (get_piece_at_position(make_pair(i, subject.second)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(i, subject.second));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'r' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(i, subject.second)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        // along horizontal
        for (int j = subject.second + 1; j < 8; j++)
        {

            if (get_piece_at_position(make_pair(subject.first, j)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first, j));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'r' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first, j)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        for (int j = subject.second - 1; j >= 0; j--)
        {

            if (get_piece_at_position(make_pair(subject.first, j)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first, j));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'r' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first, j)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        };
        // diagonals
        int j = subject.second + 1;
        for (int i = subject.first + 1; i < 8; i++)
        {
            if (get_piece_at_position(make_pair(i, j)) != nullptr && j < 8)
            {
                piece potential = *get_piece_at_position(make_pair(i, j));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'b' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(i, j)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            j++;
        };
        j = subject.second - 1;
        for (int i = subject.first + 1; i < 8; i++)
        {
            if (get_piece_at_position(make_pair(i, j)) != nullptr && j >= 0)
            {
                piece *potential = get_piece_at_position(make_pair(i, j));
                if (potential->colour == enemy)
                {
                    if (potential->type == 'b' || potential->type == 'q')
                    {
                        threats.push_back(potential);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            j--;
        }
        j = subject.second + 1;
        for (int i = subject.first - 1; i >= 0; i--)
        {
            if (get_piece_at_position(make_pair(i, j)) != nullptr && j < 8)
            {
                piece potential = *get_piece_at_position(make_pair(i, j));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'b' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(i, j)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            j++;
        };
        j = subject.second - 1;
        for (int i = subject.first - 1; i >= 0; i--)
        {
            if (get_piece_at_position(make_pair(i, j)) != nullptr && j >= 0)
            {
                piece potential = *get_piece_at_position(make_pair(i, j));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'b' || potential.type == 'q')
                    {
                        threats.push_back(get_piece_at_position(make_pair(i, j)));
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            j--;
        }
        // knights
        if (subject.first + 2 < 8 && subject.second + 1 < 8)
        {
            if (get_piece_at_position(make_pair(subject.first + 2, subject.second + 1)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first + 2, subject.second + 1));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first + 2, subject.second + 1)));
                    }
                }
            }
        }
        if (subject.first + 2 < 8 && subject.second - 1 >= 0)
        {
            if (get_piece_at_position(make_pair(subject.first + 2, subject.second - 1)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first + 2, subject.second - 1));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first + 2, subject.second - 1)));
                    }
                }
            }
        }
        if (subject.first - 2 >= 0 && subject.second + 1 < 8)
        {
            if (get_piece_at_position(make_pair(subject.first - 2, subject.second + 1)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first - 2, subject.second + 1));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first - 2, subject.second + 1)));
                    }
                }
            }
        }
        if (subject.first - 2 >= 0 && subject.second - 1 >= 0)
        {
            if (get_piece_at_position(make_pair(subject.first - 2, subject.second - 1)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first - 2, subject.second - 1));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first - 2, subject.second - 1)));
                    }
                }
            }
        }
        if (subject.first - 1 >= 0 && subject.second - 2 >= 0)
        {
            if (get_piece_at_position(make_pair(subject.first - 1, subject.second - 2)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first - 1, subject.second - 2));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first - 1, subject.second - 2)));
                    }
                }
            }
        }
        if (subject.first - 1 >= 0 && subject.second + 2 < 8)
        {
            if (get_piece_at_position(make_pair(subject.first - 1, subject.second + 2)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first - 1, subject.second + 2));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first - 1, subject.second + 2)));
                    }
                }
            }
        }
        if (subject.first + 1 < 8 && subject.second + 2 < 8)
        {
            if (get_piece_at_position(make_pair(subject.first + 1, subject.second + 2)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first + 1, subject.second + 2));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first + 1, subject.second + 2)));
                    }
                }
            }
        }
        if (subject.first + 1 < 8 && subject.second - 2 >= 0)
        {
            if (get_piece_at_position(make_pair(subject.first + 1, subject.second - 2)) != nullptr)
            {
                piece potential = *get_piece_at_position(make_pair(subject.first + 1, subject.second - 2));
                if (potential.colour == enemy)
                {
                    if (potential.type == 'n')
                    {
                        threats.push_back(get_piece_at_position(make_pair(subject.first + 1, subject.second - 2)));
                    }
                }
            }
        }
        // pawn
        if (colour == 0 && subject.first - 1 >= 0)
        {
            if (subject.second + 1 < 8)
            {
                piece *potential = get_piece_at_position(make_pair(subject.first - 1, subject.second + 1));
                if (potential != nullptr)
                {
                    if (potential->colour == enemy)
                    {
                        if (potential->type == 'p')
                        {
                            threats.push_back(potential);
                        }
                    }
                }
            }
            if (subject.second - 1 >= 0)
            {
                piece *potential = get_piece_at_position(make_pair(subject.first - 1, subject.second - 1));
                if (potential != nullptr)
                {
                    if (potential->colour == enemy)
                    {
                        if (potential->type == 'p')
                        {
                            threats.push_back(potential);
                        }
                    }
                }
            }
        }
        else if (colour == 1 && subject.first + 1 < 8)
        {
            if (subject.second + 1 < 8)
            {
                piece *potential = get_piece_at_position(make_pair(subject.first + 1, subject.second + 1));
                if (potential != nullptr)
                {
                    if (potential->colour == enemy)
                    {
                        if (potential->type == 'p')
                        {
                            threats.push_back(potential);
                        }
                    }
                }
            }
            if (subject.second - 1 >= 0)
            {
                piece *potential = get_piece_at_position(make_pair(subject.first + 1, subject.second - 1));
                if (potential != nullptr)
                {
                    if (potential->colour == enemy)
                    {
                        if (potential->type == 'p')
                        {
                            threats.push_back(potential);
                        }
                    }
                }
            }
        }
        // king
        for (int i = subject.first - 1; i <= subject.first + 1; i++)
        {
            for (int j = subject.second - 1; j <= subject.second + 1; j++)
            {
                if (i < 8 && i >= 0 && j < 8 && j >= 0)
                {
                    if (!(i == subject.first && j == subject.second))
                    {
                        if (get_piece_at_position(make_pair(i, j)) != nullptr)
                        {
                            piece potential = *get_piece_at_position(make_pair(i, j));
                            if (potential.colour == enemy)
                            {
                                if (potential.type == 'k')
                                {
                                    threats.push_back(get_piece_at_position(make_pair(i, j)));
                                }
                            }
                        }
                    }
                }
            }
        }
        return threats;
    }

    piece *find_king(bool colour)
    {
        if (colour)
        {
            for (auto &i : white)
            {
                if (i.type == 'k')
                {
                    return &i;
                }
            }
        }
        else
        {
            for (auto &i : black)
            {
                if (i.type == 'k')
                {
                    return &i;
                }
            }
        }
    }

    void make_move(chance c, bool colour)
    {
        piece *taken = get_piece_at_position(c.final);
        c.to_move->position = c.final;
        c.to_move->is_moved = true;
        if (taken != nullptr)
        {
            kill(taken);
        }
    }

    void kill(piece *taken)
    {
        if (taken->colour)
        {
            taken->position = make_pair(-1, -1);
        }
        else
        {
            taken->position = make_pair(-2, -2);
        }
    }

    bool check_after_put(chance c, bool turn)
    {
        // dbg(0);
        bool is_valid = false;
        piece kg_temp = *find_king(turn);
        piece *taken = get_piece_at_position(c.final);
        if (taken == nullptr)
        {
            c.to_move->position = c.final;
        }
        else
        {
            taken->position = make_pair(-3, -3);
            c.to_move->position = c.final;
        }
        if (c.to_move->type == 'k')
        {
            kg_temp = *find_king(turn);
        }
        // print_board_vector(turn);
        if (find_threats(kg_temp.position, turn).size() == 0)
        {
            is_valid = true;
        }
        c.to_move->position = c.initial;
        if (taken != nullptr)
        {
            taken->position = c.final;
        }
        return is_valid;
    }

    void dbg(int i)
    {
        cout << "test" << i << endl;
    }

    piece *validate_input(string &input, bool colour)
    {
        if (input.size() != 4)
        {
            return nullptr;
        }
        piece *subject = nullptr;
        string piece_name = "";
        piece_name += input[0];
        piece_name += input[1];
        if (colour)
        {
            for (auto &i : white)
            {
                if (tolower(i.name[0]) == tolower(piece_name[0]) && tolower(i.name[1]) == tolower(piece_name[1]))
                {
                    subject = &i;
                }
            }
        }
        else
        {
            for (auto &i : black)
            {
                if (tolower(i.name[0]) == tolower(piece_name[0]) && tolower(i.name[1]) == tolower(piece_name[1]))
                {
                    subject = &i;
                }
            }
        }
        if (subject == nullptr)
        {
            return nullptr;
        }

        if (tolower(input[2]) < 97 || tolower(input[2]) > 104)
        {
            return nullptr;
        }

        if (input[3] < 49 || input[3] > 56)
        {
            return nullptr;
        }
        pair<int, int> posn;
        posn.first = input[3] - 49;
        posn.second = (104 - input[2]);
        piece *taken = get_piece_at_position(posn);
        if (taken != nullptr)
        {
            if (taken->colour == colour)
            {
                return nullptr;
            }
        }
        // castling
        if (subject->type == 'k' && !subject->is_moved)
        {
            int delta = subject->position.second - posn.second;
            // king side castle
            if (subject->position.first == posn.first && delta == 2)
            {
                int kg_file;
                if (colour)
                {
                    kg_file = 0;
                }
                else
                {
                    kg_file = 7;
                }
                piece *is_rook = get_piece_at_position(make_pair(kg_file, 0));
                if (is_rook != nullptr)
                {
                    if (is_rook->type == 'r' && !is_rook->is_moved)
                    {
                        if (get_piece_at_position(make_pair(kg_file, 1)) == nullptr && get_piece_at_position(make_pair(kg_file, 2)) == nullptr)
                        {
                            vector<piece *> threat1 = find_threats(make_pair(kg_file, 1), colour);
                            vector<piece *> threat2 = find_threats(make_pair(kg_file, 2), colour);
                            vector<piece *> threat3 = find_threats(make_pair(kg_file, 3), colour);
                            if (threat1.size() == 0 && threat2.size() == 0 && threat3.size() == 0)
                            {
                                chance A;
                                A.to_move = is_rook;
                                A.initial = make_pair(0, 0);
                                A.final = make_pair(0, 2);
                                make_move(A, colour);
                                return subject;
                            }
                        }
                    }
                }
            }
            // queen side castle
            else if (subject->position.first == posn.first && delta == -2)
            {
                int kg_file;
                if (colour)
                {
                    kg_file = 0;
                }
                else
                {
                    kg_file = 7;
                }
                piece *is_rook = get_piece_at_position(make_pair(kg_file, 7));
                if (is_rook != nullptr)
                {
                    if (is_rook->type == 'r' && !is_rook->is_moved)
                    {
                        if (get_piece_at_position(make_pair(kg_file, 4)) == nullptr && get_piece_at_position(make_pair(kg_file, 5)) == nullptr && get_piece_at_position(make_pair(kg_file, 5)) == nullptr)
                        {
                            vector<piece *> threat1 = find_threats(make_pair(kg_file, 3), colour);
                            vector<piece *> threat2 = find_threats(make_pair(kg_file, 4), colour);
                            vector<piece *> threat3 = find_threats(make_pair(kg_file, 5), colour);
                            if (threat1.size() == 0 && threat2.size() == 0 && threat3.size() == 0)
                            {
                                chance A;
                                A.to_move = is_rook;
                                A.initial = make_pair(kg_file, 7);
                                A.final = make_pair(kg_file, 4);
                                make_move(A, colour);
                                return subject;
                            }
                        }
                    }
                }
            }
        }
        vector<piece *> threats = find_threats(posn, !colour);
        bool can_go = false;
        for (auto i : threats)
        {
            if (i->name == subject->name)
            {
                can_go = true;
            }
            if (i->type == 'p' && can_go && (get_piece_at_position(posn) == nullptr || get_piece_at_position(posn)->colour == colour))
            {
                can_go = false;
            }
            if (can_go)
            {
                break;
            }
        }
        if (subject->type == 'p' && !can_go)
        {
            if (colour)
            {
                if (subject->position.first + 1 == posn.first && subject->position.second == posn.second)
                {
                    if (get_piece_at_position(make_pair(subject->position.first + 1, subject->position.second)) == nullptr)
                    {
                        can_go = true;
                    }
                }
                else if (subject->position.first + 2 == posn.first && subject->position.second == posn.second && !subject->is_moved)
                {
                    if (get_piece_at_position(make_pair(subject->position.first + 2, subject->position.second)) == nullptr)
                    {
                        can_go = true;
                    }
                }
            }
            else
            {
                if (subject->position.first - 1 == posn.first && subject->position.second == posn.second)
                {
                    if (get_piece_at_position(make_pair(subject->position.first - 1, subject->position.second)) == nullptr)
                    {
                        can_go = true;
                    }
                }
                else if (subject->position.first - 2 == posn.first && subject->position.second == posn.second && !subject->is_moved)
                {
                    if (get_piece_at_position(make_pair(subject->position.first - 2, subject->position.second)) == nullptr)
                    {
                        can_go = true;
                    }
                }
            }
        }
        if (!can_go)
        {
            return nullptr;
        }
        return subject;
    }

    chance convert_input_to_chance(piece *subject, string &input)
    {
        chance A;
        A.to_move = subject;
        A.initial = subject->position;
        pair<int, int> posn;
        posn.first = input[3] - 49;
        posn.second = tolower(104 - input[2]);
        A.final = posn;

        return A;
    }

    vector<chance> possible_moves(bool colour)
    {
        vector<chance> possible;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                pair<int, int> posn = make_pair(i, j);
                vector<piece *> threats = find_threats(posn, !colour);
                for (auto i : threats)
                {
                    if (get_piece_at_position(posn) != nullptr && get_piece_at_position(posn)->colour != colour)
                    {
                        chance A;
                        A.to_move = i;
                        A.final = posn;
                        A.initial = i->position;
                        possible.push_back(A);
                    }
                    else if (get_piece_at_position(posn) == nullptr)
                    {
                        if (i->type != 'p')
                        {
                            chance A;
                            A.to_move = i;
                            A.final = posn;
                            A.initial = i->position;
                            possible.push_back(A);
                        }
                    }
                }
            }
        }
        if (colour)
        {
            for (auto &i : white)
            {
                if (i.type == 'p')
                {
                    if (i.position.first + 1 < 8)
                    {
                        if (get_piece_at_position(make_pair(i.position.first + 1, i.position.second)) == nullptr)
                        {
                            chance A;
                            A.to_move = &i;
                            A.initial = i.position;
                            A.final = make_pair(i.position.first + 1, i.position.second);
                            possible.push_back(A);
                        }
                    }
                    if (i.position.first + 2 < 8)
                    {
                        if (get_piece_at_position(make_pair(i.position.first + 1, i.position.second)) == nullptr && get_piece_at_position(make_pair(i.position.first + 2, i.position.second)) == nullptr && !i.is_moved)
                        {
                            chance A;
                            A.to_move = &i;
                            A.initial = i.position;
                            A.final = make_pair(i.position.first + 2, i.position.second);
                            possible.push_back(A);
                        }
                    }
                }
            }
        }
        else
        {
            for (auto &i : black)
            {
                if (i.type == 'p')
                {
                    if (i.position.first - 1 >= 0)
                    {
                        if (get_piece_at_position(make_pair(i.position.first - 1, i.position.second)) == nullptr)
                        {
                            chance A;
                            A.to_move = &i;
                            A.initial = i.position;
                            A.final = make_pair(i.position.first - 1, i.position.second);
                            possible.push_back(A);
                        }
                    }
                    if (i.position.first - 2 >= 0)
                    {
                        if (get_piece_at_position(make_pair(i.position.first - 1, i.position.second)) == nullptr && get_piece_at_position(make_pair(i.position.first - 2, i.position.second)) == nullptr && !i.is_moved)
                        {
                            chance A;
                            A.to_move = &i;
                            A.initial = i.position;
                            A.final = make_pair(i.position.first - 2, i.position.second);
                            possible.push_back(A);
                        }
                    }
                }
            }
        }
        for (auto it = possible.begin(); it != possible.end();)
        {
            if (!check_after_put(*it, colour))
            {
                it = possible.erase(it);
            }
            else
            {
                it++;
            }
        }

        // castling king side
        int kg_rank;
        if (colour)
        {
            kg_rank = 0;
        }
        else
        {
            kg_rank = 7;
        }
        piece *kg_temp = find_king(colour);
        if (!kg_temp->is_moved)
        {
            piece *is_rook_k = get_piece_at_position(make_pair(kg_rank, 0));
            piece *is_rook_q = get_piece_at_position(make_pair(kg_rank, 7));
            if (is_rook_k != nullptr)
            {
                if (is_rook_k->type == 'r' && !is_rook_k->is_moved)
                {
                    if (get_piece_at_position(make_pair(kg_rank, 1)) == nullptr && get_piece_at_position(make_pair(kg_rank, 2)) == nullptr)
                    {
                        vector<piece *> threat1 = find_threats(make_pair(kg_rank, 1), colour);
                        vector<piece *> threat2 = find_threats(make_pair(kg_rank, 2), colour);
                        vector<piece *> threat3 = find_threats(make_pair(kg_rank, 3), colour);
                        if (threat1.size() == 0 && threat2.size() == 0 && threat3.size() == 0)
                        {
                            chance A;
                            A.to_move = kg_temp;
                            A.initial = kg_temp->position;
                            A.final = make_pair(kg_rank, 1);
                            possible.push_back(A);
                        }
                    }
                }
            }
            if (is_rook_q != nullptr)
            {
                if (is_rook_q->type == 'r' && !is_rook_q->is_moved)
                {
                    if (get_piece_at_position(make_pair(kg_rank, 4)) == nullptr && get_piece_at_position(make_pair(kg_rank, 5)) == nullptr && get_piece_at_position(make_pair(kg_rank, 6)) == nullptr)
                    {
                        vector<piece *> threat1 = find_threats(make_pair(kg_rank, 3), colour);
                        vector<piece *> threat2 = find_threats(make_pair(kg_rank, 4), colour);
                        vector<piece *> threat3 = find_threats(make_pair(kg_rank, 5), colour);
                        if (threat1.size() == 0 && threat2.size() == 0 && threat3.size() == 0)
                        {
                            chance A;
                            A.to_move = kg_temp;
                            A.initial = kg_temp->position;
                            A.final = make_pair(kg_rank, 5);
                            possible.push_back(A);
                        }
                    }
                }
            }
        }
        return possible;
    }

    void save_history(string input)
    {
        fstream file;
        file.open("history.txt", ios_base::app);
        if (file.is_open())
        {
            file << input << endl;
        }
        file.close();
    }

    int redo_history()
    {
        reset_vectors();
        int turn = 1;
        bool colour = turn % 2;
        ifstream file;
        string line;
        file.open("history.txt");
        while (getline(file, line))
        {
            bool colour = turn % 2;
            piece *moving = validate_input(line, colour);

            if (moving != nullptr)
            {
                chance A = convert_input_to_chance(moving, line);

                if (A.to_move->type == 'p' && (A.final.first == 7 || A.final.first == 0))
                {
                    // promotion
                    char choice = line[4];
                    char first = choice;
                    char second = 48 + A.to_move->name[1];
                    if (colour)
                    {
                        first = choice - 32;
                    }
                    string name = "";
                    name += first;
                    name += second;
                    if (choice == 'q')
                    {
                        if (get_piece_at_position(A.final) != nullptr)
                        {
                            kill(get_piece_at_position(A.final));
                        }
                        kill(moving);
                        if (colour)
                        {
                            white.push_back(queen(name, A.final, 1));
                        }
                        else
                        {
                            black.push_back(queen(name, A.final, 0));
                        }
                        turn++;
                    }
                    else if (choice == 'r')
                    {
                        if (get_piece_at_position(A.final) != nullptr)
                        {
                            kill(get_piece_at_position(A.final));
                        }
                        kill(moving);
                        if (colour)
                        {
                            white.push_back(rook(name, A.final, 1));
                        }
                        else
                        {
                            black.push_back(rook(name, A.final, 0));
                        }
                        turn++;
                    }
                    else if (choice == 'k')
                    {
                        if (get_piece_at_position(A.final) != nullptr)
                        {
                            kill(get_piece_at_position(A.final));
                        }
                        kill(moving);
                        if (colour)
                        {
                            white.push_back(knight(name, A.final, 1));
                        }
                        else
                        {
                            black.push_back(knight(name, A.final, 0));
                        }
                        turn++;
                    }
                    else if (choice == 'b')
                    {
                        if (get_piece_at_position(A.final) != nullptr)
                        {
                            kill(get_piece_at_position(A.final));
                        }
                        kill(moving);
                        if (colour)
                        {
                            white.push_back(knight(name, A.final, 1));
                        }
                        else
                        {
                            black.push_back(knight(name, A.final, 0));
                        }
                        turn++;
                    }
                    continue;
                }
                make_move(A, colour);
                turn++;
            }
        }
        return turn;
    }

    void play_game(int turn)
    {
        do
        {
            bool colour = turn % 2;
            print_board_vector(colour);
            vector<chance> possible = possible_moves(colour);
            vector<piece *> kg_threats = find_threats(find_king(colour)->position, colour);
            if (possible.size() == 0)
            {
                game_over = true;

                if (kg_threats.size() == 0)
                {
                    cout << "STALEMATE" << endl;
                }
                else
                {
                    cout << "CHECKMATE" << endl;
                }
                break;
            }
            else if (kg_threats.size() != 0)
            {
                cout << "CHECK" << endl;
            }
            // for (auto i : possible)
            // {
            //     cout << i.to_move->name << " " << i.final.first << " " << i.final.second << endl;
            // }
            // cout << endl;
            if (colour)
            {
                cout << "WHITE MOVE: ";
            }
            else
            {
                cout << "BLACK MOVE: ";
            }
            string input;
            cin >> input;
            piece *moving = validate_input(input, colour);

            if (moving != nullptr)
            {
                chance A = convert_input_to_chance(moving, input);
                for (auto &i : possible)
                {
                    if (i.to_move == A.to_move && i.final == A.final && i.initial == A.initial)
                    {
                        if (i.to_move->type == 'p' && (i.final.first == 7 || i.final.first == 0))
                        {
                            // promotion
                            cout << "choose piece:\n(q)ueen\n(r)ook\n(k)night\n(b)ishop\n";
                            char choice;
                            cin >> choice;
                            char first = choice;
                            char second = 48 + i.to_move->name[1];
                            if (colour)
                            {
                                first = choice - 32;
                            }
                            string name = "";
                            name += first;
                            name += second;
                            if (choice == 'q')
                            {
                                input += 'q';
                                if (get_piece_at_position(i.final) != nullptr)
                                {
                                    kill(get_piece_at_position(i.final));
                                }
                                kill(moving);
                                if (colour)
                                {
                                    white.push_back(queen(name, i.final, 1));
                                }
                                else
                                {
                                    black.push_back(queen(name, i.final, 0));
                                }
                                turn++;
                            }
                            else if (choice == 'r')
                            {
                                input += 'r';
                                if (get_piece_at_position(i.final) != nullptr)
                                {
                                    kill(get_piece_at_position(i.final));
                                }
                                kill(moving);
                                if (colour)
                                {
                                    white.push_back(rook(name, i.final, 1));
                                }
                                else
                                {
                                    black.push_back(rook(name, i.final, 0));
                                }
                                turn++;
                            }
                            else if (choice == 'k')
                            {
                                input += 'k';
                                if (get_piece_at_position(i.final) != nullptr)
                                {
                                    kill(get_piece_at_position(i.final));
                                }
                                kill(moving);
                                if (colour)
                                {
                                    white.push_back(knight(name, i.final, 1));
                                }
                                else
                                {
                                    black.push_back(knight(name, i.final, 0));
                                }
                                turn++;
                            }
                            else if (choice == 'b')
                            {
                                input += 'b';
                                if (get_piece_at_position(i.final) != nullptr)
                                {
                                    kill(get_piece_at_position(i.final));
                                }
                                kill(moving);
                                if (colour)
                                {
                                    white.push_back(knight(name, i.final, 1));
                                }
                                else
                                {
                                    black.push_back(knight(name, i.final, 0));
                                }
                                turn++;
                            }
                            continue;
                        }
                        make_move(A, colour);
                        save_history(input);
                        turn++;
                        break;
                    }
                }
            }
            system("cls");
        } while (!game_over);
    }
};

int main()
{
    game chess;
    int turn = chess.redo_history();
    chess.play_game(turn);
}