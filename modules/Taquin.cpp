#include "Taquin.h"

bool Taquin::is_correct_move(string state, int move)
{
    int blank_position = state.find(BLANK_CASE);
    if (blank_position == string::npos)
    {
        return false;
    }
    switch (move)
    {
    case UP:
        if (blank_position - SIZE >= 0)
            return true;
        break;
    case DOWN:
        if (blank_position + SIZE < SIZE * SIZE)
            return true;
        break;
    case LEFT:
        if ((blank_position) % SIZE > 0)
            return true;
        break;
    case RIGHT:
        if ((blank_position) % SIZE < SIZE - 1)
            return true;
        break;
    default:
        break;
    }
    return false;
}
string Taquin::do_move(string state, int move)
{
    string new_state = state;
    int blank_position = state.find(BLANK_CASE);
    switch (move)
    {
    case UP:
        new_state[blank_position] = state[blank_position - SIZE];
        new_state[blank_position - SIZE] = state[blank_position];
        break;
    case DOWN:
        new_state[blank_position] = state[blank_position + SIZE];
        new_state[blank_position + SIZE] = state[blank_position];
        break;
    case LEFT:
        new_state[blank_position] = state[blank_position - 1];
        new_state[blank_position - 1] = state[blank_position];
        break;
    case RIGHT:
        new_state[blank_position] = state[blank_position + 1];
        new_state[blank_position + 1] = state[blank_position];
        break;
    }
    return new_state;
}
list<string> Taquin::neighbords_list(string state)
{
    list<string> voisins;
    int move;
    for (move = UP; move <= RIGHT; move++)
        if (this->is_correct_move(state, move))
            voisins.push_back(this->do_move(state, move));

    return voisins;
}
void Taquin::solve()
{
    list<string> visited = {this->state};
    list<string> finished = {};
    Graphe graphe;
    string actual_state = FINAL_STATE;
    this->story = {};
    Node node_root;
    node_root.label = visited.front();
    node_root.parent = "";
    node_root.neighbords = neighbords_list(node_root.label);
    graphe.addNode(node_root);

    while (!visited.empty())
    {
        Node node;
        node.label = visited.front();
        visited.pop_front();
        node = graphe.get(node.label);
        // cout << "Node : " << node.label << endl;

        for (auto it = node.neighbords.begin(); it !=
                                                node.neighbords.end();
             ++it)
        {
            bool found_finished = (std::find(finished.begin(), finished.end(), *it) != finished.end());
            bool found_visited = (std::find(visited.begin(), visited.end(), *it) != visited.end());
            if (found_visited == false && found_finished == false)
            {
                Node node_child;
                node_child.label = *it;
                node_child.parent = node.label;
                node_child.neighbords = neighbords_list(node_child.label);
                graphe.addNode(node_child);
                visited.push_back(*it);
            }
        }

        finished.push_back(node.label);
        if (node.label.compare(FINAL_STATE) == 0)
            break;
    }
    this->graphe = graphe;
    while (actual_state.compare(string("")))
    {
        this->story.push_front(actual_state);
        actual_state = graphe.get(actual_state).parent;
    }
}
void Taquin::show_list(list<string> my_list)
{
    for (auto it = my_list.begin(); it !=
                                    my_list.end();
         ++it)
        cout << ' ' << *it;
    cout << endl;
}
void Taquin::show_state(string state)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        if (i == 0)
        {
            for (j = 0; j < 2 * SIZE + 3; j++)
                cout << "-";
            cout << endl;
        }
        for (j = 0; j < SIZE; j++)
        {
            if (j == 0)
                cout << "|";
            cout << " " << state[i * SIZE + j];
            if (j == SIZE - 1)
                cout << " |" << endl;
        }
        if (i == SIZE - 1)
        {
            for (j = 0; j < 2 * SIZE + 3; j++)
                cout << "-";
            cout << endl;
        }
    }
}
void Taquin::show_story()
{
    cout << "Story: ";
    this->show_list(this->story);
    cout << "Initial state" << endl;
    for (auto it = this->story.begin(); it != this->story.end(); it++)
    {
        show_state(*it);
        cout << endl;
    }
    cout << "Solved in " << this->story.size() - 1 << " steps(s)" << endl;
}

void Taquin::write_inDb()
{
    if (this->story.size())
    {
        string const nomFichier(DB_NAME);
        ofstream monFlux(nomFichier.c_str(), ios::app);
        int actual_size = story.size()-1;

        if (monFlux)
        {
           for(auto it=this->story.begin(); actual_size > 0; it++, actual_size--){
                monFlux << *it << ";" << actual_size << endl;
           }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier " << DB_NAME << endl;
        }
    }
}


