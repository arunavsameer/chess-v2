bool check_position_by_type(pair<int, int> position, char type, bool colour)
    {
        if (type == 'r' || type == 'q')
        {
            if (colour == 1)
            {
                if (arena[position.first][position.second][0] == 'R' || arena[position.first][position.second][0] == 'Q')
                {
                    return true;
                }
            }
            else
            {
                if (arena[position.first][position.second][0] == 'r' || arena[position.first][position.second][0] == 'q')
                {
                    return true;
                }
            }
        }
        else if (type == 'b' || type == 'q')
        {
            if (colour == 1)
            {
                if (arena[position.first][position.second][0] == 'B' || arena[position.first][position.second][0] == 'Q')
                {
                    return true;
                }
            }
            else
            {
                if (arena[position.first][position.second][0] == 'b' || arena[position.first][position.second][0] == 'q')
                {
                    return true;
                }
            }
        }
        else if (type == 'n')
        {
            if (colour == 1)
            {
                if (arena[position.first][position.second][0] == 'K' && arena[position.first][position.second][1] != 'G')
                {
                    return true;
                }
            }
            else
            {
                if (arena[position.first][position.second][0] == 'k' && arena[position.first][position.second][1] != 'g')
                {
                    return true;
                }
            }
        }
        else if (type == 'k')
        {
            if (colour == 1)
            {
                if (arena[position.first][position.second][0] == 'K' && arena[position.first][position.second][1] == 'G')
                {
                    return true;
                }
            }
            else
            {
                if (arena[position.first][position.second][0] == 'k' && arena[position.first][position.second][1] == 'g')
                {
                    return true;
                }
            }
        }
        else if (type == 'p')
        {
            if (colour == 1)
            {
                if (arena[position.first][position.second][0] == 'P')
                {
                    return true;
                }
            }
            else
            {
                if (arena[position.first][position.second][0] == 'p')
                {
                    return true;
                }
            }
        }
        return false;
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
                        if (get_piece_at_position(make_pair(i.position.first + 2, i.position.second)) == nullptr && !i.is_moved)
                        {
                            chance A;
                            A.to_move = &i;
                            A.initial = i.position;
                            A.final = make_pair(i.position.first + 2, i.position.second);
                            possible.push_back(A);
                        }
                    }
                    if (get_piece_at_position(make_pair(i.position.first + 1, i.position.second + 1)) != nullptr && get_piece_at_position(make_pair(i.position.first + 1, i.position.second + 1))->colour == !colour)
                    {
                        chance A;
                        A.to_move = &i;
                        A.initial = i.position;
                        A.final = make_pair(i.position.first + 1, i.position.second + 1);
                        possible.push_back(A);
                    }
                    if (get_piece_at_position(make_pair(i.position.first + 1, i.position.second - 1)) != nullptr && get_piece_at_position(make_pair(i.position.first + 1, i.position.second - 1))->colour == !colour)
                    {
                        chance A;
                        A.to_move = &i;
                        A.initial = i.position;
                        A.final = make_pair(i.position.first + 1, i.position.second + 1);
                        possible.push_back(A);
                    }
                }
            }
        }

chance A;
A.to_move = is_rook;
A.initial = make_pair(0, 0);
A.final = make_pair(0, 2);
make_move(A, colour);

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
            black.push_back(queen(name, i.final, 1));
        }
        turn++;
    }
    else if (choice == 'r')
    {
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
            black.push_back(rook(name, i.final, 1));
        }
        turn++;
    }
    else if (choice == 'k')
    {
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
            black.push_back(knight(name, i.final, 1));
        }
        turn++;
    }
    else if (choice == 'b')
    {
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
            black.push_back(knight(name, i.final, 1));
        }
        turn++;
    }
    continue;
}