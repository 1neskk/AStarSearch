#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

std::vector<std::vector<State>> ReadBoardFile(const std::string& filename);
std::vector<State> ParseLine(const std::string& line);
void PrintBoard(const std::vector<std::vector<State>>& board);
std::string CellString(State cell);

namespace AStarSearch
{
    std::vector<std::vector<State>> Search(std::vector<std::vector<State>>& board, int init[2], int goal[2]);
    int Heuristic(int x1, int y1, int x2, int y2);
    void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& openNodes, std::vector<std::vector<State>>& board);
    bool Compare(const std::vector<int>& node1, const std::vector<int>& node2);
    void CellSort(std::vector<std::vector<int>>& openNodes);
    bool CheckValidCell(int x, int y, const std::vector<std::vector<State>>& board);
    void ExpandNeighbors(const std::vector<int>& currentNode, int goal[2], std::vector<std::vector<int>>& openNodes, std::vector<std::vector<State>>& board);
}
