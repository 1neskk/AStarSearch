#include "main.h"

int main()
{
    const std::string filename = "board.txt";
    std::vector<std::vector<State>> board = ReadBoardFile(filename);
    int init[2]{0, 0};
    int goal[2]{4, 5};
    const std::vector<std::vector<State>> solution = AStarSearch::Search(board, init, goal);
    PrintBoard(solution);
    return 0;
}

std::vector<std::vector<State>> ReadBoardFile(const std::string& filename)
{
    std::vector<std::vector<State>> board;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return board;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<State> row = ParseLine(line);
        board.push_back(row);
    }
    file.close();
    return board;
}

std::vector<State> ParseLine(const std::string& line)
{
    std::istringstream iss(line);
    std::vector<State> row;
    int value;
    char comma;
    while (iss >> value >> comma)
    {
        row.push_back(value == 0 ? State::kEmpty : State::kObstacle);
    }
    return row;
}

void PrintBoard(const std::vector<std::vector<State>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << CellString(board[i][j]);
        }
        std::cout << "\n";
    }
}

std::string CellString(State cell)
{
    switch (cell)
    {
		case State::kObstacle: return "#   "; // emojis doesn't work in cmd/powershell :(
		case State::kPath: return "*   ";
		case State::kStart: return "&   ";
		case State::kFinish: return "$   ";
        default: return "0   ";
    }
}

// A* Search functions

std::vector<std::vector<State>> AStarSearch::Search(std::vector<std::vector<State>>& board, int init[2], int goal[2])
{
    std::vector<std::vector<int>> openNodes{};
	int x = init[0];
    int y = init[1];
    constexpr int g = 0;
    const int h = Heuristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, openNodes, board);
    while(!openNodes.empty())
    {
        CellSort(openNodes);
        auto currentNode = openNodes.back();
        openNodes.pop_back();
        x = currentNode[0];
        y = currentNode[1];
        board[x][y] = State::kPath;
        if (x == goal[0] && y == goal[1])
        {
            return board;
        }
        ExpandNeighbors(currentNode, goal, openNodes, board);
    }

    std::cout << "No path found!" << std::endl;
    return std::vector<std::vector<State>>{};
}

int AStarSearch::Heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}

void AStarSearch::AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& openNodes, std::vector<std::vector<State>>& board)
{
    const std::vector<int> node{x, y, g, h};
    openNodes.push_back(node);
    board[x][y] = State::kClosed;
}

bool AStarSearch::Compare(const std::vector<int>& node1, const std::vector<int>& node2)
{
    return (node1[2] + node1[3]) > (node2[2] + node2[3]);
}

void AStarSearch::CellSort(std::vector<std::vector<int>>& openNodes)
{
    std::sort(openNodes.begin(), openNodes.end(), Compare);
}

bool AStarSearch::CheckValidCell(int x, int y, const std::vector<std::vector<State>>& board)
{
    const bool onGridX = (x >= 0 && x < board.size());
    const bool onGridY = (y >= 0 && y < board[0].size());
    if (onGridX && onGridY)
    {
        return board[x][y] == State::kEmpty;
    }
    return false;
}

void AStarSearch::ExpandNeighbors(const std::vector<int>& currentNode, int goal[2], std::vector<std::vector<int>>& openNodes, std::vector<std::vector<State>>& board)
{
    constexpr int delta[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
    const int x = currentNode[0];
    const int y = currentNode[1];
    int g = currentNode[2];

    for (int i = 0; i < 4; i++)
    {
        const int x2 = x + delta[i][0];
        const int y2 = y + delta[i][1];
        if (CheckValidCell(x2, y2, board))
        {
            const int g2 = g++;
            const int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, openNodes, board);
        }
    }
}
